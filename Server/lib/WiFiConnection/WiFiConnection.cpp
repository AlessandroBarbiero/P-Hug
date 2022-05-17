#include <Arduino.h>
#include <WiFiConnection.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

WiFiConnection::WiFiConnection(String ssid, String password, WiFiServer server){
    _ssid = ssid;
    _password = password;
    _server = server;
}

int WiFiConnection::getPort(){
    return _port;
}

bool WiFiConnection::searchClient(){
    _client = _server.available();
    return _client;
}

bool WiFiConnection::isClientConnected(){
    return _client.connected();
}

bool WiFiConnection::checkMessage(){
    return _client.available() > 0;
}

void WiFiConnection::setup(){
    int status = WL_IDLE_STATUS;
    WiFi.config(_ip, _gateway, _subnet);
    Serial.print("Connecting to ");
    Serial.println(_ssid);
    
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network: ");
        Serial.println(_ssid);
        status = WiFi.begin(_ssid, _password);

        // wait 10 seconds for connection:
        delay(10000);
    }
  
    _server.begin();

    Serial.println("You're connected to the network and Server started");
    Serial.println("----------------------------------------");
    printData();
    Serial.println("----------------------------------------");
}

char WiFiConnection::readMessage(){
    return (char) _client.read();
}

void WiFiConnection::stopClient(){
    _client.stop();
    Serial.println("Client disconnected");
}

//---private
void WiFiConnection::printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
}
