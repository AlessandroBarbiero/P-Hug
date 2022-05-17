/**
 * Please enter your sensitive data in the include/Secrets.h to run the WiFi network
 *
 */

#include <Secrets.h>
#include <ESP8266WiFi.h>
#include <Caress.h>
#include <Hug.h>
#include <WiFiConnection.h>

// debug checking
// #define DEBUG
// #define BUTTON A0

// Define Pins
#define VIB1 14
#define VIB2 12
#define VIB3 13
#define NROFVIB 3
// Define the vibration settings
#define VIB4 15
#define VIB5 0      // not good
#define VIB6 16     // maybe good
#define VIB7 2      // maybe good
#define VIB8 5      // maybe good
#define VIB9 4      // maybe good


#define RX 3
#define TX 1
#define INTERVAL 255
#define SHIFT 180
#define INFLATECOOLDOWN 5000
#define STARTCOOLDOWN 10000

unsigned long lastPing;

uint8_t pins[NROFVIB] = {VIB1, VIB2, VIB3};
Caress caressUnit(pins, NROFVIB);
Hug hugUnit(INFLATECOOLDOWN, STARTCOOLDOWN);

WiFiServer server(TCP_PORT);
WiFiConnection wifi(SECRET_SSID, SECRET_PASS, server);

char msg;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  #ifdef DEBUG
  pinMode(BUTTON, INPUT);
  #else
  wifi.setup();
  #endif
}

void loop() {

  #ifdef DEBUG
  caressUnit.run();
  delay(5);
  if (analogRead(BUTTON) > 500) {
    Serial.println("button pressed");
    caressUnit.start(INTERVAL, SHIFT);
  }
  #else

  if (wifi.searchClient()) {
    Serial.println("new client");
    lastPing = millis();
    
    while (wifi.isClientConnected()) {
      delay(3);
      caressUnit.run();
      hugUnit.run();

      if (wifi.checkMessage()) {
        msg = wifi.readMessage();

        switch(msg){
          case 'p':
            lastPing = millis();
            break;
          case 'c':
            caressUnit.start(INTERVAL, SHIFT);
            break;
          case 'h':
            hugUnit.start(); 
            break;
          default:
            Serial.print("Message: ");
            Serial.println(msg);
        }
      }
      
      // if client disconnect
      if (millis() - lastPing > 5000) {
        wifi.stopClient();
      }
    }
  }
  #endif
}
