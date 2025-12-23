#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SFE_BMP180.h>

// -------------------------------------------
// LCD Display
// -------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------------------------------
// BMP180 Sensor
// -------------------------------------------
SFE_BMP180 bmp;

// -------------------------------------------
// Blynk Authentication & WiFi Credentials
// -------------------------------------------
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// -------------------------------------------
// DHT11 Sensor
// -------------------------------------------
DHT dht(D3, DHT11);

// -------------------------------------------
// Pins for Additional Sensors
// -------------------------------------------
#define rain A0
#define light D0

BlynkTimer timer;

// -------------------------------------------
// Setup Function
// -------------------------------------------
void setup() {
  Serial.begin(9600);

  // BMP180 initialization
  if (bmp.begin()) {
    Serial.println("BMP180 initialized");
  } else {
    Serial.println("BMP180 NOT detected");
  }

  // LCD initialization
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(3000);
  lcd.clear();

  // WiFi + Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // DHT11 start
  dht.begin();

  // Timer intervals
  timer.setInterval(2000L, DHT11sensor);
  timer.setInterval(1000L, rainSensor);
  timer.setInterval(5000L, pressure);
  timer.setInterval(1000L, LDRsensor);

  pinMode(light, INPUT);
}

// -------------------------------------------
// DHT11 Sensor Reading
// -------------------------------------------
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT read failed!");
    return;
  }

  // Send to Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  // Show on LCD
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C  ");

  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("% ");

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.println(h);
}

// -------------------------------------------
// Rain Sensor
// -------------------------------------------
void rainSensor() {
  int value = analogRead(rain);
  value = map(value, 1024, 0, 0, 100);

  Blynk.virtualWrite(V2, value);

  lcd.setCursor(0, 1);
  lcd.print("R:");
  lcd.print(value);
  lcd.print("% ");

  Serial.print("Rain: ");
  Serial.print(value);
  Serial.println("%");
}

// -------------------------------------------
// Pressure Sensor (BMP180)
// -------------------------------------------
double T, P;
char status;

void pressure() {
  status = bmp.startTemperature();
  if (status != 0) {
    delay(5);

    status = bmp.getTemperature(T);
    status = bmp.startPressure(3);

    if (status != 0) {
      delay(5);
      status = bmp.getPressure(P, T);

      if (status != 0) {
        Blynk.virtualWrite(V3, P);

        lcd.setCursor(8, 1);
        lcd.print("P:");
        lcd.print(P);

        Serial.print("Pressure: ");
        Serial.println(P);
      }
    }
  }
}

// -------------------------------------------
// LDR Sensor
// -------------------------------------------
void LDRsensor() {
  bool value = digitalRead(light);
  WidgetLED LED(V4);

  if (value == 0) LED.on();
  else LED.off();

  Serial.print("Light: ");
  Serial.println(value);
}

// -------------------------------------------
// Loop
// -------------------------------------------
void loop() {
  Blynk.run();
  timer.run();
}
