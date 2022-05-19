#include <Arduino.h>
#include <SmallFSR.h>
#include <WiFi101.h>


SmallFSR::SmallFSR(WiFiClient client, int pin, int trigger, int duration) {
    _pin = pin;
    _client = client;
    _trigger = trigger;
    _duration = duration;
}

unsigned long SmallFSR::getActivationTime(){
    return _activationTime;
}

bool SmallFSR::isActive(){
    return _active;
}

int SmallFSR::getDuration(){
    return _duration;
}

void SmallFSR::setActive(bool isActive){
    _active = isActive;
}

void SmallFSR::setActivationTime(){
    _activationTime = millis();
}

void SmallFSR::setClient(WiFiClient client){
    _client = client;
}

void SmallFSR::send(){
    int value = analogRead(_pin);
    Serial.println(value);
    if(value > _trigger){
        Serial.println("Caress done");
        _client.write('c');
    }
}

void SmallFSR::start(){
    int value = analogRead(_pin);
    Serial.println(value);
    if(value > _trigger){
        setActive(true);
        setActivationTime();
        Serial.println("Touched");
    }
    if(millis() > getActivationTime() + getDuration() && isActive()){
        setActive(false);
        Serial.println("Duration expired");
    }
}