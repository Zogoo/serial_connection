#define BAUD_RATE 115200

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 15)
  {
    String data = Serial.readStringUntil('\n');
    Serial.println("You sent me: " + data);
  }
}
