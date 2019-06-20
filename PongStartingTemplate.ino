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

//TASK 1
// Button Pin Setup

//Speaker/buzzer

//Onboard LED

//Screen Size Parameters

// Ball velocities:

// Ball position:                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ;

// Paddle Parameters

// Paddle positions:

// Player scores

// Put your setup code here, to run once:
void setup()
{
  //TASK 2
  // Define the pinMode for each button

  //Seed the random nr generator

  //Start the serial monitor
  
  //Initialize screen
  
  //change display rotation so it is upside down.
  
  // you can change the contrast around to adapt the display 
  // for the best viewing!

  // show splashscreen
   
  // clears the screen and buffer
  
  //Display Arduino Pong splashscreen

}

void loop() {

  //Set a delay on the loop, you can change this delay to slow down or speed up the game.
  
  // Update position of left paddle:
 
  // Update position of right paddle:

  // Check for ball hitting a wall:

  // Check for ball bouncing off ceiling:
  
  // Update ball position:
  
  // Check for ball bouncing off paddles:
  
  // Draw pong elements to display:
  
  // Display scores

  // Display all elements

}

//Predefined functions
bool ball_on_right_paddle() 
{
  // If ball is heading towards paddle and is at the surface of paddle between the top and bottom of the paddle, then it's a hit
  return (x_pos == x_pixels - paddle_width - 1 && y_pos >= r_pos && y_pos <= (r_pos + paddle_height) && x_vel == 1);
}


bool ball_on_left_paddle() 
{
  return (x_pos == paddle_width - 1 && y_pos >= l_pos && y_pos <= (l_pos + paddle_height) && x_vel == -1);
}


void ball_reset(bool left) 
{
  //If left is true, then ball should launch from the left, otherwise launch from the right
  //Ball should launch at a random Y location and at a random Y velocity
  delay(500);
  y_pos = random(display.height());
  if (random(2) > 0) 
  {
    y_vel = 1;
  }
  else 
  {
    y_vel = -1;
  }

  if (left) 
  {
    x_vel = 1;
    x_pos = paddle_width - 1;
  }

  else 
  {
    x_vel = -1;
    x_pos = display.width() - paddle_width;
  }
}
