/*
  KeyPress_WithRisingEdge.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The KeyPress event occurs when presses a key
*/

#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

RepeatButton button;                // Decalre the RepeatButton object

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isPressed(true)) {               // Steady State Pressed Key
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}