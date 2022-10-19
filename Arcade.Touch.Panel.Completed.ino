#include "Keyboard.h"

// --Input Pins--
//const int startButton = 18;           //First Button Pin (Digital)
//const int startLED = 8;               //First LED Pin (Digital)
const int totalButtons = 8;             //Total Buttons
const int buttonPins[] = {10, 16, 14, 15, 18, 19, 20, 21};
const int LEDPins[] = {9, 8, 7, 6, 5, 4, 3, 2};
// --Input Pins--

const int Bsmoothing = 50;            // Repeat speed of keys
const int clickDelay = 150;           // Pause Between Clicks
const int long LEDTimer = 100000;           // Time until LEDs Auto Off
int Bsmoothingindex = 0;              // Index of button smoother
int currentButtonState = 0;           // Current Button State
int currentButtonTotal = 0;           // Smoothed State
int long currentLEDState = 0;              // Current LED State
int long currentLEDTime = 0;               // Current LED Time
int lastButtonState[totalButtons][Bsmoothing];    // Last state of the buttons - number of interations
int smoothedButtonState[totalButtons];// Current Button State after smoothing
int lastLEDState[totalButtons];       // Last state of the LEDs

void setup() {
  Serial.begin(9600);

  // --Initialize Button Pins--
  pinMode(0, INPUT_PULLUP); //-- Escape Key!--

  for (int initPinIndex = 0; initPinIndex < totalButtons; initPinIndex++)
  {
    pinMode(buttonPins[initPinIndex], INPUT_PULLUP);
  }
  // --Initialize Button Pins--

  // --Initialize LED Pins--
  for (int initPinIndex = 0; initPinIndex < totalButtons; initPinIndex++)
  {
    pinMode(LEDPins[initPinIndex], OUTPUT);
  }
  // --Initialize Button Pins--

  // --Button Array Init--
  for (int thisReading = 0; thisReading < totalButtons; thisReading++)
  {
    for (int thatReading = 0; thatReading < Bsmoothing; thatReading++)
    {
      lastButtonState[thisReading][thatReading] = 0;
    }
    lastLEDState[thisReading] = 0;
    smoothedButtonState[totalButtons] = 0;
  }
  // --Button Array Init--

  Keyboard.begin();

}

void loop() {
  // --Escape Key!--
  while (digitalRead(0) == LOW)
  {
    Keyboard.releaseAll();
    currentLEDTime = LEDTimer;
    delay(1000);
    Serial.print("Esc State: ");
    Serial.println(digitalRead(0));
  }
  // --Escape Key!--

  buttonPress();
  cycleLEDs();

  // --Read pin values for buttons--
  for (int Bindex = 0; Bindex < totalButtons; Bindex++)
  {
    currentButtonState = digitalRead(buttonPins[Bindex]);
    if (currentButtonState != lastButtonState[Bindex][Bsmoothingindex])
    {
      lastButtonState[Bindex][Bsmoothingindex] = currentButtonState;
    }
  }
  // --Read pin values for buttons--

  Bsmoothingindex++;
  if (Bsmoothingindex > Bsmoothing)
  {
    Bsmoothingindex = 0;
  }
}

void buttonPress()
{
  // --Iterate lastButtonState[][], total, average, populate smoothedButtonState[]--
  for (int Bindex = 0; Bindex < totalButtons; Bindex++)
  {
    currentButtonTotal = 0;

    for (int Sindex = 0; Sindex < Bsmoothing; Sindex++)
    {
      currentButtonTotal = currentButtonTotal + lastButtonState[Bindex][Sindex];
    }

    if ((currentButtonTotal / Bsmoothing) == 0)
    {
      smoothedButtonState[Bindex] = 0;
    }
    else
    {
      smoothedButtonState[Bindex] = 1;
    }
  }
  // --Iterate lastButtonState[][], total, average, populate smoothedButtonState[]--

  // --Iterate smoothedButtonState[], update lastLEDState[], send Keyboard.Press()--
  for (int Bindex = 0; Bindex < totalButtons; Bindex++)
  {
    if (smoothedButtonState[Bindex] == 1)
    {
      smoothedButtonState[Bindex] = 0;
      currentLEDTime = 0;                   //  Auto LED Off reset
      for (int Rindex = 0; Rindex < Bsmoothing; Rindex++)
      {
        lastButtonState[Bindex][Rindex] = 0;
      }
      switch (Bindex) {
        case 0:     // Winamp Previous  (CTRL+SHIFT+A)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('A');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
        case 1:     // Winamp Play/Pause/Stop  (CTRL+SHIFT+G)/(CTRL+SHIFT+H)/(CTRL+SHIFT+D)
          if (lastLEDState[Bindex] == 0)
          {
            lastLEDState[Bindex] = 1;
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('G');
            Keyboard.releaseAll();
            //digitalWrite(LEDPins[Bindex], HIGH);
            delay(clickDelay);
            break;
          }
          if (lastLEDState[Bindex] == 1)
          {
            lastLEDState[Bindex] = 0;
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('D');
            Keyboard.releaseAll();
            //digitalWrite(LEDPins[Bindex], LOW);
            delay(clickDelay);
            break;
          }
          break;
        case 2:     // Winamp Next  (CTRL+SHIFT+F)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('F');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
        case 3:     // Pending | Pause (P)
          //Keyboard.press(KEY_LEFT_CTRL);
          //Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('P');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
        case 4:     // Volume Down  (CTRL+SHIFT+-)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('-');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
        case 5:     // Volume Up  (CTRL+SHIFT+=)
          delay(clickDelay);
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('=');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
        case 6:     // Mute      (CTRL+SHIFT+M)/(CTRL+SHIFT+N)
          delay(clickDelay);
          if (lastLEDState[Bindex] == 0) {
            lastLEDState[Bindex] = 1;
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('M');
            Keyboard.releaseAll();
            delay(clickDelay);
            break;
          }
          if (lastLEDState[Bindex] == 1) {
            lastLEDState[Bindex] = 0;
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('N');
            Keyboard.releaseAll();
            delay(clickDelay);
            break;
          }
          break;
        case 7:     // Pending  (Pause) (P)
          delay(clickDelay);
          //Keyboard.press(KEY_LEFT_CTRL);
          //Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('P');
          Keyboard.releaseAll();
          digitalWrite(LEDPins[Bindex], HIGH);
          delay(clickDelay);
          digitalWrite(LEDPins[Bindex], LOW);
          delay(clickDelay);
          break;
      }
    }
    // --Iterate smoothedButtonState[], update lastLEDState[], send Keyboard.Press()--
  }


}


void cycleLEDs()
{
  // --Auto Off All LEDs
  currentLEDTime = currentLEDTime + 1;
  Serial.print("LED Timer: ");
  Serial.println(currentLEDTime);
  Serial.println(LEDTimer);

  if (currentLEDTime > LEDTimer)
  {
    for (int Tindex = 0; Tindex < totalButtons; Tindex++)
    {
      digitalWrite(LEDPins[Tindex], LOW);
    }
    return;
  }
  // --Auto Off All LEDs

  else {
    // --Set LED Status for All--
    for (int Lindex = 0; Lindex < totalButtons; Lindex++) {
      currentLEDState = digitalRead(LEDPins[Lindex]);
      if (currentLEDState != lastLEDState[Lindex]) {
        if (lastLEDState[Lindex] == 0) {
          digitalWrite(LEDPins[Lindex], LOW);
        }
        if (lastLEDState[Lindex] == 1) {
          digitalWrite(LEDPins[Lindex], HIGH);
        }
      }
      //Serial.print("LED State: ");
      //Serial.println(lastLEDState[Lindex]);
    }
    // --Set LED Status for All--
  }
}
