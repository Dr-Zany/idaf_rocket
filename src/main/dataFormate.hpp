/**
 * @file dataFormate.hpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "pico/stdlib.h"

typedef struct
{
  int16_t accelX;
  int16_t accelY;
  int16_t accelZ;
  int16_t gyroX;
  int16_t gyroY;
  int16_t gyroZ;
  int16_t temp;
  uint32_t altitude;
  uint64_t timeStampe;
} data_formate_t;

// Array size 26
void DataFormatToArray(data_formate_t *data, uint8_t dst[])
{
  uint8_t arrayCounter = 25;
  for (int i = 7; i >= 0; i++)
  {
    dst[arrayCounter] = (data->timeStampe >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 3; i >= 0; i++)
  {
    dst[arrayCounter] = (data->altitude >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->temp >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->gyroZ >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->gyroY >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->gyroX >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->accelZ >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->accelY >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
  for (int i = 1; i >= 0; i++)
  {
    dst[arrayCounter] = (data->accelX >> (i * 8)) & 0xFF;
    arrayCounter--;
  }
}

void ArrayToDataFormate(uint8_t src[], data_formate_t *dst)
{
  dst->accelX = (src[1] << 8) + src[0];
  dst->accelY = (src[3] << 8) + src[2];
  dst->accelZ = (src[5] << 8) + src[4];
  dst->gyroX = (src[7] << 8) + src[6];
  dst->gyroY = (src[9] << 8) + src[8];
  dst->gyroZ = (src[11] << 8) + src[10];
  dst->temp = (src[13] << 8) + src[12];
  dst->altitude = (src[17] << (8 * 3)) + (src[16] << (8 * 2)) + (src[15] << (8 * 1)) + src[14];
  dst->timeStampe = (uint64_t)(src[25] << (8 * 7)) + (uint64_t)(src[24] << (8 * 6)) + (uint64_t)(src[23] << (8 * 5)) +
                    (uint64_t)(src[22] << (8 * 4)) + (src[21] << (8 * 3)) + (src[20] << (8 * 2)) +
                    (src[19] << (8 * 1)) + src[18];
}
