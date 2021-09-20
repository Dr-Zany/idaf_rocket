/**
 * @file mpl3155a2Driver.cpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mpl3155a2Driver.hpp"

MPL3155a2Driver::MPL3155a2Driver(i2c_inst_t *i2cInterface) : MPL3155a2Interface(i2cInterface)
{
}

MPL3155a2Driver::~MPL3155a2Driver()
{
}

bool MPL3155a2Driver::Init()
{
  uint8_t src[] = {0x26, 0xB8};
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 2, false);
}
bool MPL3155a2Driver::DataReady()
{
  uint8_t dst;
  uint8_t reg = 0x00;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  return (dst & 0x08);
}
uint32_t MPL3155a2Driver::DataRead()
{
  uint8_t dst[3];
  uint8_t reg = 0x01;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, dst, 3, false);
  return (dst[2] << 12) + (dst[1] << 4) + (dst[0] >> 4);
}