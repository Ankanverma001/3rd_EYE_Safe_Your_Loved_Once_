/*
  3rd Eye Smartwatch Firmware
  Author : Ankan Verma
  Version: 1.0
  License: MIT
*/

// ========== Libraries ==========
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30105.h"

// ========== OLED ==========
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ========== MAX30102 ==========
MAX30105 particleSensor;

// ========== GPS & GSM ==========
SoftwareSerial sim800l(2, 3); // RX, TX (for GSM SIM800L)
SoftwareSerial gpsSerial(4, 5); // RX, TX (for GPS)
TinyGPSPlus gps;

// ========== Pins ==========
#define SOS_BUTTON 7
#define BUZZER     8
#define CAM_BUTTON 9

// ========== Global Variables ==========
unsigned long lastHealthRead = 0;
const unsigned long healthInterval = 60000; // 1 minute

// ========== Setup ==========
void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);
  gpsSerial.begin(9600);

  pinMode(SOS_BUTTON, INPUT_PULLUP);
  pinMode(CAM_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop if OLED fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("3rd Eye Watch Booting...");
  display.display();
  delay(2000);

  // MAX30102 init
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    display.println("MAX30102 Not Found!");
    display.display();
    while (true);
  }
  particleSensor.setup();

  initGSM();
}

// ========== Main Loop ==========
void loop() {
  readGPS();
  readHealthSensor();

  if (digitalRead(SOS_BUTTON) == LOW) {
    triggerSOS();
    delay(2000);
  }

  if (digitalRead(CAM_BUTTON) == LOW) {
    triggerCamera();
    delay(2000);
  }
}

// ========== Functions ==========

void initGSM() {
  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CMGF=1"); // Set to text mode
  delay(500);
}

void readGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}

void readHealthSensor() {
  if (millis() - lastHealthRead > healthInterval) {
    lastHealthRead = millis();
    long irValue = particleSensor.getIR();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Heart Monitor:");
    display.print("IR: ");
    display.println(irValue);
    display.display();
  }
}

void triggerSOS() {
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);

  String sms = "🚨 SOS Alert! I need help.\n";

  if (gps.location.isValid()) {
    sms += "Location: https://maps.google.com/?q=";
    sms += gps.location.lat();
    sms += ",";
    sms += gps.location.lng();
  } else {
    sms += "Location not available.";
  }

  sim800l.println("AT+CMGS=\"+91XXXXXXXXXX\""); // Replace with actual number
  delay(1000);
  sim800l.println(sms);
  delay(500);
  sim800l.write(26); // CTRL+Z to send
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("SOS Sent!");
  display.display();
}

void triggerCamera() {
  // Stub function – add SPI OV2640 code here if connected
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("📸 Camera Triggered!");
  display.display();
}
