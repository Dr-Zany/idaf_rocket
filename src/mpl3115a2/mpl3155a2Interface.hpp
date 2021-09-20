/**
 * @file mpl3155a2Interface.hpp
 * @author Dr-Zany
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

class MPL3155a2Interface
{
protected:
  i2c_inst_t *m_i2cInterface;
  uint8_t m_defaultAddress = 0xC0;

  virtual ~MPL3155a2Interface() = default;

public:
  MPL3155a2Interface(i2c_inst_t *i2cInterface) : m_i2cInterface(i2cInterface)
  {
  }

  virtual bool Init(void);
  virtual bool DataReady(void);
  virtual uint32_t DataRead(void);
};
