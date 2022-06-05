#include <Accelerometer.h>

Accelerometer::Accelerometer(){

}

Accelerometer::Accelerometer(MPU6050 *mpu6050) {
  _mpu6050 = mpu6050;
}

void Accelerometer::setup(){
  Wire.begin();
  (*_mpu6050).begin();
  (*_mpu6050).calcGyroOffsets(false);
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
  (*_mpu6050).update();
  _temp = (*_mpu6050).getTemp();
  _accX = (*_mpu6050).getAccX();
  _accY = (*_mpu6050).getAccY();
  _accZ = (*_mpu6050).getAccZ();
  _gyroX = (*_mpu6050).getGyroX();
  _gyroY = (*_mpu6050).getGyroY();
  _gyroZ = (*_mpu6050).getGyroZ();
  print();
}

void Accelerometer::send(){
  
}

void Accelerometer::print(){
  Serial.println("=======================================================");
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
   Serial.println("=======================================================");  
}