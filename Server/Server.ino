#include "arduino_secrets.h"
#include <ESP8266WiFi.h>

// Define Pins
#define VIB1 14
#define VIB2 12
#define VIB3 13
#define MAX 255
#define BUTTON A0
#define COOLDOWN 10000
#define INTERVAL 510
#define HINTERVAL 255
#define SHIFT 255
#define NROFVIB 3
int val,i;
unsigned long lastCaress,lastHug;
bool caressing,hugging;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status
// mac address for M-Duino

int data = 0;
int tcp_port = 5566;
IPAddress ip(192, 168, 43, 179); 
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(tcp_port);
void setup() {
  //Vibration init
  pinMode(VIB1, OUTPUT);
  pinMode(VIB2, OUTPUT);
  pinMode(VIB3, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  Serial.begin(9600);
  lastCaress = 0;
  caressing = false;
  hugging = false;
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  WiFi.config(ip, gateway, subnet);
  while (!Serial);
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
    
  }
  
  server.begin();

  

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network and Server started");
  
  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");
}

void loop() {
  // check the network connection once every 10 seconds:
 //delay(1000);
 //printData();
 //Serial.println("----------------------------------------");

  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    
    while (client.connected()) {
      if (client.available()) {
        char c = (char) client.read();
        Serial.print("Message: ");
        Serial.println(c);
        if(c=='c'){
          caress();
          }
         else if(c== 'h'){
          hug();
          }
        
        }
       if (caressing){
          
          if(i< INTERVAL){
              analogWrite(VIB1, i);
              }
            else if(i<INTERVAL*2){
              analogWrite(VIB1, INTERVAL*2-i);
              }
            
            if(i>SHIFT && i<SHIFT+INTERVAL){
              analogWrite(VIB2, i-SHIFT);
              }
            else if(i>SHIFT+INTERVAL && i<SHIFT+2*INTERVAL){
              analogWrite(VIB2, SHIFT+2*INTERVAL-i);
              }
      
            if(i>2*SHIFT && i<2*SHIFT+INTERVAL){
              analogWrite(VIB3, i-2*SHIFT);
              }
            else if(i>2*SHIFT+INTERVAL && i<2*SHIFT+2*INTERVAL){
              analogWrite(VIB3, 2*SHIFT+2*INTERVAL-i);
              }
      
              i++;
              delay(1);
              if(i == (SHIFT+INTERVAL)*(NROFVIB-1)){
                caressing = false;
                i=0;
                }
        }

        if(hugging){
          digitalWrite(0, LOW);
          delay(1000);
          digitalWrite(0, HIGH);
          hugging = false;
          }
      }

      delay(1000);
    }
    // give the web browser time to receive the data
    
  
    // close the connection:
    //client.stop();
    //Serial.println("client disonnected");
}


void printData() {
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

void caress(){
  if(millis()- lastCaress > COOLDOWN){
    Serial.println("Caress started at time: ");
    
    lastCaress = millis();

    Serial.println(lastCaress);

   caressing = true;
    
  }
}

void hug(){
  if(millis()- lastHug > COOLDOWN){
    Serial.println("Hug started at time: ");
    
    lastHug = millis();

    Serial.println(lastHug);

   hugging = true;
    
  }
  }
