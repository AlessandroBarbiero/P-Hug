/**
 * Please enter your sensitive data in the include/Secrets.h to run the WiFi network
 *
 */

#include <Secrets.h>
#include <ESP8266WiFi.h>
#include <Caress.h>
#include <Hug.h>
#include <WiFiConnection.h>
#include <Heat.h>

// debug checking
 #define DEBUG
 #define BUTTON A0

#define RX 3
#define TX 1

// %%%%%% CARESS PARAMETERS %%%%%%
#define INTERVAL 255
#define SHIFT 180

// Define Pins for the first wave
#define A_VIB1 14
#define A_VIB2 12
#define A_VIB3 13
#define A_TOT_VIB 3

// Define pins for the second wave
#define B_VIB1 2
#define B_VIB2 5
#define B_VIB3 4
#define B_TOT_VIB 3

// other possible pins to use
/*  #define VIB4 15
    #define VIB6 16     
 */

// %%%%%% HUG PARAMETERS %%%%%%
#define INFLATE_TIME 5000
#define START_COOLDOWN 10000

// %%%%%% HEAT PARAMETERS %%%%%%
#define HEATING_TIME 5000
#define HEATING_COOLDOWN 10000


#define PING_TOLERANCE 5000
unsigned long lastPing;

uint8_t pinsA[A_TOT_VIB] = {A_VIB1, A_VIB2, A_VIB3};
Caress caressUnitA(pinsA, A_TOT_VIB);
uint8_t pinsB[B_TOT_VIB] = {B_VIB1, B_VIB2, B_VIB3};
Caress caressUnitB(pinsB, B_TOT_VIB);

Hug hugUnit(INFLATE_TIME, START_COOLDOWN);
Heat heatUnit(HEATING_TIME, HEATING_COOLDOWN);

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
  caressUnitA.run();
  caressUnitB.run();
  delay(5);
  /* if (analogRead(BUTTON) > 500) {
    Serial.println("D: button pressed");
    caressUnit.start(INTERVAL, SHIFT);
  } */

  //try Start the caress every 5 seconds or more (it is correct if it is not executed at every 5 seconds -> maybe the millis is not called exactly)
  if(millis()%5000 == 0){
    caressUnitA.start(INTERVAL, SHIFT);
    caressUnitB.start(INTERVAL, SHIFT);
  }

  #else

  if (wifi.searchClient()) {
    Serial.println("D: new client");
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
            Serial.print("D: Message: ");
            Serial.println(msg);
        }
      }
      
      // if client disconnect
      if (millis() - lastPing > PING_TOLERANCE) {
        wifi.stopClient();
      }
    }
  }
  #endif
}
