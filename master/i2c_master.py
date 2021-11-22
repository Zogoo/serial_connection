import smbus
import time
bus = smbus.SMBus(1)

MIDWARE_ADDRESS = 0x08

def writeStringToI2C(value):
    byteValue = StringToBytes(value)    
    bus.write_i2c_block_data(MIDWARE_ADDRESS, 0x00, byteValue)
    return -1

def readStringFromI2C():
  charArr = []
  smbus.read_i2c_block_data(MIDWARE_ADDRESS, charArr)
  return BytesToString(charArr)

def StringToBytes(val):
  retVal = []
  for c in val:
          retVal.append(ord(c))
  return retVal

def BytesToString(val):
  retVal = ""
  for c in val:
    retVal += chr(ord(c))
  return retVal

while True:
    writeStringToI2C("Hello Leanordo")
    time.sleep(0.1)
    print(readStringFromI2C)