/*
A library for reading the acceleration, angular velocity and temperature values from the 
LSM6DS3 sensor. 

This uses the SPI protocol with the standard MOSI, MISO and CLK pins, but the CS pin can be
specified by the user.

The sensor operates at the high-performance 416Hz mode. This can be changed at your own risk 
by refering to the datasheet and changing the control bytes in the begin function acordingly
(see registers 0x10 and 0x11 in the datasheet).

This library was designed on the esp32s3 chip with a custom microcontroller. It should work on
most arduino-ide compatible architectures but this is not guaranteed as the esp32s3 is the only
platform it was tested on.


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/



#include "LSM6DS3.h"
//initialize sensor object. arguments are SPI CS pin, accelerometer range (in g, can be 2, 4, 8 or 16 (in units of g), defaults to 2 if other value is passed)
// and gyroscope range (125, 250, 500, 1000, 2000 (deg/sec). defaults to 125 if other values are passed)
LSM6 sensor(10, 8,250);

void setup() {
  // Wait for initialization, start sensor with specified sensors.
  Serial.begin(9600);
  while(!Serial){}
  sensor.begin();
  
}

void loop() {
  
  
  // A loop that uses all methods in the library. 
  //the value in brackets is optional, they represent zero-point calibrations for the respective measurement
  //(i.e. the value these take when the expected value is zero. default=0)
  Serial.print("x:");
  Serial.print(sensor.xl_x(0.1));
  Serial.print(" y:");
  Serial.print(sensor.xl_y(-0.05));
  Serial.print(" z:"); //units m/s^2
  Serial.println(sensor.xl_z(0.2));
  Serial.print("gx:");
  Serial.print(sensor.g_x(3.6));
  Serial.print(" gy:"); //deg/sec
  Serial.print(sensor.g_y(-4.7));
  Serial.print(" gz:");
  Serial.println(sensor.g_z(-3.8));
  Serial.print("Temp:"); //C
  Serial.println(sensor.temp(-3.1));
  delay(500);


}
