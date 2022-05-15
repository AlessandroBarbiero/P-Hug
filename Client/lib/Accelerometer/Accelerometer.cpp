#include <Accelerometer.h>


Accelerometer::Accelerometer() {
}

void Accelerometer::setClient(WiFiClient client){
    _client = client;
}

void Accelerometer::send(){
}