int bottomLeftButton = 12;
int buzzer = 10;

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(bottomLeftButton, INPUT_PULLUP);
}

void loop() 
{
  if (digitalRead(bottomLeftButton) == LOW)
  {
    tone(buzzer,1000);
  }
  else
  {
    noTone(buzzer);
  }
  delay(100);
}
