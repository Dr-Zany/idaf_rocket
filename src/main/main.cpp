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

#define PIN_MPU_I2C_SDA 4
#define PIN_MPU_I2C_SCL 5

#define PIN_MPL_I2C_SDA 10
#define PIN_MPL_I2C_SCL 11

#define MAX_STORAGE 4000

typedef enum
{
  IDLE,
  WATING_FOR_FIRST_MPL,
  MEASURING,
  SEND_DATA
} state_t;

int main()
{
  absolute_time_t timeOut;
  absolute_time_t timeNow;
  data_formate_t dataStorage[MAX_STORAGE];
  uint32_t dataStorageCounte = 0;
  uint32_t mplDataBuff;
  uint8_t timeCounter = 0;
  state_t state = IDLE;
  char buffChare = 0;

  stdio_init_all();

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);

  // mpu init
  i2c_init(i2c0, 100 * 1000);
  gpio_set_function(PIN_MPU_I2C_SCL, GPIO_FUNC_I2C);
  gpio_set_function(PIN_MPU_I2C_SDA, GPIO_FUNC_I2C);
  gpio_pull_up(PIN_MPU_I2C_SCL);
  gpio_pull_up(PIN_MPU_I2C_SDA);
  bi_decl(bi_2pins_with_func(PIN_MPU_I2C_SDA, PIN_MPU_I2C_SCL, GPIO_FUNC_I2C));
  MPU6050Driver mpu(i2c0);
  MPU6050InterfaceTypes::MPU6050Data data;
  mpu.Init();
  mpu.setAccelerometerRange(MPU6050InterfaceTypes::accel_range_t::RANGE_4_G);
  mpu.setGyroRange(MPU6050InterfaceTypes::gyro_range_t::RANGE_500_DEG);

  // mpl init
  i2c_init(i2c1, 100 * 1000);
  gpio_set_function(PIN_MPL_I2C_SCL, GPIO_FUNC_I2C);
  gpio_set_function(PIN_MPL_I2C_SDA, GPIO_FUNC_I2C);
  gpio_pull_up(PIN_MPL_I2C_SCL);
  gpio_pull_up(PIN_MPL_I2C_SDA);
  bi_decl(bi_2pins_with_func(PIN_MPL_I2C_SDA, PIN_MPL_I2C_SCL, GPIO_FUNC_I2C));
  MPL3155a2Driver mpl(i2c1);
  mpl.Init();

  while (true)
  {
    timeOut = make_timeout_time_ms(10);

    switch (state)
    {
    case IDLE:
      buffChare = getchar_timeout_us(0);
      if (buffChare == 's')
      {
        buffChare = 0;
        state = WATING_FOR_FIRST_MPL;
      }
      else if (buffChare == 'd')
      {
        buffChare = 0;
        state = SEND_DATA;
      }
      break;
    case WATING_FOR_FIRST_MPL:
      if (mpl.DataReady())
      {
        mplDataBuff = mpl.DataRead();
        timeCounter = 0;
        state = MEASURING;
      }
      break;
    case MEASURING:
      if (mpl.DataReady())
      {
        mplDataBuff = mpl.DataRead();
      }
      timeCounter++;
      if (timeCounter >= 10)
      {
        timeCounter = 0;
        data = mpu.ReadData();
        if (dataStorageCounte == MAX_STORAGE)
        {
          state = IDLE;
        }
        dataStorage[dataStorageCounte].altitude = mplDataBuff;
        dataStorage[dataStorageCounte].timeStampe = get_absolute_time()._private_us_since_boot;
        dataStorage[dataStorageCounte].accelX = data.accel.x;
        dataStorage[dataStorageCounte].accelY = data.accel.y;
        dataStorage[dataStorageCounte].accelZ = data.accel.z;
        dataStorage[dataStorageCounte].gyroX = data.gyro.x;
        dataStorage[dataStorageCounte].gyroY = data.gyro.y;
        dataStorage[dataStorageCounte].gyroZ = data.gyro.z;
        dataStorage[dataStorageCounte].temp = data.temp;
        dataStorageCounte++;
      }
      buffChare = getchar_timeout_us(0);
      if (buffChare == 'e')
      {
        buffChare = 0;
        state = IDLE;
      }

      break;
    case SEND_DATA:
      printf("timeStamp;accelx;accely;accelz;gyrox;gyroy;gyroz;temp;altitude\n");
      for (uint32_t i = 0; i < dataStorageCounte; i++)
      {
        printf("%lld;%d;%d;%d;%d;%d;%d;%d;%ld\n", dataStorage[i].timeStampe, dataStorage[i].accelX,
               dataStorage[i].accelY, dataStorage[i].accelZ, dataStorage[i].gyroX, dataStorage[i].gyroY,
               dataStorage[i].gyroZ, dataStorage[i].temp, dataStorage[i].altitude);
      }
      printf("%ld Data send\n", dataStorageCounte);
      dataStorageCounte = 0;
      state = IDLE;
      break;

    default:
      break;
    }
    timeNow = get_absolute_time();
    if (timeOut._private_us_since_boot < timeNow._private_us_since_boot)
    {
      // printf("#############loop too slow############\n");
    }

    busy_wait_until(timeOut);
  }
}