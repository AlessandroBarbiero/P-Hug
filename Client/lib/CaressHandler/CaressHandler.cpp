#include <CaressHandler.h>


CaressHandler::CaressHandler(SmallFSR smallFSR1, SmallFSR smallFSR2, SmallFSR smallFSR3, Ear ear1, Ear ear2){
    _duration = smallFSR1.getDuration() + smallFSR2.getDuration() + smallFSR3.getDuration();
    _smallFSR1 = smallFSR1;
    _smallFSR2 = smallFSR2;
    _smallFSR3 = smallFSR3;
    _ear1 = ear1;
    _ear2 = ear2;
}

WiFiClient CaressHandler::getClient(){
    return _client;
}

unsigned long CaressHandler::getActivationTime(){
    return _activationTime;
}

bool CaressHandler::getReady(){
    return _ready;
}

int CaressHandler::getDuration(){
    return _duration;
}

void CaressHandler::setActivationTime(unsigned long activationTime){
    _activationTime = activationTime;
}

void CaressHandler::setReady(bool ready){
    _ready = ready;
}

void CaressHandler::setClient(WiFiClient client){
    _client = client;
}

void CaressHandler::setSpeaker(Speaker speaker){
    _speaker = speaker;
}

void CaressHandler::run(){
    _smallFSR1.run();
    _smallFSR2.run();
    _smallFSR3.run();
    if(_smallFSR1.isActive() && !_smallFSR2.isActive() && !_smallFSR3.isActive()){
        setActivationTime(millis());
    }
    if(_smallFSR2.isActive() && !_smallFSR3.isActive() && millis() < getActivationTime() + getDuration()){
        setReady(true);
    }
    if(_smallFSR3.isActive() && getReady() && millis() < getActivationTime() + getDuration()){
        getClient().write("C");
        Serial.println(F("Caress Done"));
        _speaker.caress();
        _ear1.caress();
        _ear2.caress();
        setReady(false);
    }
}

