#pragma once

#include <Adafruit_NeoPixel.h>

#define PIN            13    // Pin, na kterém je připojen Data pin LED pásku
#define NUMPIXELS      11   // Počet LED na pásku


class SmartLed
{
private:

    static inline Adafruit_NeoPixel* strip = NULL;

    static inline int strip_color_r = 0;
    static inline int strip_color_g = 0;
    static inline int strip_color_b = 0;

    static void update_led();
    
public:
    static void begin();
    static void loop();
    static void change_color(int r, int g, int b);
    

};


