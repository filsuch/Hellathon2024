#pragma once
#include <Arduino.h>
// Nastavení RGB LED
#define RED_PIN 34
#define GREEN_PIN 32
#define BLUE_PIN 35


class SmartVTLed
{
private:
    /* data */
public:

    static void begin();
    static void set_color(int r, int g, int b);
 
};

