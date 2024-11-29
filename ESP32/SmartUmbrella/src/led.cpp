
#include "./include/led.h"



void SmartLed::begin() {
    SmartLed::strip =  new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

    // Inicializace NeoPixel pásku
    SmartLed::strip->begin();
    SmartLed::strip->show();  // Nastaví všechny LED na "off"
}

void SmartLed::loop() {
       // Nastavení barev pro všechny LED na pásku (modrá)
    for (int i = 0; i < SmartLed::strip->numPixels(); i++) {
        SmartLed::strip->setPixelColor(i, SmartLed::strip->Color(0, 0, 255));  // Modrá barva
    }
    SmartLed::strip->show();  // Aplikace změn na pásku
    delay(1000);    // Čekání 1 sekundu
    
    // Změna na červenou
    for (int i = 0; i < SmartLed::strip->numPixels(); i++) {
        SmartLed::strip->setPixelColor(i, SmartLed::strip->Color(255, 0, 0));  // Červená barva
    }
    SmartLed::strip->show();
    delay(1000);    // Čekání 1 sekundu
    
    // Změna na zelenou
    for (int i = 0; i < SmartLed::strip->numPixels(); i++) {
        SmartLed::strip->setPixelColor(i, SmartLed::strip->Color(0, 255, 0));  // Zelená barva
    }
    SmartLed::strip->show();
    delay(1000);    // Čekání 1 sekundu
}