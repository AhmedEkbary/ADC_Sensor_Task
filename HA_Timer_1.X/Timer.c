/*
 * File:   Timer.c
 * Author: ADMIN
 *
 * Created on April 25, 2020, 7:16 AM
 */


#include <avr/io.h>

#include "DIO.h"

void Timer0_init() {
    //    TCCR0 |= (1<<CS02) | (1<<CS00); //Clk / 1024 Normal Mode
    TCCR0 |= (1<<COM00) | (1 << CS02) | (1 << CS00) | (1 << WGM01); //Clk / 1024 CTC Mode

//    TIMSK |= (1 << TOIE0); //EN overflow interrupt of timer 0
        TIMSK |= (1 << OCIE0); 
        OCR0=0x80;
        PINBas(3,OUT);

}