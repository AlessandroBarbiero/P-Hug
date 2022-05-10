#include <WiFi101.h>

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

void sendLongFSR(){
  int fsrValue = analogRead(fsrAnalogPin);
  Serial.println(fsrValue);
  if(fsrValue > 500){
    Serial.println("Hugged done");
    client.write('h');
  }
}

void sendFSR(){
  int softPotADC = analogRead(SOFT_POT_PIN);
  // Map the 0-1023 value to 0-40
  int softPotPosition = map(softPotADC, 0, 1023, 0, GRAPH_LENGTH);
  Serial.print(softPotPosition);
  if(checkAction(softPotPosition)){
   Serial.print ("CARESS DONE");
   client.write('c');
  }
}

bool checkAction(int value){

  if(value < 5){
    p1 = true;
    p2 = false;
    p3 = false;
  }
  if(value >= 5 && value < 15){
    if (p1 = true){
      p2 = true;
      p3 = false;
    }
    else{
      p1 = false;
      p2 = false;
      p3 = false;
    }
  }
  else{
    if (p1 && p2 ){
      p3 = true;
    }
    else{
      p1 = false;
      p2 = false;
      p3 = false;
    }
  } 

 if(p1 && p2 && p3){
  return true;
 }
 return false;
}



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
    sendLongFSR();
    sendFSR();
    delay(500);
  }

  /*
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  */
  
  Serial.println();
  Serial.println("closing connection");
}
