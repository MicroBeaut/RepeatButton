/*
  KeyRepeat_WithCallbackFunc.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The Key Repeat event occurs when repeating a key.
*/

#include "RepeatButton.h"

#define buttonPin 2                     // Define the button input pin.

const uint16_t repeatDelay = 500;       // Set Delay 500 milliseconds
const uint16_t repeatRate = 100;        // Set Repeat rate 200 milliseconds

RepeatButton button;                    // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e); // Declare the OnKeyStateChanged Callback Function for the repeating option.

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP);   // Set the button mode
  button.repeatDelay(repeatDelay, repeatRate);  // Set the Hold delay and Repeat Rate
  button.buttonEvents(OnKeyStateChanged);       // Configure the callback function event on the key holding
}

void loop() {
  button.repeatButton();                        // Executing the Repeat button function
}

void OnKeyStateChanged(ButtonEvents e) {
  switch (e) {
    case PRESS:
      Serial.println("Event on Key Pressed");   // Print message event on key pressed
      break;
    case REPEAT:
      Serial.println("Event on Key Repeat");    // Print message event on key repeat                          
      break;
  }
}