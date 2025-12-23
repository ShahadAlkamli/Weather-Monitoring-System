#  Weather Monitoring System

This project is an IoT-based weather monitoring system built using the ESP8266 NodeMCU. It measures temperature, humidity, atmospheric pressure, rain intensity, and ambient light, then displays the data on a 16×2 LCD and sends it to the Blynk IoT Cloud for real-time remote monitoring.

---

## Project Overview

The system integrates several sensors with the ESP8266 microcontroller to collect and transmit weather data. The Blynk platform is used for visualization on both mobile and web dashboards.

The system measures:
- Temperature (DHT11)
- Humidity (DHT11)
- Atmospheric Pressure (BMP180)
- Rain Level (Rain Sensor)
- Light Intensity (LDR)

All readings are updated locally through the LCD and remotely through the Blynk dashboard.

---

## Features

- Real-time temperature and humidity monitoring  
- Atmospheric pressure measurement  
- Rain detection and intensity level calculation  
- Light detection using an LDR sensor  
- Local LCD display output  
- Blynk IoT dashboard integration  
- Wi-Fi enabled cloud connectivity  
- Automatic timed data updates  

---

## Hardware Components

- ESP8266 NodeMCU  
- DHT11 temperature and humidity sensor  
- BMP180 barometric pressure sensor  
- Rain sensor module  
- LDR light sensor  
- 16×2 LCD with I2C module  
- Breadboard  
- Jumper wires  
- USB cable for programming  

---

## Pin Connections

| Component       | ESP8266 Pin |
|-----------------|-------------|
| DHT11 Sensor    | D3          |
| Rain Sensor     | A0          |
| LDR Sensor      | D0          |
| BMP180 Sensor   | SDA → D2, SCL → D1 |
| LCD (I2C)       | SDA → D2, SCL → D1 |

---

## Circuit Diagram

```
![Circuit Diagram](https://raw.githubusercontent.com/ShahadAlkamli/Weather-Monitoring-System/main/Circuit_Diagram.png)

```

## Code File

The complete implementation is contained in:

```
WMS.ino
```

This file includes:
- Wi-Fi setup  
- Blynk authentication  
- Sensor reading functions  
- LCD display output  
- Cloud communication  
- Timed data updates  

---

## Demo Video

[![Demo Video](https://img.youtube.com/vi/iuUvchgC3Vo/maxresdefault.jpg)](https://youtube.com/shorts/iuUvchgC3Vo?feature=share)

The demo shows the system displaying live sensor readings on the LCD screen and updating the data in real time on both the Blynk mobile and web dashboards.

---

## How to Use

### 1. Install Required Libraries
Install the following from the Arduino IDE Library Manager:
- ESP8266 board package  
- Blynk library  
- DHT sensor library  
- Adafruit BMP085/BMP180 library  
- LiquidCrystal_I2C library  

### 2. Configure Credentials
Update the following fields in `WMS.ino`:

```cpp
char auth[] = "YOUR_BLYNK_TOKEN";
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

### 3. Select the ESP8266 Board
In Arduino IDE:  
Tools → Board → NodeMCU 1.0 (ESP-12E Module)

### 4. Upload the Code
Connect the ESP8266 to your computer, select the correct COM port, and upload the code.

### 5. Monitor Data
Data appears:  
- On the 16×2 LCD screen  
- On the Blynk mobile app  
- On the Blynk web dashboard  

---

## Project Structure

```
IoT-Weather-Monitoring-System/
│
├── WMS.ino
├── Circuit_Diagram.png
├── Demo.MOV
└── README.md
```

---

## Conclusion

This project demonstrates a complete IoT-based environmental monitoring system using the ESP8266. It integrates multiple sensors, cloud connectivity, and real-time data visualization, making it suitable for learning, academic projects, and practical IoT applications.
