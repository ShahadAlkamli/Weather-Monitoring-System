#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BLYNK_TEMPLATE_ID "TMPL6CnptallS"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SFE_BMP180.h>

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create an object for the BMP180 sensor
SFE_BMP180 bmp;

char auth[] = "BaIwiMAy5bVgB6GYQB9w_x0R3WFbfphg"; // Auth token
char ssid[] = "iPhone"; // WIFI name
char pass[] = "9988998899"; // WIFI password

DHT dht(D3, DHT11); // (DHT sensor pin, sensor type)
BlynkTimer timer;

// Define Rain and LDR pins
#define rain A0
#define light D0

// Create variables for pressure
double T, P;
char status;

void setup() {
  Serial.begin(9600); // Set baud rate for Serial communication
  Serial.println("Starting setup..."); // Debugging info

  // Initialize BMP180 sensor
  if (bmp.begin()) {
    Serial.println("BMP180 initialized");
  } else {
    Serial.println("BMP180 not detected");
  }
  // Initialize the LCD display
  lcd.begin(16, 2); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  pinMode(light, INPUT);
  
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.println("Blynk connected"); // Debugging info

  // Start DHT11 sensor
  dht.begin();
  Serial.println("DHT11 started"); // Debugging info

  // LCD welcome message
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();

  // Call the functions every specific interval
  timer.setInterval(2000L, DHT11sensor);  // Adjust interval to 2 seconds for DHT11
  timer.setInterval(1000L, rainSensor);   // Adjust interval for rain sensor
  timer.setInterval(5000L, pressure);     // 5-second interval for pressure sensor
  timer.setInterval(1000L, LDRsensor);    // 1-second interval for LDR sensor

  Serial.println("Setup complete"); // Debugging info
}

// Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  // Display temperature and humidity on LCD
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(h);

  // Debugging info
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("C, Humidity: ");
  Serial.print(h);
  Serial.println("%");
}

// Get the rain sensor values
void rainSensor() {
  int value = analogRead(rain);
  value = map(value, 1024, 0, 0, 100);  // Invert the mapping

  // Send data to Blynk
  Blynk.virtualWrite(V2, value);

  // Display rain sensor value on LCD
  lcd.setCursor(0, 1);
  lcd.print("R:");
  lcd.print(value);
  lcd.print(" ");

  // Debugging info
  Serial.print("Rain sensor value: ");
  Serial.println(value);
}


// Get the pressure values
void pressure() {
  status = bmp.startTemperature();
  if (status != 0) {
    delay(5); // Small delay for temperature measurement
    status = bmp.getTemperature(T);

    status = bmp.startPressure(3); // 0 to 3
    if (status != 0) {
      delay(5); // Small delay for pressure measurement
      status = bmp.getPressure(P, T);
      if (status != 0) {
        Blynk.virtualWrite(V3, P);
        lcd.setCursor(8, 1);
        lcd.print("P:");
        lcd.print(P);

        // Debugging info
        Serial.print("Pressure: ");
        Serial.print(P);
        Serial.println(" Pa");
      }
    }
  }
}

// Get the LDR sensor values
void LDRsensor() {
  bool value = digitalRead(light);
  WidgetLED LED(V4);
  if (value == 0) {
    LED.on();
  } else {
    LED.off();
  }

  // Debugging info
  Serial.print("LDR sensor value: ");
  Serial.println(value);
}

void loop() {
  Blynk.run(); // Run the Blynk library
  timer.run(); // Run the Blynk timer
}


