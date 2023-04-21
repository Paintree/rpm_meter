#include "i2c.h"
#include "config.h"

#include <avr/io.h>
#include <util/twi.h>

#define TWI_FREQ 100000UL // I2C bus frequency in Hz
#define TWI_BITRATE ((F_CPU / TWI_FREQ) - 16) / 2


void i2cInit() {
  TWBR = TWI_BITRATE;
  TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWPS0);
}

void i2cStart() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  
  while (!(TWCR & (1 << TWINT)));
}

void i2cStop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}


void i2cWrite(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);

  while (!(TWCR & (1 << TWINT)));
}


uint8_t i2cRead(uint8_t ack) {
  if (ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  } else {
    TWCR = (1 << TWINT) | (1 << TWEN);
  }

  while (!(TWCR & (1 << TWINT)));

  return TWDR;
}