#include <Wire.h>

/*!
 * @file HelloWorld.ino
 * @brief Show helloworld.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @maintainer [yangfeng](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-24
 * @url https://github.com/DFRobot/DFRobot_RGBLCD1602
 */
#include "DFRobot_RGBLCD1602.h"

//const int buttonPin = 4;
//const int buttonPin = 14;
//const int buttonPin = 15;
int myCounter = 0;
int buttonState = 0;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

#define LCD_RESET 15;

DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show


// this constant won't change:

const int  Up_buttonPin   = 4;    // the pin that the pushbutton is attached to
const int  Down_buttonPin = 14;
const int  Reset_buttonPin = 15;
const int Zero_buttonPin = 33;



// Variables will change:
bool bPress = false;
float score = 10;   // counter for the number of button presses

int up_buttonState = 0;         // current state of the up button
int up_lastButtonState = 0;     // previous state of the up button

int down_buttonState = 0;         // current state of the up button
int down_lastButtonState = 0;     // previous state of the up button

int reset_buttonState = 0;
int reset_lastButtonState = 0;

int zero_buttonState = 0;
int zero_lastButtonState = 0;


void setup()
{

  Serial.begin(9600);
  pinMode( Up_buttonPin , INPUT_PULLUP);
  pinMode( Down_buttonPin , INPUT_PULLUP);
  pinMode( Reset_buttonPin , INPUT_PULLUP);
  pinMode( Zero_buttonPin, INPUT_PULLUP);
  
  lcd.init();
  lcd.setRGB(colorR, colorG, colorB);

  // Print a message to the LCD.

  lcd.setCursor(0,0);

  lcd.print("CURRENT SCORE:");

  lcd.setCursor(2,1);

  lcd.print(score);
}





void loop()
{
  checkUp();
  checkDown();
  checkReset();
  checkZero();
   
  if( bPress){
    bPress = false;
    lcd.setCursor(2,1);
    lcd.print("               ");
    lcd.setCursor(2,1);
    lcd.print(score);
  }
}


float clamp(float val, float high, float low) {
  if (val < low) {
    return low;
  } else if (val > high) {
    return high;
  }

  return val;
}


void checkUp()
{

  up_buttonState = digitalRead(Up_buttonPin);

  // compare the buttonState to its previous state

  if (up_buttonState != up_lastButtonState) {

    // if the state has changed, increment the counter

    if (up_buttonState == LOW) {

        bPress = true;

      // if the current state is HIGH then the button went from off to on:

      score = clamp(score+0.5f,10.0f,0.0f);

      Serial.println("on");

      Serial.print("number of button pushes: ");

      Serial.println(score);

      /*
      int vin = analogRead(0);
      float float1 = float(vin/10);
      lcd.print("t0.txt=\"");
      lcd.print(float1,10);
      lcd.print("\"");
      */
    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing

    delay(50);

  }

  // save the current state as the last state, for next time through the loop

  up_lastButtonState = up_buttonState;

}

void checkDown()
{

  down_buttonState = digitalRead(Down_buttonPin);

  // compare the buttonState to its previous state

  if (down_buttonState != down_lastButtonState) {

    // if the state has changed, increment the counter

    if (down_buttonState == LOW) {

        bPress = true;

      // if the current state is HIGH then the button went from off to on:
      score = clamp(score-0.5f,10.0f,0.0f);

      Serial.println("on");
      Serial.println(score);

    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing
    delay(50);

  }
    // save the current state as the last state, for next time through the loop
  down_lastButtonState = down_buttonState;
}

void checkReset() 
{
  reset_buttonState = digitalRead(Reset_buttonPin);

  if (reset_buttonState != reset_lastButtonState) {
      // if the state has changed, reset score to 10
      if (reset_buttonState == LOW) {
        bPress = true;
        score = 10.0f;
      }
      delay(50);
  }

  reset_buttonState = reset_lastButtonState;
}

void checkZero() 
{
  zero_buttonState = digitalRead(Zero_buttonPin);

  if (zero_buttonState != zero_lastButtonState) {
      // if the state has changed, reset score to 10
      if (zero_buttonState == LOW) {
        bPress = true;
        score = 0.0f;
      }
      delay(50);
  }

  zero_buttonState = zero_lastButtonState;
}



