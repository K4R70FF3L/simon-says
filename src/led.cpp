#include "constants.h"

long startTime = 0;

void resetTime() { startTime = millis(); }

unsigned long strikeStarted = 0;
bool solvedLed = false;

void setStrikeLed() { strikeStarted = millis(); }

void setSolvedLed() { solvedLed = true; }

void handleStatusLed()
{
    digitalWrite(STATUS_LED_RED, LOW);
    digitalWrite(STATUS_LED_GREEN, LOW);
    if (solvedLed) {
        digitalWrite(STATUS_LED_GREEN, HIGH);
    } else {
        if (millis() < strikeStarted + STRIKE_DURATION) {
            digitalWrite(STATUS_LED_RED, HIGH);
        }
    }
}

void handleLeds(int colors[], int currentSteps, bool buttonPressed)
{
    if (buttonPressed) {
        for (int index = 0; index < 4; ++index) {
            analogWrite(LEDS[index], LED_OFF);
        }
    } else {
        unsigned long timeWithinCycle
            = (millis() - startTime) % (BLINK_DURATION * currentSteps * 2 + BLINK_DURATION * 2);
        int currentColor = timeWithinCycle / (BLINK_DURATION * 2);
        bool ledOn = (timeWithinCycle % (BLINK_DURATION * 2)) <= BLINK_DURATION;
        for (int index = 0; index < 4; ++index) {
            if (index == colors[currentColor] && ledOn && currentColor < currentSteps) {
                digitalWrite(LEDS[index], HIGH);
            } else {
                analogWrite(LEDS[index], LED_OFF);
            }
        }
    }

    handleStatusLed();
}