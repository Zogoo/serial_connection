#include <Wire.h>
#define SLAVE_ADDRESS 0x08

String data_in_echo;
byte *data_tobe_sent;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop()
{
  if (Serial.available())
  {
    data_in_echo = Serial.readStringUntil('\n');
  }
}

void receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++)
  {
    data_in_echo[i] = Wire.read();
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }
  if (Serial.available())
  {
    Serial.println(data_in_echo);
  }
}

void sendData()
{
  Wire.write(data_in_echo.toInt());
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
}
