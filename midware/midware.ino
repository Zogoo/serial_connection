#include <Wire.h>
#define SLAVE_ADDRESS 0x08
#define BAUD_RATE 115200

String data_in_echo;
String data_out_echo;
bool i2c_data_received;
bool serial_data_recieved;

void setup()
{
  i2c_data_received = false;
  serial_data_recieved = false;
  data_out_echo = "\n";
  Serial.begin(BAUD_RATE);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop()
{
  if (Serial.availableForWrite() > 15 && i2c_data_received)
  {
    Serial.println(data_in_echo);
    data_in_echo = "\n";
    data_out_echo = Serial.readStringUntil('\n');
    serial_data_recieved = true;
    i2c_data_received = false;
  }
}

void receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++)
  {
    data_in_echo[i] = Wire.read();
  }
  i2c_data_received = true;
}

void sendData()
{
  if (serial_data_recieved && data_out_echo.length() > 0)
  {
    Wire.write(data_out_echo.c_str());
  }
}
