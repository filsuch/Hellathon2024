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

Adafruit_AHT10 aht;

void setup() {
    Serial.begin(115200);
    
    // Inicializace displeje
    display.begin(SSD1306_I2C_ADDRESS, 0x3C); // 0x3C je běžná adresa pro OLED displej
    display.clearDisplay();  // Vyčistění displeje
    
    // Inicializace senzoru
    if (!aht.begin()) {
        Serial.println("Nepodařilo se inicializovat AHT10!");
        while (1);
    }

    display.setTextSize(1);  // Velikost textu
    display.setTextColor(WHITE);  // Barva textu
}

void loop() {
    // Čtení dat ze senzoru
    if (aht.read()) {
        float temperature = aht.getTemperature(); // Získání teploty
        float humidity = aht.getHumidity();       // Získání vlhkosti
        
        // Vyčištění displeje
        display.clearDisplay();
        
        // Zobrazení hodnot
        display.setCursor(0, 0);
        display.print("Teplota: ");
        display.print(temperature);
        display.println(" C");

        display.print("Vlhkost: ");
        display.print(humidity);
        display.println(" %");

        display.display();  // Odeslání obsahu na displej
    } else {
        Serial.println("Chyba při čtení z AHT10");
    }

    delay(2000);  // Počkat 2 sekundy před dalším měřením
}