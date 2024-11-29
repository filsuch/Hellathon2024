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
  // Nastavení sériové komunikace
  Serial.begin(115200);
  
  // Inicializace displeje
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);  
  display.setCursor(0,0);
  
  // Inicializace senzoru AHT10
  if (!aht10.begin()) {
    Serial.println("Nemohu najít AHT10 sensor!");
    while (1);
  }
}

void loop() {
  // Získání dat ze senzoru
  float temperature = aht10.readTemperature();
  float humidity = aht10.readHumidity();

  // Zobrazení dat na sériovém monitoru
  Serial.print("Teplota: ");
  Serial.print(temperature);
  Serial.print(" °C, Vlhkost: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Zobrazení dat na OLED displeji
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Teplota: ");
  display.print(temperature);
  display.println(" °C");
  display.print("Vlhkost: ");
  display.print(humidity);
  display.println(" %");
  display.display();
  
  delay(2000); // Aktualizace každé 2 sekundy
}