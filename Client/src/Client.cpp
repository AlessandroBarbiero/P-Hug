#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>
#include <LongFSR.h>
#include <SmallFSR.h>
#include <WiFiConnection.h>
#include <Ear.h>
#include <Accelerometer.h>
#include <Speaker.h>

WiFiConnection wifi;
WiFiClient client;
LongFSR longFSR(NULL,1,500);
SmallFSR smallFSR1(NULL,2,400,2000);
SmallFSR smallFSR2(NULL,3,400,2000);
SmallFSR smallFSR3(NULL,4,400,2000);
Ear ear(9);
Accelerometer accelerometer;
Speaker speaker;

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
    smallFSR1.start();
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
  ear.connect();

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
  ear.disconnect();
}