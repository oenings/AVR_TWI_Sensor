/*
 * TWI.h
 *
 * Created: 26.05.2017 10:13:05
 *  Author: Frank Oenings
 */ 

#ifndef TWI_H_
#define TWI_H_

uint8_t TWI_START()
{
	TWCR = 0b10100100;			// TWINT=1, TWSTA=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWSR&0xF8);			// Status zurückgeben
}

uint8_t TWI_SLA_R()
{
	TWDR = 0b10010001;			// Slave-Adresse 0x90+R
	TWCR = 0b10000100;			// TWINT=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWSR&0xF8);			// Status zurückgeben
}

uint8_t TWI_SLA_W()
{
	TWDR = 0b10010000;			// Slave-Adresse 0x90+W
	TWCR = 0b10000100;			// TWINT=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWSR&0xF8);			// Status zurückgeben
}

uint8_t TWI_SEND_DATA(uint8_t data)
{
	TWDR = data;
	TWCR = 0b10000100;			// TWINT=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWSR&0xF8);			// Status zurückgeben
}

uint8_t TWI_RECV_ACK()
{
	TWCR = 0b11000100;			// TWINT=1, TWEA=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWDR);				// Daten zurückgeben
}

uint8_t TWI_RECV_NACK()
{
	TWCR = 0b10000100;			// TWINT=1, TWEN=1
	while(!(TWCR&(1<<TWINT)));	// warte auf TWINT=1
	return(TWDR);				// Daten zurückgeben
}

#endif /* TWI_H_ */