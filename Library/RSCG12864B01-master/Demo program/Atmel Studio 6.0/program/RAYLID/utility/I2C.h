#ifndef I2C_h
#define I2C_h

void I2C_init(void);
uint8_t I2C_start(void);
void I2C_stop(void);
uint8_t I2C_to_write(void);
uint8_t I2C_send(uint8_t data);

#endif
