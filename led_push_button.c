#pragma config FOSC = HS        // High-speed Oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = OFF      // Power-up Timer disabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM Code Protection disabled
#pragma config WRT = OFF        // Flash Program Write Protection disabled
#pragma config CP = OFF         // Code Protection disabled

#include <xc.h>

#define _XTAL_FREQ 8000000  

void main() {
    TRISB = 0x02;  // binary 00000010
    PORTB = 0x00; 

    while (1) {
        if (RB1 == 1) { 
            PORTB = 0x01;
        } else {
            PORTB = 0x00;  
        }
    }
}
