#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
 #include <Adafruit_Sensor.h>

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



// Nastavení DHT11
#define DHTPIN 14         // Pin, na který je připojen DHT11
#define DHTTYPE DHT11     // Typ senzoru
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    // Inicializace sériové komunikace
    Serial.begin(115200);
    
    // Inicializace OLED displeje
    display.begin(SSD1306_SWITCHCAPVCC, OLED_CS);  // Upravte inicializaci pro SPI
    display.clearDisplay();
    
    // Inicializace DHT11
    dht.begin();
    
    // Zobrazení úvodního textu
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("DHT11 Sensor");
    display.display();
    delay(2000);
}

void loop() {
    // Načtení hodnot teploty a vlhkosti
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Zkontrolujte, zda nedošlo k chybě při načítání dat
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Error reading DHT");
        display.display();
        return;
    }

    // Zobrazení hodnot na OLED displeji
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Humidity: ");
    display.print(humidity);
    display.print(" %");
    
    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(temperature);
    display.print(" *C");
    
    display.display();

    // Čekání před dalším čtením
    delay(2000);
}