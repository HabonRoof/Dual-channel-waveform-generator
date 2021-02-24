#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>


void I2C_init(void)
{
	TWBR = 0x80; // set the bit rate
	TWAR = 0x00; // set the slave address
	TWSR |= 0x00; // Set the division factor
	TWCR = 0X00;
	
	DDRC=DDRC&0XF7;//PC3 check LCD BUSY
	PORTC=PORTC|0X08;
}

void busy(void)
{
	while(PINC&0x08); //Check LCD busy
}
// Arbitration becomes host and sends START signal
// return value: 1 for success, 0 for failure
uint8_t I2C_start(void)
{
	busy();
	TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));
	if(((TWSR & 0xf8)!=0x08) && ((TWSR & 0xf8)!=0x10))
	return 0;
	return 1;
}

// stop communication and send STOP signal)`
void I2C_stop(void)
{
	TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

// Issued from the machine address and write command, that is, SLA + W, into the MT mode
// return value: 1 for success, 0 for failure
uint8_t I2C_to_write(void)
{
	TWDR=0;
	TWCR=(TWCR&0X0F)|(1<<TWINT)|(1<<TWEN);
	while(!(TWCR &(1<<TWINT)));
	if((TWSR & 0xf8)!=0x18)
	return 0;
	return 1;
}

// send data to the slave
// return value: 0 for failure, 1 for ACK, 2 for NOT ACK
uint8_t I2C_send(uint8_t data)
{
	busy();
	TWDR=data;
	TWCR=(TWCR&0X0F)|(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xf8)==0x28)
	return 1;
	else if((TWSR & 0xf8)==0x30)
	return 2;
	return 0;
}
