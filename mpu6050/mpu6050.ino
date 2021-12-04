#include <RH_ASK.h>
#include <SPI.h>
//#include <ServoTimer2.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.

RH_ASK rf_driver;

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data

boolean cal = true;
int cal_num = 0;
long calx = 0;
long caly = 0;
long calz = 0;
float pitch,roll;
int p1, p2, p3, p4;
String message;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  rf_driver.init();
}
void loop() {
  gyro();
  rf_inputs();
  p1 = message.substring(0,4).toInt();
  p2 = message.substring(0,4).toInt();
  p3 = message.substring(0,4).toInt();
  p4 = message.substring(0,4).toInt();
}

void rf_inputs() {
  uint8_t buf[6];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen)) {
    // Message received with valid checksum
    message = (String((char *)buf));
  }
}

void gyro() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  
  // print out data
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  //Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  //Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read();
  if (cal) {
    calx+=gyro_x;
    caly+=gyro_y;
    calz+=gyro_z;
    cal_num+=1;
  }
  if (cal_num == 1000) {
    cal = false;
    cal_num = 0;
    calx/=1000;
    caly/=1000;
    calz/=1000;
  }
  gyro_x-=calx;
  gyro_y-=caly;
  gyro_z-=calz;

  roll = gyro_x/131.0;
  pitch = gyro_y/131.0;
}
