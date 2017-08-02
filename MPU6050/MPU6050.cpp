/*
MPU6050
Created by B3RTL1M
This code is completely open source, and you may edit it however you like. 

This code is just for demonstration purpose and the author can't be responsible
of the disfonctionning or destruction of some software or hardware.
*/

#include "MPU6050.h"
#include "Arduino.h"

MPU6050::MPU6050()
{
  Wire.begin();
  GyrRes = 131;
  AccRes = 16384;
}

byte MPU6050::readRegister(byte reg)
{
  byte val = -1;
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(MPU6050_ADDR, 1);
  if (1<= Wire.available()) {
    val = Wire.read();
  }
  return val;
}

void MPU6050::writeRegister(byte reg, byte val)
{
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);  // PWR_MGMT_1 register
  Wire.write(val);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

SpaceData MPU6050::getSpaceData()
{
  SpaceData val;
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(MPU6050_R_ACCEL_XOUT_H);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR,14,true);  // request a total of 14 registers
  val.Acc.X=(Wire.read()<<8|Wire.read())/AccRes;  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  val.Acc.Y=(Wire.read()<<8|Wire.read())/AccRes;  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  val.Acc.Z=(Wire.read()<<8|Wire.read())/AccRes;  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  val.Tmp=(Wire.read()<<8|Wire.read())/340.00+36.53;  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  val.Gyr.X=(Wire.read()<<8|Wire.read())/GyrRes;  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  val.Gyr.Y=(Wire.read()<<8|Wire.read())/GyrRes;  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  val.Gyr.Z=(Wire.read()<<8|Wire.read())/GyrRes;  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  return val;
}

