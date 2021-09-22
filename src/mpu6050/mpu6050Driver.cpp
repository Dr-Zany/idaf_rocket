/**
 * @file mpu6050Driver.cpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mpu6050Driver.hpp"

using namespace MPU6050InterfaceTypes;

MPU6050Driver::MPU6050Driver(i2c_inst_t *i2cInterface) : MPU6050Interface(i2cInterface)
{
}

MPU6050Driver::~MPU6050Driver()
{
}

bool MPU6050Driver::Init()
{
  bool ret;
  uint8_t src[] = {RegAddr::PWR_MGMT_1, 0x00};
  ret = (bool)i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 2, false);
  return ret;
}

accel_range_t MPU6050Driver::getAccelerometerRange(void)
{
  uint8_t dst;
  uint8_t reg = RegAddr::ACCEL_CONFIG;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  return (accel_range_t)((dst >> 3) & 0b11);
}

void MPU6050Driver::setAccelerometerRange(accel_range_t accelRange)
{
  uint8_t data = accelRange;
  uint8_t src[] = {RegAddr::ACCEL_CONFIG, data << 3};
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 2, false);
}

gyro_range_t MPU6050Driver::getGyroRange(void)
{
  uint8_t dst;
  uint8_t reg = RegAddr::GYRO_CONFIG;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  return (gyro_range_t)((dst >> 3) & 0b11);
}

void MPU6050Driver::setGyroRange(gyro_range_t gyroRange)
{
  uint8_t data = gyroRange;
  uint8_t src[] = {RegAddr::GYRO_CONFIG, data << 3};
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 1, false);
}

clock_select_t MPU6050Driver::getClock(void)
{
  uint8_t dst;
  uint8_t reg = RegAddr::PWR_MGMT_1;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  return (clock_select_t)(dst & 0b111);
}
void MPU6050Driver::setClock(clock_select_t clockSelect)
{
  uint8_t src[] = {RegAddr::GYRO_CONFIG, clockSelect};
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 1, false);
}

bandwidth_t MPU6050Driver::getFilterBandwidth(void)
{
  uint8_t dst;
  uint8_t reg = RegAddr::CONFIG;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  return (bandwidth_t)(dst & 0b111);
}

void MPU6050Driver::setFilterBandwidth(bandwidth_t bandwidth)
{
  uint8_t dst;
  uint8_t reg = RegAddr::CONFIG;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, &dst, 1, false);
  dst = dst & ~((uint8_t)bandwidth);
  dst = dst | ((uint8_t)bandwidth);
  uint8_t src[] = {RegAddr::CONFIG, dst};
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, src, 1, true);
}

// 0b0000 0000 0000 0000
MPU6050Data MPU6050Driver::ReadData()
{
  uint8_t dst[14];
  uint8_t reg = RegAddr::ACCEL_OUT;
  MPU6050Data ret;
  i2c_write_blocking(m_i2cInterface, m_defaultAddress, &reg, 1, true);
  i2c_read_blocking(m_i2cInterface, m_defaultAddress, dst, 14, false);
  ret.accel.x = (dst[0] << 8) + dst[1];
  ret.accel.y = (dst[2] << 8) + dst[3];
  ret.accel.z = (dst[4] << 8) + dst[5];
  ret.temp = (dst[6] << 8) + dst[7];
  ret.gyro.x = (dst[8] << 8) + dst[9];
  ret.gyro.y = (dst[10] << 8) + dst[11];
  ret.gyro.z = (dst[12] << 8) + dst[13];
  return ret;
}