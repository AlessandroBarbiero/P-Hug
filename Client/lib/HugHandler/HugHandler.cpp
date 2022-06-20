#include <HugHandler.h>
#define MESSAGE_DELAY 6000
#define HUG_DURATION 5000

HugHandler::HugHandler(LongFSR longFSR, Ear ear1, Ear ear2){
    _messageTime = millis();
    _longFSR = longFSR;
    _ear1 = ear1;
    _ear2 = ear2;
}

WiFiClient HugHandler::getClient(){
    return _client;
}

void HugHandler::setClient(WiFiClient client){
    _client = client;
}

void HugHandler::setSpeaker(Speaker speaker){
    _speaker = speaker;
}

void HugHandler::run(){
    
    _longFSR.run();
    
    if(_longFSR.isActive()){
        if(millis() >= _messageTime + MESSAGE_DELAY){
            _messageTime = millis();
            getClient().write('h');
        }
        _activationTime = millis();
        _earsUp = false;
        _ear1.hug();
        _ear2.hug();
        _speaker.hug();
    }
    else{
        _ear1.idle();
        _ear2.idle();
        if(millis()>_activationTime + HUG_DURATION && !_earsUp){
            _ear1.connect();
            _ear2.connect();
            _earsUp = true;
        }
    }
}