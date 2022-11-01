# Untitled - By: lenovo - 周四 11月 4 2021
import sensor, image,time,lcd,utime
from pyb import UART
red_threshold =(9, 65, 5, 127, -128, 127)
red=[9, 65, 5, 127, -128, 127]
uart=UART(3,115200)
green_threshold  =(0, 33, -128, -2, -128, 127)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_whitebal(False)
sensor.set_auto_gain(False)
#lcd.init()
#lcd.rotation(2)
#areas=[(),(),(),(),()]
areas = [(25,50,20,20), (45,50,20,20),(65,50,20,20),(85,50,20,20),(105,50,20,20)]
def getTrace(img):
    Trace = [0,0,0,0,0]
    for area in areas:
        #img.draw_rectangle(area)   #圈出识别区块
        statistics = img.get_statistics(roi=area) #统计像素颜色

        if red[0]<statistics.l_mode()<red[1] and red[2]<statistics.a_mode()<red[3] and red[4]<statistics.b_mode()<red[5]: #如果该区域是红色
            #img.draw_string(area[0]+5, area[1]+3, "1")    #标记为1
            Trace[areas.index(area)] = 1
        #else: #img.draw_string(area[0]+5, area[1]+3, "0")  #标记为0
    return Trace
num=[0,0,0,0,0]

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    num=getTrace(img)
    num10=num[4]*1+num[3]*2+num[2]*4+num[1]*8+num[0]*16
    blobs = img.find_blobs([green_threshold],area_threshold=50,pixels_threshold=300,margin=400,merge = True)
    if blobs:
        for b in blobs:
            x = b[0]
            y = b[1]
            width = b[2]
            height = b[3]
            #img.draw_rectangle([x,y,width,height]) # rect
            #img.draw_cross(b[5], b[6]) # cx, cy
            num=b[9]
            if num<=3:
                num=1
            print(num)
            data1 = bytearray([0xfe,num10,num,0xff])    #帧头 + 帧头 + x + y + 帧尾
            uart.write(data1)
    else :
        data = bytearray([0xfe,num10,1,0xff])    #帧头 + 帧头 + x + y + 帧尾
        uart.write(data)
    #print(num)
    #print(num10)

    #lcd.display(img)
    #print(clock.fps())
