#include <Control_Surface.h> // https://github.com/tttapa/Control-Surface

USBMIDI_Interface midi;

CCButton button[] = {
  {2, {MIDI_CC::General_Purpose_Controller_1, Channel_2}},
  {3, {MIDI_CC::General_Purpose_Controller_2, Channel_2}},
  {4, {MIDI_CC::General_Purpose_Controller_3, Channel_2}},
  {5, {MIDI_CC::General_Purpose_Controller_4, Channel_2}},
  {6, {MIDI_CC::General_Purpose_Controller_5, Channel_2}},
  {7, {MIDI_CC::General_Purpose_Controller_6, Channel_2}},
  {8, {MIDI_CC::General_Purpose_Controller_7, Channel_2}},
  {9, {MIDI_CC::General_Purpose_Controller_8, Channel_2}},
};

CCPotentiometer potentiometer {
  A1, {MIDI_CC::Modulation_Wheel, Channel_2},
};

const int numButtons = 5;
const int buttonPins[numButtons] = {2, 3, 4, 5, 6};
const int ledPins[numButtons] = {10, 16, 14, 15, A0};

int activeLed = 0;

bool main_flag = 0;
bool flag = 0;

uint32_t btnTimer = 0;
byte debounce_time = 60;

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  digitalWrite(ledPins[activeLed], HIGH);
  Control_Surface.begin(); // Initialize Control Surface
}

void loop() {
  if (!digitalRead(8) && !main_flag && millis() - btnTimer > debounce_time or !digitalRead(9) && !main_flag && millis() - btnTimer > debounce_time) {
    main_flag = 1;
    btnTimer = millis();
    digitalWrite(ledPins[activeLed], LOW);
    activeLed = 0;
    digitalWrite(ledPins[activeLed], HIGH);
  }
  if (digitalRead(8) && main_flag && millis() - btnTimer > debounce_time or digitalRead(9) && main_flag && millis() - btnTimer > debounce_time) {
    main_flag = 0;
    btnTimer = millis();
  }

  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW && millis() - btnTimer > debounce_time) {
      if (activeLed != -1) {
        digitalWrite(ledPins[activeLed], LOW);
      }
      activeLed = i;
      digitalWrite(ledPins[i], HIGH);
      btnTimer = millis();
    }
  }

  Control_Surface.loop(); // Update the Control Surface
}
