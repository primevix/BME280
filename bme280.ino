       // BMP280.ino https://community.blynk.cc/t/bmp280/15188/6

    #include <ESP8266WiFi.h>
    #include <BlynkSimpleEsp8266.h>
      
    #include <Wire.h>
    #include "SPI.h" //Why? Because library supports SPI and I2C connection
    #include <Adafruit_Sensor.h>
    #include <Adafruit_BMP280.h>

    //Setup connection of the sensor
    Adafruit_BMP280 bmp; // I2C


    /*//For SPI connection!
    #define BMP_SCK 13
    #define BMP_MISO 12
    #define BMP_MOSI 11 
    #define BMP_CS 10
    //Adafruit_BMP280 bme(BMP_CS); // hardware SPI
    //Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
    */

    char auth[] = "*******************************";
    char ssid[] = "********************";
    char pass[] = "***************";
    char server[] = "*********";
    BlynkTimer timer;

    //Variables
    float pressure;     //To store the barometric pressure (Pa)
    float temperature;  //To store the temperature (oC)
    int altimeter;      //To store the altimeter (m) (you can also use it as a float variable)

    void setup() {
      bmp.begin();    //Begin the sensor
      Serial.begin(9600); //Begin serial communication at 9600bps
      Serial.println("Adafruit BMP280 test:");
      Blynk.begin(auth, ssid, pass, server);
      timer.setInterval(5000L, ReadSensors);   // read sensor every 5s 
    }

    void ReadSensors(){
      //Read values from the sensor:
      pressure = bmp.readPressure();
      temperature = bmp.readTemperature();
      altimeter = bmp.readAltitude (1029.00); //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)

      Blynk.virtualWrite(V1, pressure/100);     // write pressure to V1 value display widget
      Blynk.virtualWrite(V2, temperature);  // write temperature to V2 value display widget
      Blynk.virtualWrite(V3, altimeter-51);    // write altimeter to V3 value display widget
      
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
      Serial.print(altimeter); // this should be adjusted to your local forcase
      Serial.println(" m");    
      //delay(5000); //Update every 5 sec  
    }

    void loop() {
      Blynk.run();
      timer.run();
    }
