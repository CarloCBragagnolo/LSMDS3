#ifndef LSM6DS3_H
#define LSM6DS3_H

#include "arduino.h"
#include "SPI.h"
#define ctrl_address_xl 0x10
#define ctrl_address_g 0x11
class LSM6
{
public:


    LSM6(int pin =10, int sens_xl = 2, int sens_g = 125);

    void begin();
    
    float xl_x(float zerogx = 0);
    
    float xl_y(float zerogy = 0);
    
    float xl_z(float zerogz = 0);

    float g_x(float zero_ratex = 0);

    float g_y(float zero_ratey = 0);

    float g_z(float zero_ratez = 0);
    
    float temp(float zero_temp = 0);
private:
    int CS_PIN;
    int sens_a;
    int sens_gyro;
};
#endif LSM6DS3_H