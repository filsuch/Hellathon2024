#include "./include/led.h"


void SmartLed::begin(int pin) {
    SmartLed::strip =  new Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);

    // Inicializace NeoPixel pásku
    SmartLed::strip->begin();
    SmartLed::strip->show();  // Nastaví všechny LED na "off"
}

void SmartLed::loop() { 



}

void SmartLed::update_led() {
    // Nastavení barev pro všechny LED na pásku (modrá)
    for (int i = 0; i < SmartLed::strip->numPixels(); i++) {
        SmartLed::strip->setPixelColor(i, SmartLed::strip->Color(SmartLed::strip_color_r, SmartLed::strip_color_g, SmartLed::strip_color_b));  
    }
    SmartLed::strip->show();  
}

void SmartLed::change_color(int r, int g, int b) {
    SmartLed::strip_color_r = r;
    SmartLed::strip_color_g = g;
    SmartLed::strip_color_b = b;

    SmartLed::update_led();
}


void SmartLed::on() {
    SmartLed::strip->setBrightness(255);
    SmartLed::update_led();
}

void SmartLed::off() {
    SmartLed::strip->setBrightness(0);
    SmartLed::strip->show(); 
}

