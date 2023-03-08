/*
  KeyHold_WithCallbackFunc.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut
*/

/*
  The KeyHold event occurs when holding a key.
*/

#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t holdDelay = 3000;    // Set Hold Time 3000 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyHolding(ButtonEvents e); // Declare the OnKeyHolding Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP);   // Set the button mode
  button.holdDelay(holdDelay);                  // Set the Hold delay
  button.onKeyHolding(OnKeyHolding);            // Configure the callback function event on the key holding
}

void loop() {
  button.repeatButton();                        // Executing the Repeat button function
}

void OnKeyHolding(ButtonEvents e) {
  Serial.println("Callback Event on Key Holding"); // Print message event on key Holding
}