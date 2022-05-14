#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>
#include <LongFSR.h>
#include <SmallFSR.h>
#include <WiFiConnection.h>
#include <Ear.h>

WiFiConnection wifi;

// Use WiFiClient class to create TCP connections
WiFiClient client;

LongFSR longFSR(NULL,1,500);
SmallFSR smallFSR(NULL,2,400);
Ear ear(9);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  wifi.setup();

}

void loop() {

  delay(5000);

  Serial.print("connecting to ");
  Serial.println(wifi.getHost());

  if (!client.connect(wifi.getHost(), wifi.getPort())) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("Connected");

  ear.connect();

  longFSR.setClient(client);
  smallFSR.setClient(client);

  while(client.connected()){
    longFSR.send();
    smallFSR.send();
    delay(500);
  }
  
  Serial.println();
  Serial.println("closing connection");

  ear.disconnect();
}