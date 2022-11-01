# Untitled - By: lenovo - 周四 11月 4 2021
import sensor, image,time,lcd,utime
import KPU as kpu
import gc, sys
from fpioa_manager import fm
from machine import UART
# need your connect hardware IO 9/10 to loopback
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)  #映射串口IO口

uart_A = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096) #初始化串口
red_threshold =(0, 34, -128, 127, -128, 127)
red=[0, 34, -128, 127, -128, 127]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
lcd.init()
lcd.rotation(2)
#areas=[(),(),(),(),()]
areas = [(60,100,40,40), (100,100,40,40),(140,100,40,40),(180,100,40,40),(220,100,40,40)]
def getTrace(img):
    Trace = [0,0,0,0,0]
    for area in areas:
        img.draw_rectangle(area)   #圈出识别区块
        statistics = img.get_statistics(roi=area) #统计像素颜色

        if red[0]<statistics.l_mode()<red[1] and red[2]<statistics.a_mode()<red[3] and red[4]<statistics.b_mode()<red[5]: #如果该区域是红色
            img.draw_string(area[0]+5, area[1]+3, "1")    #标记为1
            Trace[areas.index(area)] = 1
        else: img.draw_string(area[0]+5, area[1]+3, "0")  #标记为0
    return Trace
num=[0,0,0,0,0]

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    num=getTrace(img)
    num10=num[4]*1+num[3]*2+num[2]*4+num[1]*8+num[0]*16
    data = bytearray([0xfe,num10,0xff])    #帧头 + 帧头 + x + y + 帧尾
    uart_A.write(data)
    lcd.display(img)
