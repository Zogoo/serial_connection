#include <Wire.h>
#define SLAVE_ADDRESS 0x08
#define BAUD_RATE 115200

String data_in_echo;
String data_out_echo;
bool is_data_received;

void setup()
{
  is_data_received = false;
  data_out_echo = "\n";
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop()
{
  if (Serial.available() && is_data_received)
  {
    Serial.println(data_in_echo);
    data_out_echo = Serial.readStringUntil('\n');
    data_in_echo = "\n";
    is_data_received = false;
  }
}

void receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++)
  {
    data_in_echo[i] = Wire.read();
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }
  is_data_received = true;
}

void sendData()
{
  if (!is_data_received){
    Wire.write(data_out_echo.toInt());
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  } else {
    Wire.write('\0');
  }
}
