# RepeatButton
RepeatButton represents a control that raises its press event repeatedly from the time it is pressed until it is released. The `repeatDelay` property determines when the event begins. You can also control the repeat rate of the repetitions with the `repeat rate` property.
- [Syntax](#syntax)
  - [Declaration](#declaration)
  - [Button Events](#button-events)
  - [Execute](#execute)
  - [Parameters](#parameters)
  - [Events](#events)
  - [Returns](#returns)
- [Examples](#examples)
    - [Key Press and onKeyPressed](#key-press-and-onkeypressed)
    - [Key Release and onKeyReleased](#key-release-and-onkeyreleased)
    - [Key Hold and onKeyHolding](#key-hold-and-onkeyholding)
    - [Key Repeat and onKeyRepeating](#key-repeat-and-onkeyrepeating)

## Syntax

### Declaration
```C
RepeatButton repeatButtonVariable;
```

### Button Events
```C
enum ButtonEvents {
  PRESS = 1,     // Occurs when a key is pressed
  RELEASE = 2,   // Occurs when a key is released
  HOLD = 3,      // Occurs when a key is hold
  REPEAT = 4     // Occurs when a key is pressed an hold
};
```

### Execute
```C
bool repeatButton();    // Executing the Repeat button function
```

### Parameters
```C
void buttonMode(uint8_t pin, uint8_t mode /*INPUT | INPUT_PULLUP*/);
void debounceDelay(uint16_t debounceDelay /*mS*/);
void repeatDelay(uint16_t repeatDelay /*mS*/, uint16_t repeatRate/*mS*/);
```

### Events
```C
void buttonEvents(KeyEventCallback keyEventCallback);    // Occurs when a key is changed

// typedef void (*KeyEventCallback) (ButtonEvents e);
```

### Returns
```C
bool isKeyPressed();    // Determines whether the specified key is pressed
bool isKeyReleased();   // Determines whether the specified key is release
bool isKeyHolding();    // Determines whether the specified key is holding
bool isRepeating();     // Determines whether the specified key is repeating
```

## Examples

### Key Press and onKeyPressed

```C
#include "RepeatButton.h"

#define buttonPin 2                     // Define the button input pin.

RepeatButton button;                    // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e); // Occurs when a key is changed

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.buttonEvents(OnKeyStateChanged);     // Configure the callback function event on the key pressed
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyReleased(true)) {           // Steady State Key Pressed -> False = Rising Edge, True = Seady State
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyStateChanged(ButtonEvents e) {
  Serial.println("Event on Key Pressed");     // Print message event on key Pressed
}
```

### Key Release and onKeyReleased
```C
#include "RepeatButton.h"

#define buttonPin 2                     // Define the button input pin.

RepeatButton button;                    // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e); // Occurs when a key is changed

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.buttonEvents(OnKeyStateChanged);     // Configure the callback function event on the key released
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyReleased(true)) {           // Steady State Key Released -> False = Rising Edge, True = Seady State
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyStateChanged(ButtonEvents e) {
  Serial.println("Event on Key Released");    // Print message event on key Released
}
```

### Key Hold and onKeyHolding
```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t holdDelay = 3000;    // Set Hold Time 3000 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e);  // Occurs when a key is changed

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.holdDelay(holdDelay);                // Set the Hold delay
  button.buttonEvents(OnKeyStateChanged);     // Configure the callback function event on the key holding
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyHolding(true)) {            // Steady State Key Holding -> False = Rising Edge, True = Seady State
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyStateChanged(ButtonEvents e) {
  Serial.println("Event on Key Hold");        // Print message event on key Hold
}
```

### Key Repeat and onKeyRepeating

```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t repeatDelay = 500;   // Set Delay 500 milliseconds
const uint16_t repeatRate = 200;    // Set Repeat rate 200 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e);  // Occurs when a key is changed

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP);   // Set the button mode
  button.repeatDelay(repeatDelay, repeatRate);  // Set the Hold delay
  button.buttonEvents(OnKeyStateChanged);       // Configure the callback function event on the key holding
  pinMode(LED_BUILTIN, OUTPUT);                 // Set the LED_BUILTIN mode

}

void loop() {
  button.repeatButton();                        // Executing the Repeat button function
  if (button.isRepeating()) {                   // Steady State Key Repeating -> False = Rising Edge, True = Seady State
    digitalWrite(LED_BUILTIN, HIGH);            // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);             // Turned LED OFF
  }
}

void OnKeyStateChanged(ButtonEvents e) {
  switch (e) {
    case PRESS:
      Serial.println("Event on Key Pressed");   // Print message event on key pressed
      break;
    case REPEAT
      Serial.println("Event on Key Repeat");    // Print message event on key repeat                          
      break;
  }
}
```