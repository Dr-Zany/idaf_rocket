import serial
import time
 
# open the file in the write mode
f = open('yes.csv', 'w')
 
ser = serial.Serial(
 port='/dev/cu.usbmodem143301',\
 baudrate=115200,\
 parity=serial.PARITY_NONE,\
 stopbits=serial.STOPBITS_ONE,\
 bytesize=serial.EIGHTBITS,\
 timeout=None)
 
 
ser.close()
ser.open()
print("connected to: " + ser.portstr)
 
time.sleep(1)
ser.write(b'e')
ser.write(b'd')
 
print('Data:')
line = 0
while(1):
 line += 1
 x = ser.readline().decode('utf-8').rstrip()
 if(x != ''):
  print('line ' + str(line) + ': ' + x)
 f.write(x+'\n')
 if(x == str(line-2) + ' Data send'):
  break