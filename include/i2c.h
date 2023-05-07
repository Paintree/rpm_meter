#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>
typedef enum {
    SCL_100 = 100000UL,
    SCL_400 = 400000UL,
} i2c_frequency;

typedef enum {
    WRITE = 0x00,
    READ =  0x01,
} i2c_mode;

void i2cInit(unsigned long frequency);
bool i2cStart(uint8_t address, uint8_t mode);
void i2cStop(void);
bool i2cWrite(uint8_t data);
uint8_t i2cRead(bool ack);
bool i2cSendByte(uint8_t address, uint8_t data);
bool i2cSendMessage(uint8_t address, uint8_t* data, uint16_t length);
bool i2cReadMessage(uint8_t address, uint8_t* data, uint16_t length);

#endif // I2C_H