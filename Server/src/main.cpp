#include <arduino_secrets.h>
#include <ESP8266WiFi.h>
#include <Caress.h>

// Define Pins
#define VIB1 14
#define VIB2 12
#define VIB3 13
#define MAX 255
#define BUTTON A0
#define INTERVAL 255
#define SHIFT 255
#define NROFVIB 3

void printData();
void hug();

uint8_t pins[NROFVIB] = {VIB1, VIB2, VIB3};
Caress caressUnit(pins, NROFVIB);

int val,i;
unsigned long lastHug;
bool hugging;

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
  // init
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
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
  delay(1000);
  printData();
  Serial.println("----------------------------------------");

  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    
    while (client.connected()) {
      caressUnit.run();

      if (client.available()) {
        char c = (char) client.read();
        Serial.print("Message: ");
        Serial.println(c);

        if(c=='c')
          caressUnit.start(INTERVAL, SHIFT);
        else if(c== 'h')
          hug();
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
    client.stop();
    Serial.println("client disonnected");
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

void hug(){
  if(millis()- lastHug > 5000){
    Serial.println("Hug started at time: ");
    lastHug = millis();
    Serial.println(lastHug);
    hugging = true;
    
  }
  }
