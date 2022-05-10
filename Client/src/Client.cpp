#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>
#include <LongFSR.h>
#include <SmallFSR.h>

// Basic code to change for caress 
bool p1 = false;
bool p2 = false;
bool p3 = false;


// Wifi connection parameters
const char* ssid     = "Armor 8";
const char* password = "0032074b4f8e";
const char* host = "192.168.43.179";
// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 5566;

// Input analog pins
int fsrAnalogPin = 0; // Force Sensing Resistor is connected to analog 0
const int SOFT_POT_PIN = A1; // Pin connected to softpot wiper
const int GRAPH_LENGTH = 40; // Length of line graph

LongFSR longFSR(NULL,0,500);
SmallFSR smallFSR(client,1,40);

void setup() {
  Serial.begin(115200);
  pinMode(SOFT_POT_PIN, INPUT);
  
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
    //smallFSR.send();
    client.write('h');
    delay(500);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
