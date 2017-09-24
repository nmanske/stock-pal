#include <Arduino.h>

#include "LED.h"
#include "Stock.h"

#define RED_PIN 16
#define GREEN_PIN 0
#define BLUE_PIN 2

void initLED(void) {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void setLED(Trend trend) {
    int red = 0, blue = 0, green = 0;
    if (trend == NO_CHANGE) {
        blue = 255;
    } else if (trend == INCREASE) {
        green = 255;
    } else if (trend == DECREASE) {
        red = 255;
    }
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);  
}
