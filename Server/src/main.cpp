/**
 * This is the code running in the jacket
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
// #define DEBUG
// #define BUTTON A0

#define RX 3
#define TX 1

// %%%%%% CARESS PARAMETERS %%%%%%
#define INTERVAL 255
#define SHIFT 180

// Define Pins for the left caress
#define L_VIB1 14
#define L_VIB2 12
#define L_VIB3 13
#define L_TOT_VIB 3

// Define pins for the right caress
#define R_VIB1 2
#define R_VIB2 5
#define R_VIB3 4
#define R_TOT_VIB 3

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


#define PING_TOLERANCE 20000
unsigned long lastPing;

uint8_t pinsL[L_TOT_VIB] = {L_VIB1, L_VIB2, L_VIB3};
Caress caressUnitLeft(pinsL, L_TOT_VIB);
uint8_t pinsR[R_TOT_VIB] = {R_VIB1, R_VIB2, R_VIB3};
Caress caressUnitRight(pinsR, R_TOT_VIB);

Hug hugUnit(INFLATE_TIME, START_COOLDOWN);
Heat heatUnit(HEATING_TIME, HEATING_COOLDOWN);

WiFiServer server(TCP_PORT);
WiFiConnection wifi(SECRET_SSID, SECRET_PASS, server);

char msg;
unsigned long time;

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
      time = millis();
      caressUnitLeft.run(time);
      caressUnitRight.run(time);
      hugUnit.run(time);
      heatUnit.run(time);

      if (wifi.checkMessage()) {
        msg = wifi.readMessage();

        switch(msg){
          case 'p':
            lastPing = time;
            break;
          case 'c':
            caressUnitLeft.start(time, INTERVAL, SHIFT);
            caressUnitRight.start(time, INTERVAL, SHIFT);
            break;
          case 'h':
            hugUnit.start(time); 
            heatUnit.start(time);
            break;
          default:
            Serial.print("D: Message: ");
            Serial.println(msg);
        }
      }
      
      // if client doesn't send ping for PING_TOLERANCE time, it is considered disconnected
      if (millis() - lastPing > PING_TOLERANCE) {
        wifi.stopClient();
      }
    }
  }
  #endif
}
