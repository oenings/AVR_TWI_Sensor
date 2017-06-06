/*
 * UART.h
 *
 * Created: 26.05.2017 10:13:34
 *  Author: Frank Oenings
 */ 

#ifndef UART_H_
#define UART_H_

void UARTInit()
{
	UBRRL=0x17;		// Baudrate 9600
	UCSRB=0x18;		// RXEN=1, TXEN=1
	UCSRC=0x86;		// Async. Mode, keine Parität
	// 8 Datenbit, 1 Stoppbit
}

void UARTPutChar(uint8_t val)
{
	while(!(UCSRA&(1<<UDRE)));	// warte auf freies Senderegister
	UDR=val;					// sende Daten
}

void UARTPutDecimal(uint8_t byte)
{
	UARTPutChar(0x30 + (byte/100));				// Hunderter
	UARTPutChar(0x30 + ((byte/10) % 10));		// Zehner
	UARTPutChar(0x30 + (byte % 10));			// Einer
}

void UARTPutBinary(uint8_t byte)
{
	uint8_t bit;
	
	for (bit=7; bit < 255; bit--)
	{
		if ( byte & (1<<bit) )
		UARTPutChar('1');
		else
		UARTPutChar('0');
	}
}

#endif /* UART_H_ */