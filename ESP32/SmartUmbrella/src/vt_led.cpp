#include "./include/vt_led.h"

void SmartVTLed::begin() {
    pinMode(RED_PIN,   OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN,  OUTPUT);
}

void SmartVTLed::set_color(int r, int g, int b) {
    analogWrite(RED_PIN,  255 - r);
    analogWrite(GREEN_PIN, 255 - g);
    analogWrite(BLUE_PIN,  255 - b);
}