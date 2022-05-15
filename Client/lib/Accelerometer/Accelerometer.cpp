#include <Accelerometer.h>

Adafruit_MPU6050 mpu;

Accelerometer::Accelerometer() {
    while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(1000);
  }
}

void Accelerometer::setClient(WiFiClient client){
    _client = client;
}

void Accelerometer::send(){
}