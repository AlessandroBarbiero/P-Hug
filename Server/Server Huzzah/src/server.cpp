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
//#define DEBUG
// #define BUTTON A0

//%%%%%%%%%%%%% WIFI PARAMETERS %%%%%%%%%%%%%%
const String SSID_prefix = "SSID: ";
const String PSW_prefix = "Password: ";
bool searchingSSID = true;
bool searchingPassword = true;


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
#define HEATING_DUTY_CYCLE (float)0.90


#define PING_TOLERANCE 20000
unsigned long lastPing;

uint8_t pinsL[L_TOT_VIB] = {L_VIB1, L_VIB2, L_VIB3};
Caress caressUnitLeft(pinsL, L_TOT_VIB);
uint8_t pinsR[R_TOT_VIB] = {R_VIB1, R_VIB2, R_VIB3};
Caress caressUnitRight(pinsR, R_TOT_VIB);

Hug hugUnit(INFLATE_TIME, START_COOLDOWN);
Heat heatUnit(HEATING_DUTY_CYCLE);

WiFiServer server(TCP_PORT);
WiFiConnection wifi(SECRET_SSID, SECRET_PASS, server);

char msg;
unsigned long exTime;
#ifdef DEBUG
  unsigned long startTime;
  bool done1, done2, done3;
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial);
  heatUnit.start(millis());

  #ifdef DEBUG
    startTime = millis();
    done1=false;
    done2=false;
    done3=false;
  #else

  String connectionDetails;
  while(searchingSSID || searchingPassword){
    if(Serial.available()>0){
      Serial.print("D: Message arrived: ");
      connectionDetails = Serial.readString();
      Serial.println(connectionDetails);
      if(connectionDetails.startsWith(SSID_prefix)){
        wifi.setSSID(connectionDetails.substring(SSID_prefix.length()));
        searchingSSID = false;
      }
      if(connectionDetails.startsWith(PSW_prefix)){
        wifi.setPassword(connectionDetails.substring(PSW_prefix.length()));
        searchingPassword = false;
      }
    }
  }
  Serial.println("R: success");
  
  wifi.setup();
  caressUnitLeft.notify(2);
  #endif
}

void loop() {

  #ifdef DEBUG
  exTime = millis();
  caressUnitLeft.run(exTime);
  caressUnitRight.run(exTime);
  hugUnit.run(exTime);
  heatUnit.run(exTime);
  delay(3);

/*   if(!done1 && exTime - startTime > 8000){
    hugUnit.start(exTime);
    done1 = true;
  }
  if(!done2 && exTime - startTime > 18000){
    caressUnitLeft.start(exTime, INTERVAL, SHIFT);
    done2 = true;
  }
  if(!done3 && exTime - startTime > 22000){
    caressUnitRight.start(exTime, INTERVAL, SHIFT);
    done3 = true;
  }
 */
  if(exTime - startTime > 5100){
    // caressUnitLeft.shake(exTime);
    // caressUnitRight.shake(exTime);
     caressUnitLeft.start(exTime, INTERVAL, SHIFT);
    // caressUnitRight.start(exTime, INTERVAL, SHIFT);
    startTime = exTime;
  }


  #else

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
      }
    }
  }
  #endif
}