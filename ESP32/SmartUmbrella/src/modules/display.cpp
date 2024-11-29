#include "./include/display.h"


void SmartDisplay::begin() {
    //Vytvoření nové třídy displeje
    SmartDisplay::display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
    //Spuštění funkce pro inicializaci displeje
    SmartDisplay::display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
}


void SmartDisplay::power_on_display() {

}

void SmartDisplay::power_off_display() {

}