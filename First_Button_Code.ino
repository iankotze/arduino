//Declare variables
//The bottom left button will connect to pin nr 12.
int bottomLeftButton = 12;
//The on board LED is automatically connected to pin 13. You don't need any wires for this
int onBoardLED = 13;
//In setup we define a bunch of things that Arduino needs to know about our construction
//This is only executed once when the program is run.
void setup()
{
  //The pin that the bottom left button is connected to is defined as an "INPUT_PULLUP" pin
  pinMode(bottomLeftButton, INPUT_PULLUP);
  //Start the serial monitor, this allows us to view certain things in the serial monitor
  Serial.begin(9600);
}
// Put your main code here, this runs in a loop forever
void loop() {
  //Print  the digitial status of the bottomLeftButton to the serial monitor
  //Output will be either a 0 or a 1
  // 0 = LOW 1 = HIGH
  Serial.println(digitalRead(bottomLeftButton));
  //If the button is pushed then the onboard LED is switched on
  if (digitalRead(bottomLeftButton) == LOW)
  {
    digitalWrite(onBoardLED, HIGH);
  }
  //If the button is not pushed then the onboard LED is switched of
  else
  {
    digitalWrite(onBoardLED, LOW);
  }
  //Wait for 1/10th of a second before repeating the loop.
  delay(100);
}
