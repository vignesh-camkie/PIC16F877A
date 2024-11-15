// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Disable (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (Write protection off)
#pragma config CP = OFF         // Code Protection (Program memory code protection off)

#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) {
    unsigned char segments_code[10] = {
        0x3F, // 0: a, b, c, d, e, f
        0x06, // 1: b, c
        0x5B, // 2: a, b, d, e, g
        0x4F, // 3: a, b, c, d, g
        0x66, // 4: b, c, f, g
        0x6D, // 5: a, c, d, f, g
        0x7D, // 6: a, c, d, e, f, g
        0x07, // 7: a, b, c
        0x7F, // 8: a, b, c, d, e, f, g
        0x6F  // 9: a, b, c, d, f, g
    };
    unsigned char counter = 0;
    
    TRISB = 0x00; 
    PORTB = 0x00; 

    while (1) {
        PORTB = segments_code[counter]; 
        __delay_ms(1000);               
        counter++;                     
        if (counter == 10) {        
            counter = 0;
        }
    }
}
