/**
 * @file mpl3155a2Driver.hpp
 * @author Dr-Zany
 * @brief
 * @version 0.1
 * @date 2021-09-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mpl3155a2Interface.hpp"

class MPL3155a2Driver : public MPL3155a2Interface
{
private:
public:
  MPL3155a2Driver(i2c_inst_t *i2cInterface);
  ~MPL3155a2Driver();
  bool Init(void) override;
  bool DataReady(void) override;
  uint32_t DataRead(void) override;
};
