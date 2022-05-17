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
#define SHIFT 255
#define INFLATECOOLDOWN 5000
#define STARTCOOLDOWN 10000


uint8_t pins[NROFVIB] = {VIB1, VIB2, VIB3};
Caress caressUnit(pins, NROFVIB);

WiFiServer server(TCP_PORT);
WiFiConnection wifi(SECRET_SSID, SECRET_PASS, server);
char msg;
Hug hugUnit(INFLATECOOLDOWN, STARTCOOLDOWN);

void setup() {
  #ifdef DEBUG
  pinMode(BUTTON, INPUT);
  #endif

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  wifi.setup();
}

void loop() {

  #ifdef DEBUG
  caressUnit.run();
  if (analogRead(BUTTON) > 500) {
    Serial.println("button pressed");
    caressUnit.start(INTERVAL, SHIFT);
  }
  #else

  if (wifi.searchClient()) {
    Serial.println("new client");
    
    while (wifi.isClientConnected()) {
      caressUnit.run();
      hugUnit.run();

      if (wifi.checkMessage()) {
        msg = wifi.readMessage(); 
        Serial.print("Message: ");
        Serial.println(msg);

        if(msg=='c')
          caressUnit.start(INTERVAL, SHIFT);
        else if(msg== 'h')
          hugUnit.start();
        }

      }

      // if client disconnect
 //     client.stop();
 //     Serial.println("client disonnected");
    }
    #endif
}
