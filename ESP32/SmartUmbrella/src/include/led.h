#pragma once

#include <Adafruit_NeoPixel.h>

#define PIN            13    // Pin, na kterém je připojen Data pin LED pásku
#define NUMPIXELS      11   // Počet LED na pásku


class SmartLed
{
private:

    static inline Adafruit_NeoPixel* strip = NULL;
    
public:
    static void begin();
    static void loop();

};


