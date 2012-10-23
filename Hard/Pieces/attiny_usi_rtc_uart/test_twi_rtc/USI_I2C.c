#include "USI_I2C.h"

void I2C_delay(uint8_t length) {
	do {
		_delay_us(1);
	} while (--length);
}


void I2C_init(void) {
	// Set IO pins as output with pullup resistors
	I2C_PORT |= (1<<I2C_SDA) | (1<<I2C_SCL);
	I2C_DDR  |= (1<<I2C_SDA) | (1<<I2C_SCL);

	// Preload release of SDA
	USIDR = 0xFF;
	// Set USI in two wire mode, clock source USITC software strobe
	USICR = (1<<USIWM1) | (1<<USICS1) | (1<<USICLK);
	// Clear flags and counter
	USISR = (1<<USISIF) | (1<<USIOIF) | (1<<USIPF) | (1<<USIDC) | 
		(0x0<<USICNT0);
}

// Main I2C transfer function. First byte of the buffer should be:
// (I2C_DEV_ADDR << I2C_ADDR_BITS) | READ/WRITE
uint8_t I2C_xfer(uint8_t *buffer, uint8_t buflen) {
	// USISR for 8 bit xfer
	uint8_t SR_8bit = (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|
		(0x0<<USICNT0);
	// USISR for 1 bit xfer
	uint8_t SR_1bit = (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|
		(0xE<<USICNT0);

	I2C_state.errorState = 0;
	I2C_state.addressByte = TRUE;

	#ifdef PARAM_VERIFY
	if (buffer > (uint8_t*)RAMEND) {
		I2C_state.errorState = I2C_ERR_DATA_OUT_OF_BND;
		return FALSE;
	}
	if (buflen <= 1) {
		I2C_state.errorState = I2C_ERR_NO_DATA;
		return FALSE;
	}
	#endif

	// TODO NOISE_TESTING

	if ((buffer[0] & (1<<I2C_READ_BIT)) == I2C_READ) {
		I2C_state.dataDirection = I2C_READ;
	} else {
		I2C_state.dataDirection = I2C_WRITE;
	}

	I2C_gen_start();

	do {
		if (I2C_state.addressByte || 
				(I2C_state.dataDirection == I2C_WRITE)) {
			// Transmit a byte on the I2C bus
			// SCL low
			I2C_PORT &= ~(1<<I2C_SCL);
			// Load data register
			USIDR = *(buffer++);
			I2C_byte_xfer(SR_8bit);

			// Receive N/ACK from slave
			I2C_DDR &= ~(1<<I2C_SDA);
			if (I2C_byte_xfer(SR_1bit) & (1<<I2C_NACK_BIT)) {
				I2C_state.errorState = I2C_state.addressByte ?
					I2C_ERR_NO_ACK_ON_ADDR :
					I2C_ERR_NO_ACK_ON_DATA;
				return FALSE;
			}
			// Only one address byte
			I2C_state.addressByte = FALSE;
		} else {
			// Receive a byte on the I2C bus
			// Set SDA as input
			I2C_DDR &= ~(1<<I2C_SDA);
			// Pull byte off the bus
			*(buffer++) = I2C_byte_xfer(SR_8bit);

			// Transmit ACK or NACK data
			USIDR = (buflen == 1) ? 0xFF : 0x00;
			I2C_byte_xfer(SR_1bit);
		}
	} while (--buflen);

	I2C_gen_stop();

	return TRUE;
}

// Run the shift register until the counter overflows
// Function resets SDA line to output on return
uint8_t I2C_byte_xfer(uint8_t reg) {
	// Preset counter
	USISR = reg;
	// Setup control register for clock strobe
	reg = (1<<USIWM1) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);

	do {
		I2C_delay(I2C_T1);
		// Positive edge
		USICR = reg;
		// Wait for clock stretching
		while (!(I2C_PIN & (1<<I2C_SCL))) ;
		I2C_delay(I2C_T2);
		// Negative edge
		USICR = reg;
	} while (!(USISR & (1<<USIOIF)));

	I2C_delay(I2C_T1);
	// Save shift register
	reg = USIDR;
	// Release SDA
	USIDR = 0xFF;
	// Set SDA as output
	I2C_DDR |= (1<<I2C_SDA);

	return reg;
}

uint8_t I2C_gen_start(void) {
	// Release SCL
	I2C_PORT |= (1<<I2C_SCL);
	while(!(I2C_PORT & (1<<I2C_SCL))) ;
	#ifdef I2C_FAST_MODE
	I2C_delay(I2C_T2);
	#else
	I2C_delay(I2C_T1);
	#endif

	// Generate start condition
	I2C_PORT &= ~(1<<I2C_SDA);
	I2C_delay(I2C_T2);
	I2C_PORT &= ~(1<<I2C_SCL);
	I2C_PORT |=  (1<<I2C_SDA);

	#ifdef SIGNAL_VERIFY
	// Check that the start condition was detected
	if (!(USISR & (1<<USISIF))) {
		I2C_state.errorState = I2C_ERR_MISSING_START_CON;
		return FALSE;
	}
	#endif
	return TRUE;
}

uint8_t I2C_gen_stop(void) {
	// Pull SDA low
	I2C_PORT &= ~(1<<I2C_SDA);
	// Release SCL
	I2C_PORT |=  (1<<I2C_SCL);
	// Wait for SCL to release
	while(!(I2C_PIN & (1<<I2C_SCL))) ;
	I2C_delay(I2C_T2);
	I2C_PORT |= (1<<I2C_SDA);
	I2C_delay(I2C_T1);

	#ifdef SIGNAL_VERIFY
	if (!(USISR & (1<<USIPF))) {
		I2C_state.errorState = I2C_ERR_MISSING_STOP_CON;
		return FALSE;
	}
	#endif
	return TRUE;
}