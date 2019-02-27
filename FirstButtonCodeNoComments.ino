int bottomLeftButton = 12;
int onBoardLED = 13;
void setup()
{
  pinMode(bottomLeftButton, INPUT_PULLUP);
  pinMode(onBoardLED, OUTPUT);
}
void loop() 
{
  if (digitalRead(bottomLeftButton) == LOW)
  {
    digitalWrite(onBoardLED, HIGH);
  }
  else
  {
    digitalWrite(onBoardLED, LOW);
  }
  delay(100);
}
