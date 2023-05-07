
#include <avr/io.h>
#include <util/twi.h>

#include "i2c.h"
#include "config.h"

#define SCL_PRESCALER 1
#define PRESCALER_MASK 0xF8

void i2cInit(unsigned long frequency) {
  TWSR = 0;
	TWBR = (uint8_t)((((F_CPU / frequency) / SCL_PRESCALER) - 16) / 2);
}

bool i2cStart(uint8_t address, uint8_t mode) {
	uint8_t status;

	TWCR = 0;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	
	status = TW_STATUS & PRESCALER_MASK;
	if ((status != TW_START) && (status != TW_REP_START))
		return false;
	
	TWDR = (address << 1) | mode;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	status = TW_STATUS & PRESCALER_MASK;
	if ( (status != TW_MT_SLA_ACK) && (status != TW_MR_SLA_ACK) )
		return false;
	
	return true;
}

void i2cStop(void) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
};


bool i2cWrite(uint8_t data) {
  uint8_t status;

  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));

  status = TW_STATUS & PRESCALER_MASK;
  if( status != TW_MT_DATA_ACK)
		return false;
	
	return true;
}


uint8_t i2cRead(bool ack) {
  if (ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  } else {
    TWCR = (1 << TWINT) | (1 << TWEN);
  }

  while (!(TWCR & (1 << TWINT)));

  return TWDR;
}

bool i2cSendByte(uint8_t address, uint8_t data) {
  bool status = i2cStart(address, WRITE);
  while (!status) {}
  
  status = i2cWrite(data);
  while (!status) {}

  i2cStop();
  return status;
}

bool i2cSendMessage(uint8_t address, uint8_t* data, uint16_t length) {
  bool status = i2cStart(address, WRITE);
  while (!status) {}
  
  for (uint16_t i = 0; i < length; i++) {
    status = i2cWrite(data[i]);
    while (!status) {}
  }

  i2cStop();

  return status;
}

bool i2cReadMessage(uint8_t address, uint8_t* data, uint16_t length) {
	bool status = i2cStart(address, READ);
	while (!status) {}
	
	for (uint16_t i = 0; i < (length-1); i++) {
		data[i] = i2cRead(true);
	}
	data[(length-1)] = i2cRead(false);
	
	i2cStop();
	
	return true;
}

