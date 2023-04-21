/*
  KeyRepeat_WithSteadyState.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The Key Repeat event occurs when repeating a key.
*/

#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t repeatDelay = 500;   // Set Delay 500 milliseconds
const uint16_t repeatRate = 100;    // Set Repeat rate 200 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP);   // Set the button mode
  button.repeatDelay(repeatDelay, repeatRate);  // Set the Hold delay and Repeat Rate
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isRepeat(true)) {                // Steady State RepeatKey
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}