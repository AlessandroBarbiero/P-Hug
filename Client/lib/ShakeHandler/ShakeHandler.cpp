#include <ShakeHandler.h>

ShakeHandler::ShakeHandler(int duration, Ear ear1, Ear ear2){
    _duration = duration;
    _ear1 = ear1;
    _ear2 = ear2;
}

WiFiClient ShakeHandler::getClient(){
    return _client;
}

Accelerometer ShakeHandler::getAccelerometer(){
    return _accelerometer;
}

unsigned long ShakeHandler::getActivationTime(){
    return _activationTime;
}

int ShakeHandler::getDuration(){
    return _duration;
}

void ShakeHandler::setClient(WiFiClient client){
    _client = client;
}

void ShakeHandler::setActivationTime(){
    _activationTime = millis();
}

void ShakeHandler::setSpeaker(Speaker speaker){
    _speaker = speaker;
}

void ShakeHandler::setAccelerometer(Accelerometer accelerometer){
    _accelerometer = accelerometer;
}

void ShakeHandler::run(){
    _accelerometer.run();
    if(!_isShaking && (abs(_accelerometer.getGyroX()) > 2 || abs(_accelerometer.getGyroY()) > 2 || abs(_accelerometer.getGyroZ()) > 2)){
        _isShaking = true;
        setActivationTime();
    }
    if(abs(_accelerometer.getGyroX()) < 1 && abs(_accelerometer.getGyroY()) < 1 && abs(_accelerometer.getGyroZ()) < 1){
        _isShaking = false;
    }
    if(_isShaking && millis() >= getActivationTime() + _duration){
        getClient().write("s");
        Serial.print("Shake");
        _ear1.shake();
        _ear2.shake();
        _speaker.shake();
        _isShaking = false;
    }
}

