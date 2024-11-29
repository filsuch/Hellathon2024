#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <MPU9250.h>

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

// Nastavení RGB LED
#define RED_PIN 25
#define GREEN_PIN 26
#define BLUE_PIN 27

// Inicializace MPU9250
MPU9250 mpu;

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
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    setRGB(0, 0, 0); // Vypnout LED

    // Inicializace MPU9250
    Wire.begin();
    mpu.begin();
    mpu.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    mpu.setAccelRange(MPU9250::ACCEL_RANGE_2G);
    mpu.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_10HZ);

    // Zobrazení úvodního textu
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("DHT11 Sensor");
    display.display();
    delay(2000);
}

void loop() {
    // Kontrola pohybu
    VectorFloat acceleration = mpu.readAccelerometer();
    int movement = sqrt(acceleration.XAccel * acceleration.XAccel + 
                        acceleration.YAccel * acceleration.YAccel + 
                        acceleration.ZAccel * acceleration.ZAccel);

    // Pokud je pohyb větší než threshold
    if (movement > motionThreshold) {
        isSleeping = false;
        displayValues();
        setRGB(255, 0, 0); // Změnit barvu na červenou
    } else {
        isSleeping = true;
        setRGB(0, 0, 0); // Vypnout LED
        display.clearDisplay();
        display.display();
    }

    // Čekání před dalším čtením
    delay(200);
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

void setRGB(int red, int green, int blue) {
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
}
