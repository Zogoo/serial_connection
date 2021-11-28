#define BAUD_RATE 115200

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 15)
  {
    String data = Serial.readStringUntil('\n');
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("You sent me: " + data + "\n");
  }
}
