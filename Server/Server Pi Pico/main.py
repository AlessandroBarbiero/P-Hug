from machine import UART, Pin, PWM
import utime
import os

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
    
def readFromFile():
    
    with open('credentials.txt', 'a') as f:
        lines = f.readlines()
        

    # Strips the newline character
    if(len(lines) >= 2):
        uart1.write(lines[0])
        utime.sleep(2)
        uart1.write(lines[1])
        print(lines)
    else:
        uart1.write('Empty')
        print('Empty')


def writeFile(credentials):
    
    with open('credentials.txt', 'a') as f:
        f.write(credentials[0])
        f.write(credentials[1])


def deleteFile():
    
    with open('credentials.txt', 'w') as f:
        f.close()
        
    
    
jacket = Pin(2,Pin.OUT)
stby = Pin(19, Pin.OUT)
ina1 = Pin(18, Pin.OUT)
ina2 = Pin(17, Pin.OUT)
pwma = PWM(Pin(16))
pwma.freq(65535)

wifiRead = True
led = Pin(25, Pin.OUT)
firstTime = True
firstAttempt = True
jacket.value(1)
searchFlag = False
#utime.sleep(5)
print("Ready to go")

led.value(1)

uart = UART(0, baudrate=9600)
uart1 = UART(1, baudrate=9600)


#uart.write('Please insert Network name and Password')
while(wifiRead):
    #print('checking BT')
    if uart1.any():
        try:
            command = uart1.readline()
        except:
            continue
        
        if(command != None):
            try: 
                str = command.decode('utf-8', 'ignore')  
            except:
                continue
            
            
            msg = str.split(" ")

            if(msg[0] == "R:"):
                msg[1] = msg[1].replace("\r\n", "")
                print(msg[1])
                if(msg[1] == 'read'):
                    #uart.write('Reading credentials from memory. Please wait!\n')
                    readFromFile()
                    
                if(msg[1] == 'success'):
                    if (searchFlag):
                        writeFile(credentials)
                    wifiRead = False
                    uart.write('Success')
                    print(msg[1])
                    
                if(msg[1] == 'search'):
                    searchFlag = True
                    deleteFile()
                    if(firstAttempt):
                        uart.write('Please insert Network name \n')
                    else:
                        uart.write('SSID or password not correct!\n Please insert Network name again \n')
                    firstTime = True
                    print(msg[1])

    if uart.any():
        
        try:
            command = uart.readline()
        except:
            continue
        
        #print(command)
        if(command != None):
            try:
                str = command.decode('utf-8', 'ignore')
            except:
                continue
            
            #print(str)
            if(firstTime):
                credentials = []
                str = 'SSID: ' + str
                credentials.append(str)
                uart1.write(str)
                print(str)
                firstTime = False
                if(firstAttempt):
                    uart.write('Please insert password \n')
                else:
                    uart.write('Please insert password again \n')
            else:
                str = 'Password: ' + str
                credentials.append(str)
                uart1.write(str)
                print(str)
                firstTime = True
                
                if(firstAttempt):
                    uart.write('Attempting to connect to the network \n')
                    firstAttempt = False
                else:
                    uart.write('Attempting to connect to the network \n')
                    
                utime.sleep(1)
       
    utime.sleep(1)
    
print('Ready for the jacket')

while True:
    
    try:
        message = uart1.readline()
        if(message != None):
        
            detectMessage(message)
        
        utime.sleep(0.2)
    except:
        jacket.value(0)
        controlHugMotor(0)
        continue