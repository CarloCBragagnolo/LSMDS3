#include "LSM6DS3.h"
#include "arduino.h"
#include "SPI.h"

int ctrl_byte;
LSM6::LSM6(int pin, int sens_xl, int sens_g):
CS_PIN(pin), sens_a(sens_xl), sens_gyro(sens_g){
}

void LSM6::begin(){

    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);

    SPI.begin();

    if (sens_a == 4){

        ctrl_byte = 0x68;
    }
    else if (sens_a == 8)
    {
        ctrl_byte = 0x6C;
    }
    else if (sens_a == 16)
    {
        ctrl_byte = 0x64;
    }
    else{

        ctrl_byte = 0x60;
    }
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(ctrl_address_xl);
    SPI.transfer(ctrl_byte);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();



    if (sens_gyro == 1000){

        ctrl_byte = 0x68;
    }
    else if (sens_gyro == 2000)
    {
        ctrl_byte = 0x6C;
    }
    else if (sens_gyro == 500)
    {
        ctrl_byte = 0x64;
    }
    else if (sens_gyro == 250){

        ctrl_byte = 0x60;
    }
    else{
        ctrl_byte = 0x62;
    }

    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(ctrl_address_g);
    SPI.transfer(ctrl_byte);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
            


}
float LSM6::xl_x(float zerogx){
    float sens_coeff = sens_a*0.0305;
    float ax;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x28);
    byte a = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x29);
    byte b = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_x = (static_cast<uint16_t>(b) << 8) | a;
    if(total_x >= 32768){                                               
        ax = ((total_x-65536) * sens_coeff *(0.00981))-zerogx; //result * sens. coeff * mg - zerog reading
    } else{
        ax = (total_x * sens_coeff *(0.00981))- zerogx;
    }

    return ax;
            


}
float LSM6::xl_y(float zerogy){
    float ay;
    float sens_coeff = sens_a*0.0305;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x2A);
    byte c = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x2B);
    byte d = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_y = (static_cast<uint16_t>(d) << 8) | c;
    if(total_y >= 32768){                                               
        ay = ((total_y-65536) * sens_coeff *(0.00981))-zerogy; //result * sens. coeff * mg - zerog reading
    } else{
        ay = (total_y * sens_coeff *(0.00981))- zerogy;
    }

    return ay;
            


}
float LSM6::xl_z(float zerogz){
    float az;
    float sens_coeff = sens_a*0.0305;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x2C);
    byte e = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x2D);
    byte f = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_z = (static_cast<uint16_t>(f) << 8) | e;
    if(total_z >= 32768){                                               
        az = ((total_z-65536) * sens_coeff *(0.00981))- zerogz ; //result * sens. coeff * mg - zerog reading
    } else{
        az = (total_z * sens_coeff *(0.00981))- zerogz ;
    }

    return az;      
}
float LSM6::g_x(float zero_ratex){
    float gx;
    float sens_coeff = sens_gyro*0.035;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x22);
    byte g = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x23);
    byte h = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_gx = (static_cast<uint16_t>(h) << 8) | g;
    if(total_gx >= 32768){                                               
        gx = ((total_gx-65536) * sens_coeff *(0.001))-zero_ratex; //result * sens. coeff  - zero reading
    } else{
        gx = (total_gx * sens_coeff *(0.001))-zero_ratex;
    }

    return gx;

}
float LSM6::g_y(float zero_ratey){
    float gy;
    float sens_coeff = sens_gyro*0.035;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x24);
    byte i = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x25);
    byte j = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_gy = (static_cast<uint16_t>(j) << 8) | i;
    if(total_gy >= 32768){                                               
        gy = ((total_gy-65536) * sens_coeff *(0.001))-zero_ratey; //result * sens. coeff  - zero reading
    } else{
        gy = (total_gy * sens_coeff *(0.001))-zero_ratey;
    }

    return gy;

}
float LSM6::g_z(float zero_ratez){
    float gz;
    float sens_coeff = sens_gyro*0.035;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x26);
    byte k = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x27);
    byte l = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_gz = (static_cast<uint16_t>(l) << 8) | k;
    if(total_gz >= 32768){                                               
        gz = ((total_gz-65536) * sens_coeff *(0.001))-zero_ratez; //result * sens. coeff  - zero reading
    } else{
        gz = (total_gz * sens_coeff *(0.001))-zero_ratez;
    }

    return gz;

}
float LSM6::temp(float zero_temp){
    float T;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x20);
    byte m = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    //delay(100);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(0x80 | 0x21);
    byte n = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    SPI.endTransaction();
    uint16_t total_T = (static_cast<uint16_t>(n) << 8) | m;
    if(total_T >= 32768){                                               
        T = (total_T-65536)*0.0625 + 25 - zero_temp ; //result * sens. coeff - zero reading
    } else{
        T = (total_T)*0.0625 + 25 - zero_temp;
    }
    return(T);

}
