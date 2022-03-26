#include "button.h"
#include "constants.h"
#include "led.h"
#include <Arduino.h>
#include <Wire.h>

int seed;
bool serialVowel;
byte address;
byte moduleSolved = 0;
bool strike = false;
byte strikes = 0;
int buttonsPressed = 0;
int currentSteps = 1;

bool gotConfigFromI2C = false;

int colors[STEPS];

void initializeFromI2C(int byteCount)
{
    seed = Wire.read() << 8;
    seed += Wire.read();
    serialVowel = (Wire.read() & SERIAL_VOWEL_MASK) > 0;
    randomSeed(seed);
    gotConfigFromI2C = true;
}

void getAddress(int byteCount)
{
    address = Wire.read();
    Wire.onReceive(initializeFromI2C);
    Wire.begin(address);
}

int initializeAddress()
{
    Wire.begin(8);
    Wire.onReceive(getAddress);
    return STATE_INITIALIZE;
}

void generateColors()
{
    for (int i = 0; i < STEPS; ++i) {
        colors[i] = random(4);
    }
}

int initialize()
{
    if (gotConfigFromI2C) {
        randomSeed(seed);
        generateColors();
        return STATE_SETUP;
    }
    return STATE_INITIALIZE;
}

void sendModuleStatus()
{
    byte status = moduleSolved;
    status |= MODULE_STATUS_REQUEST_STRIKES;
    if (strike) {
        status |= MODULE_STATUS_STRIKE;
        strike = false;
    }
    Wire.write(status);
}

void receiveDuringGame(int byteCount) { strikes = Wire.read(); }

bool gameStarted = false;

void sendWhenReady()
{
    sendModuleStatus();
    gameStarted = true;
    Wire.onRequest(sendModuleStatus);
}

const int* getButtonLedMapping() { return LED_BUTTON_MAPPINGS[serialVowel ? 1 : 0][strikes]; }

int setupModule()
{
    Wire.onRequest(sendWhenReady);
    Wire.onReceive(receiveDuringGame);
    return STATE_READY;
}

int ready()
{
    if (gameStarted) {
        resetTime();
        return STATE_RUNNING;
    }
    return STATE_READY;
}

int running()
{
    int button = readButton();
    if (button >= 0) {
        if (getButtonLedMapping()[colors[buttonsPressed]] == button) {
            ++buttonsPressed;
            if (buttonsPressed == currentSteps) {
                ++currentSteps;
                resetTime();
                buttonsPressed = 0;
                if (currentSteps > STEPS) {
                    setSolvedLed();
                    moduleSolved = MODULE_STATUS_SOLVED;
                    return STATE_FINISHED;
                }
            }
        } else {
            strike = true;
            setStrikeLed();
            currentSteps = 1;
            buttonsPressed = 0;
            generateColors();
            resetTime();
        }
    }
    handleLeds(colors, currentSteps, buttonsPressed > 0);
    handleButtons();

    return STATE_RUNNING;
}

int finished() { return STATE_FINISHED; }
