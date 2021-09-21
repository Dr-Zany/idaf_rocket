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

namespace MPU6050InterfaceTypes
{
/**
 * @brief FSYNC output values
 *
 * Allowed values for `setFsyncSampleOutput`.
 */
typedef enum fsync_out
{
  FSYNC_OUT_DISABLED,
  FSYNC_OUT_TEMP,
  FSYNC_OUT_GYROX,
  FSYNC_OUT_GYROY,
  FSYNC_OUT_GYROZ,
  FSYNC_OUT_ACCELX,
  FSYNC_OUT_ACCELY,
  FSYNC_OUT_ACCEL_Z,
} fsync_out_t;

/**
 * @brief Clock source options
 *
 * Allowed values for `setClock`.
 */
typedef enum clock_select
{
  INTR_8MHz,
  PLL_GYROX,
  PLL_GYROY,
  PLL_GYROZ,
  PLL_EXT_32K,
  PLL_EXT_19MHz,
  STOP = 7,
} clock_select_t;

/**
 * @brief Accelerometer range options
 *
 * Allowed values for `setAccelerometerRange`.
 */
typedef enum
{
  RANGE_2_G = 0b00,  ///< +/- 2g (default value)
  RANGE_4_G = 0b01,  ///< +/- 4g
  RANGE_8_G = 0b10,  ///< +/- 8g
  RANGE_16_G = 0b11, ///< +/- 16g
} accel_range_t;

/**
 * @brief Gyroscope range options
 *
 * Allowed values for `setGyroRange`.
 */
typedef enum
{
  RANGE_250_DEG,  ///< +/- 250 deg/s (default value)
  RANGE_500_DEG,  ///< +/- 500 deg/s
  RANGE_1000_DEG, ///< +/- 1000 deg/s
  RANGE_2000_DEG, ///< +/- 2000 deg/s
} gyro_range_t;

/**
 * @brief Digital low pass filter bandthwidth options
 *
 * Allowed values for `setFilterBandwidth`.
 */
typedef enum
{
  BAND_260_HZ, ///< Docs imply this disables the filter
  BAND_184_HZ, ///< 184 Hz
  BAND_94_HZ,  ///< 94 Hz
  BAND_44_HZ,  ///< 44 Hz
  BAND_21_HZ,  ///< 21 Hz
  BAND_10_HZ,  ///< 10 Hz
  BAND_5_HZ,   ///< 5 Hz
} bandwidth_t;

/**
 * @brief Periodic measurement options
 *
 * Allowed values for `setCycleRate`.
 */
typedef enum
{
  CYCLE_1_25_HZ, ///< 1.25 Hz
  CYCLE_5_HZ,    ///< 5 Hz
  CYCLE_20_HZ,   ///< 20 Hz
  CYCLE_40_HZ,   ///< 40 Hz
} cycle_rate_t;

struct VectorData3D
{
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
};

struct MPU6050Data
{
  VectorData3D gyro;
  VectorData3D accel;
  int16_t temp = 0;
};

}; // namespace MPU6050InterfaceTypes

class MPU6050Interface
{

protected:
  virtual ~MPU6050Interface() = default;
  i2c_inst_t *m_i2cInterface;
  uint8_t m_defaultAddress = 0x68;

public:
  MPU6050Interface(i2c_inst_t *i2cInterface) : m_i2cInterface(i2cInterface)
  {
  }
  virtual bool Init();

  virtual MPU6050InterfaceTypes::accel_range_t getAccelerometerRange(void);
  virtual void setAccelerometerRange(MPU6050InterfaceTypes::accel_range_t);

  virtual MPU6050InterfaceTypes::gyro_range_t getGyroRange(void);
  virtual void setGyroRange(MPU6050InterfaceTypes::gyro_range_t);

  virtual MPU6050InterfaceTypes::clock_select_t getClock(void);
  virtual void setClock(MPU6050InterfaceTypes::clock_select_t);

  virtual MPU6050InterfaceTypes::bandwidth_t getFilterBandwidth(void);
  virtual void setFilterBandwidth(MPU6050InterfaceTypes::bandwidth_t bandwidth);

  virtual MPU6050InterfaceTypes::MPU6050Data ReadData();
};
