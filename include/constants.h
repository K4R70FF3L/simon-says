#include <Arduino.h>

#ifndef CONSTANTS
#define CONSTANTS

// LEDs
const int LED_YELLOW = 3;
const int LED_RED = 4;
const int LED_GREEN = 5;
const int LED_BLUE = 6;
const int LEDS[] = { LED_YELLOW, LED_RED, LED_BLUE, LED_GREEN };
const int STATUS_LED_RED = 11;
const int STATUS_LED_GREEN = 12;

// Buttons
const int BUTTON_YELLOW = 7;
const int BUTTON_RED = 8;
const int BUTTON_GREEN = 9;
const int BUTTON_BLUE = 10;
const int BUTTONS[] = { BUTTON_YELLOW, BUTTON_RED, BUTTON_BLUE, BUTTON_GREEN };
const int LED_BUTTON_MAPPINGS /*vowel in serial number: 1; not: 0*/[2] /*strike count:*/[3] /*ledButtonMapping:*/[4]
    = { { { 1, 2, 0, 3 }, { 3, 1, 2, 0 }, { 1, 0, 3, 2 } }, { { 3, 2, 1, 0 }, { 1, 0, 3, 2 }, { 2, 3, 1, 0 } } };

// States
const int STATE_INITIALIZE = 1;
const int STATE_SETUP = 2;
const int STATE_READY = 3;
const int STATE_RUNNING = 4;
const int STATE_FINISHED = 5;
const int STATE_INITIALIZE_ADDRESS = 6;

// Colors
const int YELLOW = 0;
const int RED = 1;
const int BLUE = 2;
const int GREEN = 3;
const int STEPS = 5;

// Misc constants
const unsigned long DEBOUNCE_DELAY = 50;
const unsigned long BLINK_DURATION = 600;
const unsigned long STRIKE_DURATION = 1000;

const byte SERIAL_VOWEL_MASK = 0b10;

const byte MODULE_STATUS_SOLVED = 0b1;
const byte MODULE_STATUS_STRIKE = 0b10;
const byte MODULE_STATUS_REQUEST_STRIKES = 0b1000;

#endif
