# HTU21DF-Cube
HTU21DF Library for STM32Cube 

Based on [Adafruit_HTU21DF_Library](https://github.com/adafruit/Adafruit_HTU21DF_Library)

### Initializing the sensor
Before reading the sensor, it must be initialized with _htuBegin_.\
_htuBegin_ takes a pointer to the I2C Handler and returns 1 if connection was successful.\
_Example:_ `htuBegin(&hi2c1);`

### Reading the sensor
`readHTUTemperature()` returns the temperature in °C as _float_.
`readHTUHumidity()` returns the relative humidity as _float_.


