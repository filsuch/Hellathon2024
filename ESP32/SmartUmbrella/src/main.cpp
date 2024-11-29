#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <MPU9250.h>

#include "./include/vt_led.h"

// Definice pinů pro displej
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 23
#define OLED_SCK 18
#define OLED_DC 21
#define OLED_CS 22
#define OLED_RESET 15

// Inicializace displeje
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_SCK, OLED_DC, OLED_RESET, OLED_CS);

// Nastavení DHT11
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);




// Nastavení uspávacího režimu
bool isSleeping = false;
const int motionThreshold = 100; // Minimální hodnota pohybu pro aktivaci

void setup() {
    // Inicializace sériové komunikace
    Serial.begin(115200);

    // Inicializace OLED displeje
    display.begin(SSD1306_SWITCHCAPVCC, OLED_CS);
    display.clearDisplay();

    // Inicializace DHT11
    dht.begin();

    // Inicializace RGB LED
    SmartVTLed::begin();
    SmartVTLed::set_color(255, 0, 0);


    // Inicializace MPU9250
    Wire.begin();

    

    // Zobrazení úvodního textu
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("DHT11 Sensor");
    display.display();
    delay(2000);
}

void loop() {

    SmartVTLed::set_color(255, 0, 0); // Red Color
    delay(500);
       SmartVTLed::set_color(0, 255, 0); // Red Color
    delay(500);
       SmartVTLed::set_color(0, 0, 255); // Red Color
    delay(500);


}

void displayValues() {
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
}
