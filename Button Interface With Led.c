#include <xc.h>

// Configuration bits
#pragma config FOSC = XT     // Oscillator Selection
#pragma config WDTE = OFF    // Watchdog Timer Disable
#pragma config PWRTE = ON    // Power-up Timer Enable
#pragma config BOREN = ON    // Brown-out Reset Enable
#pragma config LVP = OFF     // Low Voltage Programming Disable
#pragma config CPD = OFF     // Data EEPROM Memory Code Protection
#pragma config WRT = OFF     // Flash Program Memory Write Protection
#pragma config CP = OFF      // Flash Program Memory Code Protection

#define _XTAL_FREQ 4000000  // Define clock frequency (4MHz)

void main() {
    TRISB = 0x01;  // Set RB0 as input (0x01 means 00000001) and RB1 as output
    PORTB = 0x00;  // Clear PORTB

    while (1) {
        if ((PORTB & 0x01) == 0x01) {  // Check if RB0 is high (button pressed)
            PORTB |= 0x02;             // Set RB1 high (turn on LED)
        } else {
            PORTB &= 0xFD;             // Clear RB1 (turn off LED)
        }
    }
}
