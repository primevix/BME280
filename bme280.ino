#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
      
#include <Wire.h>
#include "SPI.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Setup connection of the sensor
Adafruit_BMP280 bmp; // I2C

char auth[] = "*******************************";
char ssid[] = "********************";
char pass[] = "***************";
char server[] = "*********";
BlynkTimer timer;

//Variables
float pressure;
float temperature;
int altimeter;

void setup() {
  bmp.begin();
  Serial.begin(9600);
  Serial.println("Adafruit BMP280 test:");
  Blynk.begin(auth, ssid, pass, server);
  timer.setInterval(5000L, ReadSensors);
}

  void ReadSensors(){
  //Read values from the sensor:
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  altimeter = bmp.readAltitude (1029.00);

  Blynk.virtualWrite(V1, pressure/100);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, altimeter-51);
      
  //Print values to serial monitor:
  Serial.print(F("Pressure: "));
  Serial.print(pressure);
  Serial.print(" Mb");
  Serial.print("\t");
  Serial.print(("Temp: "));
  Serial.print(temperature);
  Serial.print(" oC");
  Serial.print("\t");
  Serial.print("Altimeter: ");
  Serial.print(altimeter);
  Serial.println(" m");    
  //delay(5000);
}

void loop() {
  Blynk.run();
  timer.run();
}
