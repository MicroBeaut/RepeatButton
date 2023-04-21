/*
  KeyHold_WithSteadyState.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The KeyHold event occurs when holding a key.
*/

#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t holdDelay = 3000;    // Set Hold Time 3000 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.holdDelay(holdDelay);                // Set the Hold delay
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isHold(true)) {                  // Steady State Hoding Key
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}