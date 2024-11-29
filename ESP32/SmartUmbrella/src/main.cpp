#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include "include/led.h"

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
bool isDeviceOn = false;

bool displayEnabled = false;

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
  static unsigned long lastPressTime = 0;
  unsigned long currentTime = millis();

  // Double-click detection
  if (currentTime - lastPressTime < 300) {
    // Toggle device on/off
    isDeviceOn = !isDeviceOn;
    
    if (isDeviceOn) {
      // Turn RED when device is on

      
    } else {
      // Turn off display and RGB strip


    }
  }

  
    if (digitalRead(BUTTON_PIN) == LOW) {
    if (buttonPressTime == 0) {
        // Zaznamenáme čas prvního stisknutí tlačítka
        buttonPressTime = currentTime;
    } else if (currentTime - buttonPressTime >= 1000) {


        //Zapnuto
        SmartLed::change_color(255, 255, 255);
        displayEnabled = true;
        
        buttonPressTime = 0; // Resetujeme čas, abychom mohli detekovat další podržení
    }
    } else {
        // Pokud tlačítko není stisknuté, resetujeme čas
        buttonPressTime = 0;
    }

  lastPressTime = currentTime;
}

void loop() {
  // Button press handling
  handleButtonPress();

  // Device functionality only when turned on
  if (isDeviceOn) {

    
    updateDisplay();

    
  }
}