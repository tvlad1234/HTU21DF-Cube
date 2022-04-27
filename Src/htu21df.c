#include "main.h"
#include "htu21df.h"

/** Read temperature register. */
#define HTU21DF_READTEMP (0xE3)

/** Read humidity register. */
#define HTU21DF_READHUM (0xE5)

/** Write register command. */
#define HTU21DF_WRITEREG (0xE6)

/** Read register command. */
#define HTU21DF_READREG (0xE7)

/** Reset command. */
#define HTU21DF_RESET (0xFE)

static const uint8_t HTU21DF_ADDR = 0x40 << 1; // Use 8-bit address
I2C_HandleTypeDef *htuPort;

uint8_t htuRead8(uint8_t a)
{
  uint8_t r;
  HAL_I2C_Master_Transmit(htuPort, HTU21DF_ADDR, &a, 1, HAL_MAX_DELAY);
  HAL_I2C_Master_Receive(htuPort, HTU21DF_ADDR, &r, 1, HAL_MAX_DELAY);
  return r;
}

void htuRead24(uint8_t a, uint8_t buf[])
{
  HAL_I2C_Master_Transmit(htuPort, HTU21DF_ADDR, &a, 1, HAL_MAX_DELAY);
  HAL_Delay(50);
  HAL_I2C_Master_Receive(htuPort, HTU21DF_ADDR, buf, 3, HAL_MAX_DELAY);
}

uint8_t htuBegin(I2C_HandleTypeDef *i2cdev)
{

  htuPort = i2cdev;
  if (htuRead8(HTU21DF_READREG) != 0x2)
    return 0;

  return 1;
}

float readHTUTemperature(void)
{

  uint8_t buf[3];
  htuRead24(HTU21DF_READTEMP, buf);
  uint16_t t = buf[0];
  t <<= 8;
  t |= buf[1] & 0b11111100;

  // 3rd byte is the CRC

  float temp = t;
  temp *= 175.72f;
  temp /= 65536.0f;
  temp -= 46.85f;
  return temp;
}

float readHTUHumidity(void)
{
  uint8_t buf[3];
  htuRead24(HTU21DF_READHUM, buf);

  uint16_t h = buf[0];
  h <<= 8;
  h |= buf[1] & 0b11111100;

  // 3rd byte is the CRC

  float hum = h;
  hum *= 125.0f;
  hum /= 65536.0f;
  hum -= 6.0f;
  return hum;
}
