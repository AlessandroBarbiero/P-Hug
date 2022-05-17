#include <Speaker.h>

Speaker::Speaker(){
}

void Speaker::setup(){
    Serial1.begin(9600);
    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!_myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while(true){
        delay(0); // Code to compatible with ESP8266 watch dog.
        }
    }
    Serial.println(F("DFPlayer Mini online."));
    _myDFPlayer.volume(25);  //Set volume value. From 0 to 30
    _myDFPlayer.play(1);  //Play the first mp3

}

void Speaker::run(){
    

}