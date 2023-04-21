#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void i2cInit();
void i2cStart();
void i2cStop();
void i2cWrite(uint8_t data);
uint8_t i2cRead(uint8_t ack);


#endif // I2C_H