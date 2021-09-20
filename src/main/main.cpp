/**
 * @file main.cpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "main.hpp"

#define PIN_I2C_SDA 26
#define PIN_I2C_SCL 27

bool reserved_addr(uint8_t addr)
{
  return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main()
{
  absolute_time_t timeOut;
  uint32_t mplData;
  stdio_init_all();
  i2c_init(i2c1, 100 * 1000);
  gpio_set_function(PIN_I2C_SCL, GPIO_FUNC_I2C);
  gpio_set_function(PIN_I2C_SDA, GPIO_FUNC_I2C);
  gpio_pull_up(PIN_I2C_SCL);
  gpio_pull_up(PIN_I2C_SDA);
  bi_decl(bi_2pins_with_func(PIN_I2C_SDA, PIN_I2C_SCL, GPIO_FUNC_I2C));

  MPL3155a2Driver mpl(i2c1);
  mpl.Init();
  // MPU6050Driver mpu6050(i2c1);
  // MPU6050InterfaceTypes::MPU6050Data data;
  // mpu6050.mpu6050Init();
  while (true)
  {
    timeOut = make_timeout_time_ms(10);
    // data = mpu6050.ReadData();
    // printf("Accale; x:%d y:%d z:%d\n", data.accel.x, data.accel.y, data.accel.z);
    // printf("Gyro; x:%d y:%d z:%d\n", data.gyro.x, data.gyro.y, data.gyro.z);
    // printf("Temp: %d", data.temp);
    if (mpl.DataReady())
    {
      mplData = mpl.DataRead();
      printf("altitute: %i", mplData);
    }
    busy_wait_until(timeOut);
  }
}