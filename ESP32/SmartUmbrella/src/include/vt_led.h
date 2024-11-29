#pragma once
#include <Arduino.h>
// Nastavení RGB LED
#define RED_PIN 4
#define GREEN_PIN 15
#define BLUE_PIN 19


class SmartVTLed {
public:
    static void begin();
    static void set_color(int r, int g, int b);

private:
    static const int PWM_CHANNEL_RED = 0;
    static const int PWM_CHANNEL_GREEN = 1;
    static const int PWM_CHANNEL_BLUE = 2;
    static const int PWM_FREQUENCY = 5000;  // 5 kHz
    static const int PWM_RESOLUTION = 8;   // 8bitové rozlišení
};

