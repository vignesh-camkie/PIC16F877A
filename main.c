#include <xc.h>
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
const char keypad[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

const unsigned char segment_map[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void init() {
    TRISB = 0x00;
    PORTB = 0x00;

    TRISD = 0xF8;
    PORTD = 0x00;
}

char read_keypad() {
    for (char row = 0; row < 4; row++) {
        PORTD = ~(1 << row);
        __delay_ms(5);
        for (char col = 0; col < 3; col++) {
            if (!(PORTD & (1 << (col + 4)))) {
                __delay_ms(20);
                if (!(PORTD & (1 << (col + 4)))) {
                    while (!(PORTD & (1 << (col + 4))));
                    return keypad[row][col];
                }
            }
        }
    }
    return 0;
}

void display_7seg(char key) {
    if (key >= '0' && key <= '9') {
        PORTB = segment_map[key - '0'];
    } else {
        PORTB = 0x00;
    }
}

void main() {
    init();

    char key;

    while (1) {
        key = read_keypad();
        if (key) {
            display_7seg(key);
        }
    }
}
