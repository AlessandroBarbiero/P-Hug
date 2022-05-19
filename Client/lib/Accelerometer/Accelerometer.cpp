#include <Accelerometer.h>


Accelerometer::Accelerometer() {
}

void Accelerometer::setup(){
  while (!_mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(1000);
  }
  Serial.println("MPU6050 chip configured");
  _mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  _mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  _mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
};

float Accelerometer::getTemperature(){
  return _temp;
}

float Accelerometer::getAccelerationX(){
  return _accX;
}

float Accelerometer::getAccelerationY(){
  return _accY;
}

float Accelerometer::getAccelerationZ(){
  return _accZ;
}

float Accelerometer::getGyroX(){
  return _gyroX;
}

float Accelerometer::getGyroY(){
  return _gyroY;
}

float Accelerometer::getGyroZ(){
  return _gyroZ;
}

void Accelerometer::setClient(WiFiClient client){
    _client = client;
}

void Accelerometer::run(){
  sensors_event_t a, g, temp;
  _mpu.getEvent(&a, &g, &temp);
  _temp = temp.temperature;
  _accX = a.acceleration.x;
  _accY = a.acceleration.y;
  _accZ = a.acceleration.z;
  _gyroX = g.gyro.x;
  _gyroY = g.gyro.y;
  _gyroZ = g.gyro.z;
}

void Accelerometer::send(){
  
}

void Accelerometer::print(){
  Serial.print("Temperature:");
  Serial.print(getTemperature());
  Serial.print("\tx-acceleration:");
  Serial.print(getAccelerationX());
  Serial.print("\ty-acceleration:");
  Serial.print(getAccelerationY());
  Serial.print("\tz-acceleration:");
  Serial.print(getAccelerationZ());
  Serial.print("\tx-gyro:");
  Serial.print(getGyroX());
  Serial.print("\ty-gyro:");
  Serial.print(getGyroY());
  Serial.print("\tz-gyro:");
  Serial.println(getGyroZ());
  
}