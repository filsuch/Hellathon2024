#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include "include/led.h"
#include "include/vt_led.h"

// Pin Definitions
#define BUTTON_PIN 26       // Button input pin
#define DHT_PIN 14          // DHT11 data pin
#define RGB_STRIP_PIN 13    // RGB LED strip data pin

// OLED Pin Definitions
#define OLED_MOSI 23
#define OLED_SCK 18
#define OLED_DC 21
#define OLED_CS 22
#define OLED_RESET 15

// Device Configurations
#define DHTTYPE DHT11      // DHT sensor type
#define SCREEN_WIDTH 128   // OLED display width
#define SCREEN_HEIGHT 64   // OLED display height
#define NUM_PIXELS 11       // Number of pixels in RGB strip

// Object Initializations
DHT dht(DHT_PIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_SCK, OLED_DC, OLED_RESET, OLED_CS);


// Global Variables
unsigned long buttonPressTime = 1;

bool displayEnabled = true;
bool ledEnable = false;



#define BUTTON_PIN 26  // Pin pro tlačítko


unsigned long lastPressTime = 0;  // Čas posledního stisku
unsigned long debounceDelay = 50;  // Čas na odstranění šumu (debouncing)
unsigned long doubleClickInterval = 400;  // Maximální čas mezi dvěma kliknutími pro detekci double-clicku
int buttonState = 0;  // Aktuální stav tlačítka
int lastButtonState = 0;  // Předchozí stav tlačítka

bool detectDoubleClick() {
  static unsigned long lastPressTimeLocal = 0;  // Lokální čas pro detekci double-clicku
  bool doubleClickDetected = false;
  
  buttonState = digitalRead(BUTTON_PIN);  // Čtení aktuálního stavu tlačítka

  // Kontrola, zda došlo k přechodu z nízkého na vysoký stav (stisknutí tlačítka)
  if (buttonState == HIGH && lastButtonState == LOW) {
    unsigned long currentTime = millis();  // Získání aktuálního času
    if (currentTime - lastPressTimeLocal <= doubleClickInterval) {
      // Pokud mezi dvěma stisky uplynulo méně než doubleClickInterval, je to dvojité kliknutí
      doubleClickDetected = true;
    }
    lastPressTimeLocal = currentTime;  // Uložení času posledního stisku
    delay(debounceDelay);  // Debouncing - krátké zpoždění, aby se zabránilo opakovanému detekování stejného stisku
  }

  lastButtonState = buttonState;  // Aktualizace předchozího stavu tlačítka
  
  return doubleClickDetected;
}


void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);

  // Initialize Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize DHT Sensor
  dht.begin();

  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  SmartLed::begin();
  SmartVTLed::begin();

  SmartLed::change_color(255, 255, 255);


  
  


}

void updateDisplay() {
    if(displayEnabled) {
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0,0);
        display.print("Temp: ");
        display.print(temperature);
        display.print(" C");
        display.setCursor(0,10);
        display.print("Humidity: ");
        display.print(humidity);
        display.print(" %");
        display.display();
    } else {
        display.clearDisplay();
        display.display();
    }
}

void handleButtonPress() {
    unsigned long currentTime = millis();  // Získání aktuálního času
    bool buttonState = digitalRead(BUTTON_PIN);  // Stav tlačítka

    // Zpracování dlouhého stisku (držení tlačítka)
    if (buttonState == LOW) {  // Pokud je tlačítko stisknuto (LOW)
        if (buttonPressTime == 0) {
            buttonPressTime = currentTime;  // Zaznamenání času při prvním stisknutí
        } else if (currentTime - buttonPressTime >= 1000) {  // Pokud tlačítko držíš déle než 1 sekundu
            displayEnabled = !displayEnabled;  // Změna stavu displeje

            if(displayEnabled) {
                SmartVTLed::set_color(255,0, 0);
            } else {
                SmartVTLed::set_color(0,0, 0);
            }

            Serial.print("Displej nastaven na: ");
            Serial.println(displayEnabled ? "ON" : "OFF");
            buttonPressTime = 0;  // Resetování času pro další stisk
        }
    } else {  // Pokud tlačítko není stisknuto
        buttonPressTime = 0;  // Resetování času pro dlouhý stisk
    }

}


void loop() {


    if (detectDoubleClick()) {
        Serial.println("Dvojklik detekován!");
        ledEnable = !ledEnable;

        if(ledEnable) {
            SmartLed::off();
        } else {
            SmartLed::on();
        }

    }

    handleButtonPress();


  

    
    updateDisplay();

    
  
}