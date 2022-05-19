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

WiFiConnection wifi;
WiFiClient client;
LongFSR longFSR(NULL,1,500);
SmallFSR smallFSR1(2,400,2000);
SmallFSR smallFSR2(3,400,2000);
SmallFSR smallFSR3(4,400,2000);
Ear ear1(9);
Ear ear2(10);
Accelerometer accelerometer;
Speaker speaker;
CaressHandler caressHandler(smallFSR1, smallFSR2, smallFSR3, ear1, ear2, speaker);

void setup() {
  Serial.begin(115200);
  delay(100);
  speaker.setup();
  accelerometer.setup();
  //wifi.setup();
}

void loop() {

  delay(5000);


  while(1){
    caressHandler.run();
    delay(500);
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

  longFSR.setClient(client);
  smallFSR1.setClient(client);
  smallFSR2.setClient(client);
  smallFSR3.setClient(client);

  while(client.connected()){
    wifi.ping(client);
    accelerometer.print();
    longFSR.send();
    smallFSR1.send();
    smallFSR2.send();
    smallFSR3.send();
    delay(500);
  }
  
  Serial.println();
  Serial.println("closing connection");

  speaker.disconnect();
  ear1.disconnect();
}