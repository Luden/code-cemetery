
#ifndef USI_I2C_H_
#define USI_I2C_H_

// I2C library using USI hardware support
// 2010 Kenneth Finnegan
// Heavily based on Atmel application note AVR310

#include <util/delay.h>
#include <avr/io.h>
#include <inttypes.h>

//#define PARAM_VERIFY
//#define SIGNAL_VERIFY
//#define NOISE_TESTING

#ifdef I2C_FAST_MODE
	#define I2C_T1	2 // >1.3us
	#define I2C_T2	1 // >0.6us
#else
	#define I2C_T1	5 // >4.7us
	#define I2C_T2	5 // >4.0us
#endif

// Bit & byte definitions
#define I2C_READ_BIT	0 // R/W bit position in device address byte
#define I2C_ADDR_BITS	1 // LSB position of device address
#define I2C_NACK_BIT	0 // Bit position of (N)ACK bit

#define TRUE 1
#define FALSE 0
#define I2C_READ 1
#define I2C_WRITE 0

// ERRORS
#define I2C_ERR_NO_DATA			0x01
#define I2C_ERR_DATA_OUT_OF_BND		0x02
#define I2C_ERR_UE_START		0x03
#define I2C_ERR_UE_STOP			0x04
#define I2C_ERR_UE_DATA_COL		0x05
#define I2C_ERR_NO_ACK_ON_DATA		0x06
#define I2C_ERR_NO_ACK_ON_ADDR		0x07
#define I2C_ERR_MISSING_START_CON	0x08
#define I2C_ERR_MISSING_STOP_CON	0x09

// Device port definitions
//#ifdef __ATtiny2313__
	#define I2C_DDR		DDRB
	#define I2C_PORT	PORTB
	#define I2C_PIN		PINB
	#define I2C_SDA		PB5
	#define I2C_SCL		PB7
//#endif

// Globals
union I2C_state {
	uint8_t errorState;
	struct {
		uint8_t addressByte	:1;
		uint8_t dataDirection	:1;
		uint8_t unused		:6;
	};
} I2C_state;

// Function Definitions
void I2C_init(void);
uint8_t I2C_xfer(uint8_t *buffer, uint8_t length);

// Private function definitions
uint8_t I2C_byte_xfer(uint8_t reg);
uint8_t I2C_gen_start(void);
uint8_t I2C_gen_stop(void);



#endif /* USI_I2C_H_ */