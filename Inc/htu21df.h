#ifndef _HTU21DF_H
#define _HTU21DF_H

// Sensor Init function
uint8_t htuBegin(I2C_HandleTypeDef *i2cdev);

float readHTUTemperature(void);
float readHTUHumidity(void);

#endif /* _HTU21DF_H */
