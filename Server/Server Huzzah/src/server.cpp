/**
 *  This is the code running in the jacket
 *  The credentials to connect to the WiFi Network can be passed through the Bluetooth application
 */

#include <Secrets.h>
#include <ESP8266WiFi.h>
#include <Caress.h>
#include <Hug.h>
#include <WiFiConnection.h>
#include <Heat.h>

#define RX 3
#define TX 1

// %%%%%% CARESS PARAMETERS %%%%%%
#define INTERVAL 255
#define SHIFT 120

// Define Pins for the left caress
#define L_VIB1 13
#define L_VIB2 12
#define L_VIB3 14
#define L_TOT_VIB 3

// Define pins for the right caress
#define R_VIB1 15
#define R_VIB2 5
#define R_VIB3 4
#define R_TOT_VIB 3

// other possible pins to use
/*
    #define VIB6 16     
 */

// %%%%%% HUG PARAMETERS %%%%%%
#define INFLATE_TIME 11000
#define START_COOLDOWN 20000

// %%%%%% HEAT PARAMETERS %%%%%%
#define HEATING_DUTY_CYCLE (float)0.70


#define PING_TOLERANCE 20000
unsigned long lastPing;

uint8_t pinsL[L_TOT_VIB] = {L_VIB1, L_VIB2, L_VIB3};
Caress caressUnitLeft(pinsL, L_TOT_VIB);
uint8_t pinsR[R_TOT_VIB] = {R_VIB1, R_VIB2, R_VIB3};
Caress caressUnitRight(pinsR, R_TOT_VIB);

Hug hugUnit(INFLATE_TIME, START_COOLDOWN);
Heat heatUnit(HEATING_DUTY_CYCLE);

WiFiServer server(TCP_PORT);
WiFiConnection wifi(server);

char msg;
unsigned long exTime;

void setup() {
  delay(5000);
  Serial.begin(9600);
  while (!Serial);
  delay(5000);
  Serial.println("D: Serial ready");
  
  wifi.setup();
  caressUnitLeft.notify(2);
  heatUnit.start(millis());
}

void loop() {
  //execute the heating loop even before the connection of the client
  delay(3);
  exTime = millis();
  heatUnit.run(exTime);

  if (wifi.searchClient()) {
    Serial.println("D: new client");
    caressUnitRight.notify(2);
    lastPing = millis();
    
    while (wifi.isClientConnected()) {
      delay(3);
      exTime = millis();
      caressUnitLeft.run(exTime);
      caressUnitRight.run(exTime);
      hugUnit.run(exTime);
      heatUnit.run(exTime);

      if (wifi.checkMessage()) {
        msg = wifi.readMessage();

        switch(msg){
          case 'p':
            lastPing = exTime;
            break;
          case 'c':
            caressUnitLeft.start(exTime, INTERVAL, SHIFT);
            caressUnitRight.start(exTime, INTERVAL, SHIFT);
            break;
          case 'h':
            hugUnit.start(exTime); 
            break;
          case 's':
            caressUnitLeft.shake(exTime);
            caressUnitRight.shake(exTime);
            break;
          default:
            Serial.print("D: Message: ");
            Serial.println(msg);
        }
      }
      
      // if client doesn't send ping for PING_TOLERANCE time, it is considered disconnected
      if (millis() - lastPing > PING_TOLERANCE) {
        wifi.stopClient();
        caressUnitLeft.notify(2);
        caressUnitRight.notify(2);
      }
    }
  }
}