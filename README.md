This is a library allowing simple interface with the LSM6DS3 sensor, with simple functions to read out the accelerometer, gyroscope and temperatue sensor via SPI. This library has only been tested on the ESP32S3 platform. The available functions are found below:
+ .begin() initializes the sensor. It takes as arguments the CS pin, the acceleration measurement range(in g) and the gyroscope measurement range(in deg/sec).
+ .xl_x, xl_y and xl_z take a zero-g calibration value as a optional argument(default = 0) and return acceleration values for the respective axis (in m/sec^2).
+ .g_x, g_y and g_z take a zero-rate calibration value as a optional argument(default = 0) and return the gyroscope reading for the axis (in deg/sec)
+ temp takes takes a zero-degree calibration value as a optional argument(default = 0) and returns the temperature value (in C)

A sensor rate of 416 Hz is used for both the accelerometer and the gyroscope. The default MISO, MOSI and CLK pins are also used, as this relies on the arduino SPI.h library.
