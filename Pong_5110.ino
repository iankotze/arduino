/*********************************************************************
  This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

  These displays use SPI to communicate, 4 or 5 pins are required to
  interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 8 - Serial clock out (SCLK)
// pin 7 - Serial data out (DIN)
// pin 6 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 7, 6, 5, 4);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


// Button Pin Setup
const int bottomRightButton = 3;
const int topRightButton = 2;
const int bottomLeftButton = 12;
const int topLeftButton = 11;

//Speaker/buzzer
const int buzzer = 10;
//onboard LED
const int onBoardLED = 13;


//Screen Size Parameters
int x_pixels = 84;
int y_pixels = 48;

//Paddle Parameters
int paddle_height = 10;
int paddle_width = 3;

// Ball velocities:
int x_vel = 1;
int y_vel = 1;

// Ball position:
int x_pos = 5;
int y_pos = 48                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ;

// Paddle positions:
int l_pos = 0;
int r_pos = 0;

// Player scores
int l_score = 0;
int r_score = 0;


void setup()
{

  // put your setup code here, to run once:
  // Button setup, button are wired without resistors, so we define them internally as pullup
  // Makes wiring easier but coding a bit more complicated  (LOW means buttons is pushed)
  pinMode(bottomRightButton, INPUT_PULLUP);
  pinMode(topRightButton, INPUT_PULLUP);
  pinMode(bottomLeftButton, INPUT_PULLUP);
  pinMode(topLeftButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(0));
  
  Serial.begin(9600);

  display.begin();
  // init done
  display.setRotation(2);
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer

//Display Arduino Pong splashscreen
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(display.width() / 2 - 20, 0);
  display.println("Ardunio");
  display.setCursor(display.width() / 2 - 20 / 2, 8);
  display.println("Pong");
  display.display();
  delay(2000);
}


void loop() {
  // Update position of left paddle:
  
  if (digitalRead(bottomLeftButton) == LOW && l_pos < (y_pixels - paddle_height)) {
    l_pos += 1;
  }
  else if (digitalRead(topLeftButton) == LOW && l_pos > 0) {
    l_pos -= 1;
  }

  //automatic right hand side paddle movement
  if (r_pos  + paddle_height < y_pixels || r_pos > 0)
  {
    r_pos = y_pos/2;
  }

  //  // Update position of right paddle:
  //  if (digitalRead(r_up_button) && r_pos < (y_pixels - paddle_height)) {
  //    r_pos += 1;
  //  }
  //  else if (digitalRead(r_down_button) && r_pos > 0) {
  //    r_pos -= 1;
  //  }
  
  
  // Check for ball hitting a wall:
  if (x_pos > x_pixels - 1) {
    ball_reset(false);
    l_score += 1;
    tone(buzzer, 50, 100);
    delay(50);
    tone(buzzer, 50, 100);
  }

  else if (x_pos < 0) {
    ball_reset(true);
    r_score += 1;
    tone(buzzer, 50, 100);
    delay(50);
    tone(buzzer, 50, 100);
  }

  // Check for ball bouncing off ceiling:

  if (y_pos > y_pixels - 1 || y_pos < 0) {
    y_vel = -y_vel;
  }

  // Check for ball bouncing off paddle:

  // Update ball position:
  x_pos += x_vel;
  y_pos += y_vel;

  // Draw pong elements to display:
  display.clearDisplay();
  //display.drawPixel(x_pos, y_pos, BLACK);
  display.drawCircle(x_pos, y_pos,  2, BLACK);
  display.fillCircle(x_pos, y_pos,  2, BLACK);
  display.fillRect(0, l_pos, paddle_width, paddle_height, BLACK);
  display.fillRect(x_pixels - paddle_width , r_pos, paddle_width, paddle_height, BLACK);

  // Display scores
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(display.width() / 4, 0);
  display.println(l_score);
  display.setCursor(display.width() * 3 / 4, 0);
  display.println(r_score);

  // Display all elements
  display.display();

  // Check for ball bouncing off paddles:
  if (ball_on_right_paddle()) {
    x_vel = -x_vel;
    tone(buzzer, 300, 100);
  }
  else if (ball_on_left_paddle()) {
    x_vel = -x_vel;
    tone(buzzer, 250, 100);
  }
}

bool ball_on_right_paddle() {
  // If ball is heading towards paddle and is at the surface of paddle between the top and bottom of the paddle, then it's a hit
  return (x_pos == x_pixels - paddle_width - 1 && y_pos >= r_pos && y_pos <= (r_pos + paddle_height) && x_vel == 1);
}


bool ball_on_left_paddle() {
  return (x_pos == paddle_width - 1 && y_pos >= l_pos && y_pos <= (l_pos + paddle_height) && x_vel == -1);
}


void ball_reset(bool left) {
  //If left is true, then ball should launch from the left, otherwise launch from the right
  //Ball should launch at a random Y location and at a random Y velocity

  y_pos = random(display.height());
  if (random(2) > 0) {
    y_vel = 1;
  }
  else {
    y_vel = -1;
  }

  if (left) {
    x_vel = 1;
    x_pos = paddle_width - 1;
  }

  else {
    x_vel = -1;
    x_pos = display.width() - paddle_width;
  }


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EXTRA TEST STUFF
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    //if ((i > 0) && (i % 14 == 0))
    //display.println();
  }
  display.display();
}

void testdrawcircle(void) {
  for (int16_t i = 0; i < display.height(); i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, BLACK);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i = 0; i < display.height() / 2; i += 3) {
    // alternate colors
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, color % 2);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i = 0; i < min(display.width(), display.height()) / 2; i += 5) {
    display.drawTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, BLACK);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = BLACK;
  for (int16_t i = min(display.width(), display.height()) / 2; i > 0; i -= 5) {
    display.fillTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, BLACK);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = BLACK;
  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawrect(void) {
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, BLACK);
    display.display();
  }
}

void testdrawline() {
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, BLACK);
    display.display();
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, BLACK);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, BLACK);
    display.display();
  }
  for (int8_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, BLACK);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, BLACK);
    display.display();
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, BLACK);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, BLACK);
    display.display();
  }
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, BLACK);
    display.display();
  }
  delay(250);
}
