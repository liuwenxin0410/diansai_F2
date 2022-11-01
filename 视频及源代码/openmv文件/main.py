THRESHOLD = (21, 0, -77, 5, -110, 127)
import sensor, image, time
from pyb import LED
import car
from pid import PID
import time
from pyb import UART
import math
rho_pid = PID(p=0.37, i=0)
theta_pid = PID(p=0.001, i=0)
LED(1).on()
LED(2).on()
LED(3).on()
uart = UART(3,19200)
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()
while(True):
	clock.tick()
	img = sensor.snapshot().binary([THRESHOLD])
	line = img.get_regression([(100,100)], robust = True)
	if (line):
		rho_err = abs(line.rho())-img.width()/2
		if line.theta()>90:
			theta_err = line.theta()-180
		else:
			theta_err = line.theta()
		img.draw_line(line.line(), color = 127)
		print(rho_err,line.magnitude(),rho_err)
		if line.magnitude()>8:
			rho_output = rho_pid.get_pid(rho_err,1)
			theta_output = theta_pid.get_pid(theta_err,1)
			output = rho_output + theta_output
			if(output<0):
				output = abs(output) + 100
			OUTPUT = str(round(output))
			uart.write(OUTPUT)
			uart.write('\r\n')
			print(OUTPUT)
		pass