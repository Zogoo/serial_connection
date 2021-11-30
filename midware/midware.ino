#include <Wire.h>
#define SLAVE_ADDRESS 0x08
#define BAUD_RATE 115200

String data_in_echo;
String data_out_echo;
bool i2c_data_received;
bool serial_data_recieved;
int data_out_index;

void setup()
{
  i2c_data_received = false;
  serial_data_recieved = false;
  data_out_index = 0;
  data_out_echo = "\n";
  Serial.begin(BAUD_RATE);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop()
{
  if (Serial.available() > 0)
  {
    if(i2c_data_received) {
      Serial.println(data_in_echo);
      data_in_index = 0;
      i2c_data_received = false;
    }
    else if (!serial_data_recieved)
    {
      data_out_echo = Serial.readStringUntil('\n');
      if (data_out_echo.length() > 0)
      {
        serial_data_recieved = true;
        data_out_index = 0;
      }
    }
  }
}

void receiveData(int bytecount)
{

  int data_in_index = 0;
  while (Wire.available())
  {
    byte recv_byte = 0;
    recv_byte = Wire.read();
    if (data_in_index < 15) data_in_echo[data_in_index] = recv_byte;
    Serial.println("Data input: " + String(recv_byte));
    data_in_index++;
  }
  i2c_data_received = true;
}

void sendData()
{
  int data_out_length = data_out_echo.length();

  if (serial_data_recieved && data_out_length > 1)
  {
    Serial.println("Data length: " + String(data_out_length));
    Wire.write(data_out_echo[data_out_index]);
    data_out_index++;
    serial_data_recieved = false;
    if (data_out_index > data_out_length)
    {
      data_out_index = 0;
    }
  }
}
