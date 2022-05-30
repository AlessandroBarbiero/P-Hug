#include <HugHandler.h>

HugHandler::HugHandler(LongFSR longFSR, Ear ear1, Ear ear2){
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
        getClient().write('h');
        _ear1.hug();
        _ear2.hug();
        //_speaker.hug();
    }
    else{
        _ear1.idle();
        _ear2.idle();
    }
}