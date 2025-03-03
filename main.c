// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000

const unsigned char segment_code[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};

void main() {
    unsigned char count = 0;
    unsigned char prev_state = 1;

    TRISD = 0x00;
    TRISB = 0x01;
    PORTD = 0x00;
    PORTB = 0x00;
    OPTION_REG &= 0x7F;

    while (1) {
        unsigned char current_state = PORTB & 0x01;

        if (current_state == 0 && prev_state == 1) {
            __delay_ms(10);
            if ((PORTB & 0x01) == 0) {
                count = (count + 1) & 0x0F;
                PORTD = segment_code[count];
            }
        }

        prev_state = current_state;
    }
}
