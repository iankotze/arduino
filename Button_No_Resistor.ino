

int bottomRightButton = 3;
int topRightButton = 2;

int bottomLeftButton = 12;
int topLeftButton = 11;
int buzzer = 10;

int onBoardLED = 13;

void setup()
{
  // put your setup code here, to run once:
  pinMode(bottomRightButton, INPUT_PULLUP);
  pinMode(topRightButton, INPUT_PULLUP);
  pinMode(bottomLeftButton, INPUT_PULLUP);
  pinMode(topLeftButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(topRightButton));
  if (digitalRead(topRightButton) == LOW)
  {
    digitalWrite(onBoardLED, HIGH);
  }
  else
  {
    digitalWrite(onBoardLED, LOW);
  }


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
