#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>
#include <LongFSR.h>
#include <SmallFSR.h>

// Wifi connection parameters
const char* ssid     = "Armor 8";
const char* password = "0032074b4f8e";
const char* host = "192.168.43.179";
// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 5566;

LongFSR longFSR(NULL,1,500);
SmallFSR smallFSR(NULL,2,400);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(600);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  longFSR.setClient(client);
  smallFSR.setClient(client);

}

void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);
 
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  while(client.connected()){
    longFSR.send();
    //client.write('c');
    smallFSR.send();
    delay(500);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
