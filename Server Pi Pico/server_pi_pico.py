from machine import UART, Pin, PWM
import utime

def detectMessage(message):
    str = message.decode('utf-8', 'ignore')
    msg = str.split(" ")
        
    if(msg[0] == "R:"):
        
        print(message)
        if(msg[1] == 'w'):
            
            jacket.value(int(msg[2]))
        
        if(msg[1] == 'h'):
            
            controlHugMotor(int(msg[2]))

    return("other input")




def controlHugMotor(controlValue):
    
     if controlValue == 0:
        stby.value(0)
        ina1.value(0)
        ina2.value(0)
        pwma.duty_u16(0)
     else:
        stby.value(1)
        ina1.value(1)
        ina2.value(0)
        pwma.duty_u16(65536)
        
     return
    


jacket = Pin(2,Pin.OUT)
stby = Pin(19, Pin.OUT)
ina1 = Pin(18, Pin.OUT)
ina2 = Pin(17, Pin.OUT)
pwma = PWM(Pin(16))
pwma.freq(65535)


jacket.value(1)
utime.sleep(5)
print("Ready to go")




uart1 = UART(1, baudrate=9600, tx=Pin(4), rx=Pin(5))

while True:
  
    message = uart1.readline()
    if(message != None):
        
        detectMessage(message)
            
        
    utime.sleep(0.2)