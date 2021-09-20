/**
 * @file mpu6050Interface.hpp
 * @author noel
 * @brief
 * @version 0.1
 * @date 2021-09-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "stdio.h"

struct VectorData3D
{
  uint16_t x = 0;
  uint16_t y = 0;
  uint16_t z = 0;
};

class MPU6050Interface
{
private:
  virtual ~MPU6050Interface();
  i2c_inst_t *m_i2cInterface;

public:
  MPU6050Interface(i2c_inst_t *i2cInterface);
  virtual int mpu6050Init() virtual VectorData3D rea;
};
