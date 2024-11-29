#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_AHT10.h>

#define SCREEN_WIDTH 128  // Šířka displeje v pixelech
#define SCREEN_HEIGHT 64  // Výška displeje v pixelech

// Definice pinů
#define OLED_MOSI 23    // Pin pro MOSI
#define OLED_SCK 18     // Pin pro SCK
#define OLED_DC 21      // Pin pro Data/Command
#define OLED_CS 22      // Pin pro Chip Select
#define OLED_RESET 15   // Pin pro reset

// Inicializace displeje
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_SCK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
    // Nastavení displeje
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D); // 0x3D je adresa pro 128x64 displej
    display.clearDisplay();  // Vyčistění displeje

    // Nastavení textových vlastností
    display.setTextSize(1);  // Velikost textu
    display.setTextColor(WHITE);  // Barva textu
    display.setCursor(0, 0);  // Nastavení kurzoru na začátek displeje

    // Zobrazení textu na displeji
    display.println("Ahoj, světe!");  // Text, který se má zobrazit
    display.display();  // Odeslání obsahu do displeje
}

void loop() {
    // Hlavní smyčka (můžete přidat další kód pro aktualizaci displeje)
}
