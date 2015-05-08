///*
//
//MinIMU-9-Arduino-AHRS
//Pololu MinIMU-9 + Arduino AHRS (Attitude and Heading Reference System)
//
//Copyright (c) 2011 Pololu Corporation.
//http://www.pololu.com/
//
//MinIMU-9-Arduino-AHRS is based on sf9domahrs by Doug Weibel and Jose Julio:
//http://code.google.com/p/sf9domahrs/
//
//sf9domahrs is based on ArduIMU v1.5 by Jordi Munoz and William Premerlani, Jose
//Julio and Doug Weibel:
//http://code.google.com/p/ardu-imu/
//
//MinIMU-9-Arduino-AHRS is free software: you can redistribute it and/or modify it
//under the terms of the GNU Lesser General Public License as published by the
//Free Software Foundation, either version 3 of the License, or (at your option)
//any later version.
//
//MinIMU-9-Arduino-AHRS is distributed in the hope that it will be useful, but
//WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
//more details.
//
//You should have received a copy of the GNU Lesser General Public License along
//with MinIMU-9-Arduino-AHRS. If not, see <http://www.gnu.org/licenses/>.
//
//*/
//
//#include <Wire.h>
//#include <L3G.h>
//#include <LSM303.h>
//
//L3G gyro;
//LSM303 compass;
//
//void I2C_Init()
//{
//  Wire.begin();
//}
//
//void Gyro_Init()
//{
//  gyro.init();
//  gyro.enableDefault();
//  gyro.writeReg(L3G::CTRL_REG4, 0x20); // 2000 dps full scale
//  gyro.writeReg(L3G::CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
//}
//
//void Read_Gyro()
//{
//  gyro.read();
//  
//  AN[0] = gyro.g.x;
//  AN[1] = gyro.g.y;
//  AN[2] = gyro.g.z;
//  gyro_x = SENSOR_SIGN[0] * (AN[0] - AN_OFFSET[0]);
//  gyro_y = SENSOR_SIGN[1] * (AN[1] - AN_OFFSET[1]);
//  gyro_z = SENSOR_SIGN[2] * (AN[2] - AN_OFFSET[2]);
//}
//
//void Accel_Init()
//{
//  compass.init();
//  compass.enableDefault();
//  switch (compass.getDeviceType())
//  {
//    case LSM303::device_D:
//      compass.writeReg(LSM303::CTRL2, 0x18); // 8 g full scale: AFS = 011
//      break;
//    case LSM303::device_DLHC:
//      compass.writeReg(LSM303::CTRL_REG4_A, 0x28); // 8 g full scale: FS = 10; high resolution output mode
//      break;
//    default: // DLM, DLH
//      compass.writeReg(LSM303::CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11
//  }
//}
//
//// Reads x,y and z accelerometer registers
//void Read_Accel()
//{
//  compass.readAcc();
//  
//  AN[3] = compass.a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
//  AN[4] = compass.a.y >> 4;
//  AN[5] = compass.a.z >> 4;
//  accel_x = SENSOR_SIGN[3] * (AN[3] - AN_OFFSET[3]);
//  accel_y = SENSOR_SIGN[4] * (AN[4] - AN_OFFSET[4]);
//  accel_z = SENSOR_SIGN[5] * (AN[5] - AN_OFFSET[5]);
//}
//
//void Compass_Init()
//{
//  // doesn't need to do anything because Accel_Init() should have already called compass.enableDefault()
//}
//
//void Read_Compass()
//{
//  compass.readMag();
//  
//  magnetom_x = SENSOR_SIGN[6] * compass.m.x;
//  magnetom_y = SENSOR_SIGN[7] * compass.m.y;
//  magnetom_z = SENSOR_SIGN[8] * compass.m.z;
//}

/*

MinIMU-9-Arduino-AHRS
Pololu MinIMU-9 + Arduino AHRS (Attitude and Heading Reference System)

Copyright (c) 2011 Pololu Corporation.
http://www.pololu.com/

MinIMU-9-Arduino-AHRS is based on sf9domahrs by Doug Weibel and Jose Julio:
http://code.google.com/p/sf9domahrs/

sf9domahrs is based on ArduIMU v1.5 by Jordi Munoz and William Premerlani, Jose
Julio and Doug Weibel:
http://code.google.com/p/ardu-imu/

MinIMU-9-Arduino-AHRS is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

MinIMU-9-Arduino-AHRS is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License along
with MinIMU-9-Arduino-AHRS. If not, see <http://www.gnu.org/licenses/>.

*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void I2C_Init()
{
  Wire.begin();
}

void Gyro_Init()
{
  gyro.begin();
//  gyro.enableDefault();
//  gyro.writeReg(L3G::CTRL_REG4, 0x20); // 2000 dps full scale
//  gyro.writeReg(L3G::CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
}

void Accel_Init()
{
  accel.begin();
  
//  compass.enableDefault();
//  switch (compass.getDeviceType())
//  {
//    case LSM303::device_D:
//      compass.writeReg(LSM303::CTRL2, 0x18); // 8 g full scale: AFS = 011
//      break;
//    case LSM303::device_DLHC:
//      compass.writeReg(LSM303::CTRL_REG4_A, 0x28); // 8 g full scale: FS = 10; high resolution output mode
//      break;
//    default: // DLM, DLH
//      compass.writeReg(LSM303::CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11
//  }
}


void Compass_Init()
{
  mag.begin();
  // doesn't need to do anything because Accel_Init() should have already called compass.enableDefault()
}

sensors_event_t event;

void Read_Compass()
{
  mag.getEvent(&event);
  
  magnetom_x = SENSOR_SIGN[6] * event.magnetic.x;
  magnetom_y = SENSOR_SIGN[7] * event.magnetic.y;
  magnetom_z = SENSOR_SIGN[8] * event.magnetic.z;
}

// Reads x,y and z accelerometer registers
void Read_Accel()
{
  accel.getEvent(&event);
  
  AN[3] = event.acceleration.x ; // shift left 4 bits to use 12-bit representation (1 g = 256)
  AN[4] = event.acceleration.y;
  AN[5] = event.acceleration.z;
  accel_x = SENSOR_SIGN[3] * (AN[3] - AN_OFFSET[3]);
  accel_y = SENSOR_SIGN[4] * (AN[4] - AN_OFFSET[4]);
  accel_z = SENSOR_SIGN[5] * (AN[5] - AN_OFFSET[5]);
}


void Read_Gyro()
{
  gyro.getEvent(&event);
  
  AN[0] = event.gyro.x;
  AN[1] = event.gyro.y;
  AN[2] = event.gyro.z;
  gyro_x = SENSOR_SIGN[0] * (AN[0] - AN_OFFSET[0]);
  gyro_y = SENSOR_SIGN[1] * (AN[1] - AN_OFFSET[1]);
  gyro_z = SENSOR_SIGN[2] * (AN[2] - AN_OFFSET[2]);
}


