#pragma once

#include <Adafruit_NeoPixel.h>

#define PIN            13    // Pin, na kterém je připojen Data pin LED pásku
#define PIN_2            12    // Pin, na kterém je připojen Data pin LED pásku
#define NUMPIXELS      10   // Počet LED na pásku


class SmartLed
{
private:

    Adafruit_NeoPixel* strip = NULL;

    int strip_color_r = 0;
    int strip_color_g = 0;
    int strip_color_b = 0;
    void update_led();
    
public:
    void begin(int pin);
    void loop();
    void change_color(int r, int g, int b);

    void on();
    void off();
    

};


