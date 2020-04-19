/*	Author: jmach017
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//#include "RIMS.h"
enum States{Start, Off, preOn,On,preOff}state;

void Tick(){
	switch(state)//transitions 
	{
	case Start: state = Off; break;
	case Off:
		if((PINA&0x01)==0x01)
		{state = preOn;} break;
	case preOn:
		if((PINA&0x01)==0x00)
		{state = On;}break;
	case On:
		if((PINA&0x01)==0x01)
		{state = preOff;}break;
	case preOff: 
		if((PINA&0x01)==0x00)
		{state = Off;}break;
	default: state = Start; break;
	}

	switch(state) //State actions
	{
	case Start: break;
	case Off:
	case preOff:
	PORTB = 0x01;break;
	case On:
	case preOn:
	PORTB = 0x02;break;
	default: break;
	
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
