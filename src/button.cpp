#include "constants.h"

enum ButtonState { unpressed, pressed };

ButtonState buttonStates[] = { unpressed, unpressed, unpressed, unpressed };

int lastReadStates[] = { HIGH, HIGH, HIGH, HIGH };

unsigned long lastDebounceTimes[] = { 0, 0, 0, 0 };

void handleButtons()
{
    unsigned long currentMillis = millis();
    for (int button = 0; button < 4; ++button) {
        if (lastDebounceTimes[button] + DEBOUNCE_DELAY > currentMillis) {
            continue;
        }
        int currentState = digitalRead(BUTTONS[button]);
        if (currentState != lastReadStates[button]) {
            lastDebounceTimes[button] = currentMillis;
            lastReadStates[button] = currentState;
            buttonStates[button] = currentState == HIGH ? unpressed : pressed;
        }
    }
}

int readButton()
{
    for (int button = 0; button < 4; ++button) {
        if (buttonStates[button] == pressed) {
            buttonStates[button] = unpressed;
            return button;
        }
    }
    return -1;
}