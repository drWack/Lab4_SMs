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
enum States{Start,idle,inc,dec,reset}state;
unsigned char C;
void Tick(){
	switch(state)//transitions 
	{
	case Start: state = idle; break;
	case idle:
		if((PINA&0x01)==0x01 && (PINA&0x02)==0x02)
		{state = reset;}
		else if((PINA&0x01)==0x01) {state =inc; if(C<9){C++;}}
		else if((PINA&0x02)==0x02){state = dec; if(C>0){C--;}}break;//single increment/decrement solved with the power of Mealy Machines
	case inc:
		if((PINA&0x01)==0x01 && (PINA&0x02) ==0x02)
		{state = reset;}
		if((PINA&0x01) != 0x01){state = idle;} break;
	case dec:
		if((PINA&0x01)==0x01 && (PINA&0X02)==0x02)
		{state = reset;}
		if((PINA&0x02) != 0x02){state = idle;}break;
	case reset: state = idle; break;
	default: state = Start; break;
	}

	switch(state) //State actions
	{
	case Start: break;
	case idle: PORTC = C; break;
	case inc:  PORTC = C; break;
	case dec:  PORTC = C; break;
	case reset: C = 0; PORTC = C;break;
	default: break;
	
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
	C = 7;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
