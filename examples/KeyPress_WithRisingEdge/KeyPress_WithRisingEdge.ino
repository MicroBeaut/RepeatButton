/*
  KeyPress_WithRisingEdge.ino
  Created:  8-Mar-2023
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
  button.repeatButton();                        // Executing the Repeat button function
  if (button.isPressed()) {                     // Check Key Press (Rissing Edge Detector) 
    Serial.println("Rising Edge Key Pressed");  // Print message on rising edge key Holdin
  }
}