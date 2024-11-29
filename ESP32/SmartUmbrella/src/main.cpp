#include <Arduino.h>
#include "./modules/include/display.h"

void setup() {
  //Inicializace serial
  Serial.begin(115200);
  //Begin funkce displeje
  SmartDisplay::begin();

}

void loop() {
  //Loop funkce displeje 
  SmartDisplay::loop();
}


