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
  stdio_init_all();
  i2c_init(i2c1, 100 * 1000);
  gpio_set_function(PIN_I2C_SCL, GPIO_FUNC_I2C);
  gpio_set_function(PIN_I2C_SDA, GPIO_FUNC_I2C);
  gpio_pull_up(PIN_I2C_SCL);
  gpio_pull_up(PIN_I2C_SDA);

  bi_decl(bi_2pins_with_func(PIN_I2C_SDA, PIN_I2C_SCL, GPIO_FUNC_I2C));
  while (true)
  {
    for (int addr = 0; addr < (1 << 7); addr++)
    {
      if (addr % 16 == 0)
      {
        printf("%02x ", addr);
      }
      int ret;
      uint8_t rxdata;
      if (reserved_addr(addr))
        ret = PICO_ERROR_GENERIC;
      else
        ret = i2c_read_blocking(i2c1, addr, &rxdata, 1, false);
      printf(ret < 0 ? "." : "@");
      printf(addr % 16 == 15 ? "\n" : "  ");
    }
  }
}