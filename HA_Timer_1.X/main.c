/*
 * File:   main.c
 * Author: Hossam Eldeen Altokhy
 *
 * Created on April 4, 2020, 6:24 PM
 */
#define F_CPU 16000000UL

// Built-in headers
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User-defined Headers
#include "Config.h"
#include "DIO.h"
#include "lcd.h"
#include "ADC.h"
#include "Timer.h"

#define BUTTON2        2
#define LED            3
#define Buzzer         3
#define LM35            1
#define Relay           2

#define portA           1
#define portB           2
#define portC           3
#define portD           4


char str1[] = "Volt = ";
char str2[] = " mV";
char cl[] = "    ";

ISR(INT0_vect) {
    static int i = 1;

    if (i) {
        startConv();
        i = 0;
    }
}

ISR(ADC_vect) {
    char buffer[20];
    int noOfSteps = getADCdata();


    // convert steps to mV
    int data = (5 * noOfSteps) / 1.024;
    
    // Display
    itoa(data, buffer, 10);
    if(data>2500){
        setPINA(Relay);
    }
    else{
        resetPIN(Relay,portA);
    }
    LCD_String_xy(0, 7, cl);
    LCD_String_xy(0, 7, buffer);
    
    _delay_ms(1000);

//    startConv();
}

void INT0_init() {
    MCUCR |= (1 << ISC01) | (1 << ISC00); // Rising Edge
    GICR |= (1 << INT0);
}

int main(void) {

    PINAas(Relay, OUT);
    resetPIN(Relay,portA);
    PINDas(LED2,OUT);
    INT0_init();
    LCD_Init();
    ADC_init(); // Sensor on ADC0
    selectChannel(LM35);
    sei();
    LCD_String_xy(0, 0, str1);
    LCD_String_xy(0, 13, str2);
    //    startConv();

    while (1) {



    }
}













