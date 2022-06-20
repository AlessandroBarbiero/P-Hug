#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>
#include <LongFSR.h>
#include <SmallFSR.h>
#include <WiFiConnection.h>
#include <Ear.h>
#include <Accelerometer.h>
#include <Speaker.h>
#include <CaressHandler.h>
#include <HugHandler.h>
#include <ShakeHandler.h>
#include <MPU6050_tockn.h>
#include <NFC.h>

#define CLOCK_INTERVAL 50
#define PN532_IRQ   (2) //11
#define PN532_RESET (3)  // 12

bool debug = true;
bool debugNFC = false;
WiFiConnection wifi;
WiFiClient client;
LongFSR longFSR(NULL,1,400);
SmallFSR smallFSR1(2,50,2000);
SmallFSR smallFSR2(3,50,2000);
SmallFSR smallFSR3(4,50,2000);
Ear ear1(9,false);
Ear ear2(8,true);
MPU6050 mpu6050(Wire);
Accelerometer accelerometer(&mpu6050);
Speaker speaker;
CaressHandler caressHandler(smallFSR1, smallFSR2, smallFSR3, ear1, ear2);
HugHandler hugHandler(longFSR,ear1, ear2);
ShakeHandler shakeHandler(2000,ear1,ear2);
Adafruit_PN532 pn532(PN532_IRQ, PN532_RESET);
NFC nfc(&pn532);


void setup() {
  Serial.begin(115200);
  delay(100);
  speaker.setup();
  accelerometer.setup();
  caressHandler.setSpeaker(speaker);
  shakeHandler.setSpeaker(speaker);
  hugHandler.setSpeaker(speaker);
  shakeHandler.setAccelerometer(accelerometer);
  speaker.networkConnectionAttempt();
  nfc.setup();
  if(!debug){
    wifi.setNFC(nfc);
    wifi.setup();
  }
}

void loop() {

  if(debugNFC){
    while(1){
      nfc.run();
    }
  }

  if(debug){
    ear1.connect();
    ear2.connect();

  while(1){
    caressHandler.run();
    //shakeHandler.run();
    //hugHandler.run();
    delay(CLOCK_INTERVAL);
    }
  }

  speaker.jacketConnectionAttempt();
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(wifi.getHost());

  if (!client.connect(wifi.getHost(), wifi.getPort())) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("Connected");

  speaker.connect();
  ear1.connect();
  ear2.connect();

  caressHandler.setClient(client);
  hugHandler.setClient(client);
  shakeHandler.setClient(client);

  while(client.connected()){
    wifi.ping(client);
    caressHandler.run();
    hugHandler.run();
    shakeHandler.run();
    delay(CLOCK_INTERVAL);
  }
  
  Serial.println();
  Serial.println("closing connection");

  speaker.disconnect();
  ear1.disconnect();
  ear2.disconnect();
}