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
enum States{Start,idle,active,preOpen,open}state;
unsigned char code;
char getX()
{
return PINA&0x01;
}
char getY()
{
return (PINA>>1)&0x01;
}
char getPound(){
return (PINA>>2)&0x01;
}
char getInside(){
return (PINA>>7)&0x01;
}
void Tick(){
	switch(state)//transitions 
	{
	case Start: state = idle; break;
	case idle: if(getPound() ==0x01){state = active;}break;
	case active: 
		if(getX()==0x01){state = idle;}
		else if(getInside()==0x01){state = idle;}
		else if(getY() ==0x01 && getPound() ==0x00){state = preOpen;}break;	
	case preOpen: if(getY()==0x00){state = open;}
			else if(getX()==0x01 || getPound() ==0x01 || getInside() == 0x01){state =idle;} break;
	case open: if(getX()==0x01 || getY() == 0x01 || getInside() == 0x01){state = idle;}
			if(getPound() == 0x01){state = active;}break;
	default: state = Start; break;
	}

	switch(state) //State actions
	{
	case Start: break;
	case idle: PORTB = 0x00; PORTC = state; break;
	case active:  PORTB = 0x00; PORTC = state; break;
	case preOpen:  PORTB = 0x01;PORTC = state; break;
	case open: PORTB = 0x01; PORTC = state;break;
	default: break;
	
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
