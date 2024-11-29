#pragma once
//Knihovny pro displej 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "./main.h"


class SmartDisplay {
private:
    //Deklarace statické proměnné pro uložení třídy pro displej
    static inline Adafruit_SSD1306* display = NULL;
    //Deklarace statické proměnné pro uložení on/off displeje
    static inline bool display_power = true;

public: 
    //Deklarace statické funkce pro inicializaci displeje
    void static begin();
    //Deklarace statické funkce pro aktualizaci 
    void static loop();
    /**
     * @brief Deklarace statické funkce pro změnu on/off displeje
     * 
     * @param state Nový stav displeje 
     */
    void static change_display_state(bool state);
    //Zapnutí displeje
    void static power_on_display();
    //Vypnutí displeje
    void static power_off_display();
};