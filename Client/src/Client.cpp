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

WiFiConnection wifi;
WiFiClient client;
LongFSR longFSR(NULL,1,400);
SmallFSR smallFSR1(2,400,2000);
SmallFSR smallFSR2(3,400,2000);
SmallFSR smallFSR3(4,400,2000);
Ear ear1(9,true);
Ear ear2(8,false);
Accelerometer accelerometer;
Speaker speaker;
CaressHandler caressHandler(smallFSR1, smallFSR2, smallFSR3, ear1, ear2);
HugHandler hugHandler(longFSR,ear1, ear2);
ShakeHandler shakeHandler(2000,ear1,ear2);

void setup() {
  Serial.begin(115200);
  delay(100);
  speaker.setup();
  accelerometer.setup();
  caressHandler.setSpeaker(speaker);
  shakeHandler.setSpeaker(speaker);
  hugHandler.setSpeaker(speaker);
  shakeHandler.setAccelerometer(accelerometer);
  //wifi.setup();
  speaker.networkConnectionAttempt();
}

void loop() {

  delay(5000);

  int i = 0;

  ear1.connect();
  ear2.connect();

  while(1){
    caressHandler.run();
    shakeHandler.run();
    hugHandler.run();
    delay(50);
  }

  

  Serial.print("connecting to ");
  Serial.println(wifi.getHost());

  if (!client.connect(wifi.getHost(), wifi.getPort())) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("Connected");

  speaker.connect();
  ear1.connect();

  caressHandler.setClient(client);
  hugHandler.setClient(client);
  shakeHandler.setClient(client);

  while(client.connected()){
    wifi.ping(client);
    caressHandler.run();
    hugHandler.run();
    shakeHandler.run();
    delay(500);
  }
  
  Serial.println();
  Serial.println("closing connection");

  speaker.disconnect();
  ear1.disconnect();
}