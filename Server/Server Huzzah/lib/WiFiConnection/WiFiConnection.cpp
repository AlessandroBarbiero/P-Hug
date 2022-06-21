#include <Arduino.h>
#include <WiFiConnection.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

WiFiConnection::WiFiConnection(WiFiServer server){
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

// Try to connect to the network, if it doesn't work after 150 seconds it tries to retreive new credentials from serial port
void WiFiConnection::setup(){
    int status = WL_IDLE_STATUS;
    WiFi.config(_ip, _gateway, _subnet);
    if(!_credentials.readFromMemory())
        _credentials.search();

    int i = 1;
    // attempt to connect to Wifi network, if connection goes wrong for 10 times (150 seconds) ask again credentials via bluetooth
    while (status != WL_CONNECTED) {
        
        Serial.print("D: Attempting to connect to network: ");
        Serial.println(_credentials.getSsid());
        status = WiFi.begin(_credentials.getSsid(), _credentials.getPassword());
        
        // wait 15 seconds for connection before retry:
        delay(15000);

        // After 10 times try to recall credentials from bluetooth application
        if(i%10==0){
            Serial.println("D: Wrong credentials, try to insert credentials again.");
            _credentials.search();
        }
        i++;
    }
    _server.begin();

    delay(3000);
    Serial.println("R: success");
    delay(3000);
    Serial.println("D: Credentials saved to memory");

    Serial.println("D: You're connected to the network and Server started");
    Serial.println("D: ----------------------------------------");
    printData();
    Serial.println("D: ----------------------------------------");
    
    delay(3000);
}

char WiFiConnection::readMessage(){
    return (char) _client.read();
}

void WiFiConnection::stopClient(){
    _client.stop();
    Serial.println("D: Client disconnected");
}

//---private
void WiFiConnection::printData() {
  Serial.println("D: Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("D: IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("D: Network Information:");
  Serial.print("D: SSID: ");
  Serial.println(WiFi.SSID());
}
