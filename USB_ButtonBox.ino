//
// Zoom Buttons
// inspired by https://www.instructables.com/Zoom-Control-Box/
//

#include "Keyboard.h"

// Define Arduino pin numbers for buttons and LEDs
#define LED 13
#define LANG 2  // Language select (connect button to GND to switch to US keyboard)
#define BTN1 4  // Alt-F2: Gallery view
#define BTN2 5  // Alt-F1: Speaker view
#define BTN3 6  // Alt-Y: Raise Hand
#define BTN4 7  // Alt-A: Mute self
#define BTN5 8  // Alt-F: Full screen
#define BTN6 9  // Alt-S: Share screen
#define NUMBUTTONS 6
int buttons[NUMBUTTONS] = {BTN1, BTN2, BTN3, BTN4, BTN5, BTN6};
unsigned long btntime[NUMBUTTONS];
boolean btnpress[NUMBUTTONS];


char line[80];
unsigned long t;
int n;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  for (int i=0; i < 3; i++) {
  digitalWrite(LED, HIGH); delay(20);
  digitalWrite(LED, LOW); delay(200);
  digitalWrite(LED, HIGH); delay(20);
  digitalWrite(LED, LOW); delay(200);
  digitalWrite(LED, HIGH); delay(20);
  digitalWrite(LED, LOW); delay(500);
  }

  for (int i = 0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    btntime[i] = 0;
    btnpress[i] = false;
  }

  pinMode(LANG, INPUT_PULLUP); // Language select HIGH = DE, LOW = US

  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    if (!digitalRead(buttons[i])) {
      // Button pressed (negative logic)
      if (btntime[i] == 0) {
        // Button has just been pressed
        btntime[i] = millis();
      }
      else {
        // Button is still pressed
        if (millis() - btntime[i] > 20 && !btnpress[i]) {
          // This is not just a glitch          
          btnpress[i] = true;
          // Now do your stuff!
          digitalWrite(LED, HIGH);
          switch (i) {
          case 0: // Alt-F2: Gallery view
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.write(KEY_F2);
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case 1: // Alt-F1: Speaker view
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.write(KEY_F1);
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case 2: // Alt-Y: Raise / lower hand be careful on DE kbd Y & Z are changed to US kbd
            Keyboard.press(KEY_LEFT_ALT);            
            if (digitalRead(LANG) == HIGH) Keyboard.write('z'); // Check which language is selected
              else Keyboard.write('y');
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case 3: // Alt-A: Mute self
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.write('a');
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case 4: // Alt-F: Full screen
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.write('f');
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case 5: // Alt-S: Share screen
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.write('s');
            Keyboard.release(KEY_LEFT_ALT);
            break;
          }  
        }
      }
    }
    else {
      // Button not pressed
      if (btntime[i] != 0) {
        // Looks like it's just been released
        digitalWrite(LED, LOW);
        btntime[i] = 0;
        btnpress[i] = false;
      }
    }
  }
}
