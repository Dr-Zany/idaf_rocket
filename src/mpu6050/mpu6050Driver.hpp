/**
 * @file mpu6050Driver.hpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mpu6050Interface.hpp"

class MPU6050Driver : public MPU6050Interface
{
private:
  enum RegAddr
  {
    I2CADDR_DEFAULT = 0x68,   ///< MPU6050 default i2c address w/ AD0 high
    DEVICE_ID = 0x68,         ///< The correct WHO_AM_I value
    SELF_TEST_X = 0x0D,       ///< Self test factory calibrated values register
    SELF_TEST_Y = 0x0E,       ///< Self test factory calibrated values register
    SELF_TEST_Z = 0x0F,       ///< Self test factory calibrated values register
    SELF_TEST_A = 0x10,       ///< Self test factory calibrated values register
    SMPLRT_DIV = 0x19,        ///< sample rate divisor register
    CONFIG = 0x1A,            ///< General configuration register
    GYRO_CONFIG = 0x1B,       ///< Gyro specfic configuration register
    ACCEL_CONFIG = 0x1C,      ///< Accelerometer specific configration register
    INT_PIN_CONFIG = 0x37,    ///< Interrupt pin configuration register
    WHO_AM_I = 0x75,          ///< Divice ID register
    SIGNAL_PATH_RESET = 0x68, ///< Signal path reset register
    USER_CTRL = 0x6A,         ///< FIFO and I2C Master control register
    PWR_MGMT_1 = 0x6B,        ///< Primary power/sleep control register
    PWR_MGMT_2 = 0x6C,        ///< Secondary power/sleep control register
    TEMP_H = 0x41,            ///< Temperature data high byte register
    TEMP_L = 0x42,            ///< Temperature data low byte register
    ACCEL_OUT = 0x3B,         ///< base address for sensor data read
  };

public:
  MPU6050Driver(i2c_inst_t *i2cInterface);
  ~MPU6050Driver();
  bool mpu6050Init() override;

  MPU6050InterfaceTypes::accel_range_t getAccelerometerRange(void) override;
  void setAccelerometerRange(MPU6050InterfaceTypes::accel_range_t) override;

  MPU6050InterfaceTypes::gyro_range_t getGyroRange(void) override;
  void setGyroRange(MPU6050InterfaceTypes::gyro_range_t) override;

  MPU6050InterfaceTypes::clock_select_t getClock(void) override;
  void setClock(MPU6050InterfaceTypes::clock_select_t) override;

  MPU6050InterfaceTypes::bandwidth_t getFilterBandwidth(void) override;
  void setFilterBandwidth(MPU6050InterfaceTypes::bandwidth_t bandwidth) override;

  MPU6050InterfaceTypes::MPU6050Data ReadData() override;
};
