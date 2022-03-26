#include "constants.h"
#include "state.h"
#include <Arduino.h>
#include <Wire.h>

// Variables
int state;

void setup()
{
    // Setup LEDs
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);

    // Setup Buttons
    pinMode(BUTTON_YELLOW, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_BLUE, INPUT_PULLUP);

    // Turn builtin LED off by default
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Set beginning state
    state = STATE_INITIALIZE_ADDRESS;
}

void loop()
{

    switch (state) {
    case STATE_INITIALIZE_ADDRESS:
        state = initializeAddress();
        break;
    case STATE_INITIALIZE:
        state = initialize();
        break;
    case STATE_SETUP:
        state = setupModule();
        break;
    case STATE_READY:
        state = ready();
        break;
    case STATE_RUNNING:
        state = running();
        break;
    case STATE_FINISHED:
        state = finished();
        break;
    }
    // TODO do stuff needed in every loop, like handling leds and reading buttons
}
