#include <Arduino.h>
#include <SmallFSR.h>
#include <WiFi101.h>


SmallFSR::SmallFSR(WiFiClient client, int pin, int mapping) {
    _pin = pin;
    _client = client;
    _mapping = mapping;
}


void SmallFSR::send(){
    int value = analogRead(_pin);
    // Map the 0-1023 value to 0-40
    int position = map(value, 0, 1023, 0, _mapping);
    Serial.print(position);
    if(checkAction(position)){
        Serial.print ("CARESS DONE");
        _client.write('c');
    }
}

bool SmallFSR::checkAction(int value){

    if(value < 5){
        p1 = true;
        p2 = false;
        p3 = false;
    }
    if(value >= 5 && value < 15){
        if (p1 == true){
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