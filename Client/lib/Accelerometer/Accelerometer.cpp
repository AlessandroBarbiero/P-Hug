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

void Accelerometer::setClient(WiFiClient client){
    _client = client;
}

void Accelerometer::send(){
}

void Accelerometer::print(){
  sensors_event_t a, g, temp;
  _mpu.getEvent(&a, &g, &temp);

  Serial.print("Temperature:");
  Serial.print(temp.temperature);
  Serial.print("\tx-acceleration:");
  Serial.print(a.acceleration.x);
  Serial.print("\ty-acceleration:");
  Serial.print(a.acceleration.y);
  Serial.print("\tz-acceleration:");
  Serial.print(a.acceleration.z);
  Serial.print("\tx-gyro:");
  Serial.print(g.gyro.x);
  Serial.print("\ty-gyro:");
  Serial.print(g.gyro.y);
  Serial.print("\tz-gyro:");
  Serial.println(g.gyro.z);
  
}