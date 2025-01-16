#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include "include/led.h"
#include "include/vt_led.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Pin Definitions
#define BUTTON_PIN 26 // Button input pin
#define DHT_PIN 16    // DHT11 data pin

// OLED Pin Definitions
#define OLED_MOSI 23
#define OLED_SCK 18
#define OLED_DC 21
#define OLED_CS 22
#define OLED_RESET 15

// Device Configurations
#define DHTTYPE DHT11    // DHT sensor type
#define SCREEN_WIDTH 128 // OLED display width
#define SCREEN_HEIGHT 64 // OLED display height
#define NUM_PIXELS 11    // Number of pixels in RGB strip

#define BATTERY_VOLTAGE_READ_PIN 34

#define SVETLO_LED 2

// Object Initializations
DHT dht(DHT_PIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_SCK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

SmartLed *led_1 = new SmartLed();
SmartLed *led_2 = new SmartLed();

// Global Variables
unsigned long buttonPressTime = 1;

bool displayEnabled = true;
bool ledEnable = false;

#define BUTTON_PIN 26 // Pin pro tlačítko

unsigned long lastPressTime = 0;         // Čas posledního stisku
unsigned long debounceDelay = 50;        // Čas na odstranění šumu (debouncing)
unsigned long doubleClickInterval = 400; // Maximální čas mezi dvěma kliknutími pro detekci double-clicku
int buttonState = 0;                     // Aktuální stav tlačítka
int lastButtonState = 0;                 // Předchozí stav tlačítka

unsigned long lastZeroTime = 0;           // Čas poslední detekce nulového zrychlení
const unsigned long thresholdTime = 5000; // 1 minuta v milisekundách
bool isZeroAccelDetected = false;         // Flag pro detekci nulového zrychlení

bool detectDoubleClick()
{
    static unsigned long lastPressTimeLocal = 0; // Lokální čas pro detekci double-clicku
    bool doubleClickDetected = false;

    buttonState = digitalRead(BUTTON_PIN); // Čtení aktuálního stavu tlačítka

    // Kontrola, zda došlo k přechodu z nízkého na vysoký stav (stisknutí tlačítka)
    if (buttonState == HIGH && lastButtonState == LOW)
    {
        unsigned long currentTime = millis(); // Získání aktuálního času
        if (currentTime - lastPressTimeLocal <= doubleClickInterval)
        {
            // Pokud mezi dvěma stisky uplynulo méně než doubleClickInterval, je to dvojité kliknutí
            doubleClickDetected = true;
        }
        lastPressTimeLocal = currentTime; // Uložení času posledního stisku
        delay(debounceDelay);             // Debouncing - krátké zpoždění, aby se zabránilo opakovanému detekování stejného stisku
    }

    lastButtonState = buttonState; // Aktualizace předchozího stavu tlačítka

    return doubleClickDetected;
}

void setup()
{
    // Initialize Serial Communication
    Serial.begin(115200);

    // Initialize Button
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    pinMode(2, OUTPUT);
    pinMode(34, INPUT);
    digitalWrite(2, 1);

    pinMode(DHT_PIN, INPUT_PULLUP);
    // Initialize DHT Sensor
    dht.begin();

    // Initialize OLED Display
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    led_1->begin(PIN);
    led_2->begin(PIN_2);

    
    SmartVTLed::begin();
    SmartVTLed::set_color(0, 0, 255);
    
    led_1->change_color(255, 255, 255);
    led_2->change_color(255, 255, 255);

    Wire.begin(25, 33);

    if (!accel.begin()) {
        Serial.println("No valid sensor found");
        while (1);
    }
}

void updateDisplay()
{
    if (displayEnabled)
    {
        int raw = analogRead(34);
        float pinVoltage = raw * (3.3 / 4095.0); 
        float batteryVoltage = pinVoltage * (3.6 / 1.72); 

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 30);
        display.print("Baterka: ");
        display.print(batteryVoltage);
        display.print(" V");
    
        display.display();
    }
    else
    {
        display.clearDisplay();
        display.display();
    }
}

void handleButtonPress()
{
    unsigned long currentTime = millis();       // Získání aktuálního času
    bool buttonState = digitalRead(BUTTON_PIN); // Stav tlačítka

    // Zpracování dlouhého stisku (držení tlačítka)
    if (buttonState == LOW)
    { // Pokud je tlačítko stisknuto (LOW)
        if (buttonPressTime == 0)
        {
            buttonPressTime = currentTime; // Zaznamenání času při prvním stisknutí
        }
        else if (currentTime - buttonPressTime >= 1000)
        {                                     // Pokud tlačítko držíš déle než 1 sekundu
            displayEnabled = !displayEnabled; // Změna stavu displeje

            Serial.print("Displej nastaven na: ");
            Serial.println(displayEnabled ? "ON" : "OFF");
            buttonPressTime = 0; // Resetování času pro další stisk
        }
    } else {          
        buttonPressTime = 0; // Resetování času pro dlouhý stisk
    }
}

void loop()
{

    sensors_event_t event;

    accel.getEvent(&event);

    Serial.println(dht.readTemperature());

    // Detekce nulového zrychlení
    if (fabs(event.acceleration.x) < 0.01 && fabs(event.acceleration.y) < 0.01 && fabs(event.acceleration.z) < 0.01)
    {
        // Zrychlení je blízko nule, počítáme čas
        if (!isZeroAccelDetected)
        {
            lastZeroTime = millis(); // Uložíme čas první detekce
            isZeroAccelDetected = true;
        }
    }
    else
    {
        // Pokud už zrychlení není nulové, resetujeme detekci
        isZeroAccelDetected = false;
    }

    // Pokud zůstane zrychlení nulové po dobu 1 minuty, provede se akce
    if (isZeroAccelDetected && (millis() - lastZeroTime >= thresholdTime))
    {
        // Akce po 1 minutě
        Serial.println("Nulové zrychlení po dobu 1 minuty detekováno!");
        // Sem vlož akci, kterou chceš provést (např. vypnutí LED, reset systému, atd.)
        isZeroAccelDetected = false; // Reset pro další detekci
    }

    
    handleButtonPress();

    if(detectDoubleClick()){
        
    }

    updateDisplay();
}