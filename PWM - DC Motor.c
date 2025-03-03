#include <xc.h>

// Configuration Bits (adjust these according to your setup)
#pragma config FOSC = XT        // Oscillator Selection (XT Oscillator)
#pragma config WDTE = OFF      // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF     // Power-up Timer Enable (PWRT disabled)
#pragma config BOREN = ON      // Brown-out Reset Enable (BOR enabled)
#pragma config LVP = OFF       // Low-Voltage Programming Disable
#pragma config CPD = OFF       // Data EEPROM Memory Code Protection Disabled
#pragma config WRT = OFF       // Flash Program Memory Write Enable (Write protection off)
#pragma config CP = OFF        // Flash Program Memory Code Protection Disabled

#define _XTAL_FREQ 4000000 // 4 MHz

#define HBRIDGE_IN1 RB0
#define HBRIDGE_IN2 RB1
#define DEBUG_LED RD0

void PWM_Init(void);
void PWM_SetDutyCycle(unsigned int dutyCycle);
void Motor_SetDirection(unsigned char direction);

int main() {
    TRISB0 = 0; // RB0 out IN1
    TRISB1 = 0; // RB1 out IN2
    TRISC2 = 0; // RC2 out PWM output
    TRISD0 = 0; // RD0 to Debug LED

    PWM_Init();

    while (1) {

        Motor_SetDirection(1); // Forward dir
        PWM_SetDutyCycle(512); // 50% duty cycle
        DEBUG_LED = 1; //   LED on
        __delay_ms(2000);

        Motor_SetDirection(0); // Reverse dir
        PWM_SetDutyCycle(768); // 75% duty cycle
        DEBUG_LED = 0; //  off LED
        __delay_ms(2000);

        PWM_SetDutyCycle(0);      // Stop motor/ 0% duty cycle
        __delay_ms(2000);
    }

    return 0;
}


void PWM_Init(void) {
    
    // SET CCP1 to PWM mode 
    CCP1CON = 0x0C;  // 0000 1100 (bit 7-6 unimplemented) (bit 5-4 PWM duty cycle 10 bit 8MSB & 2LSB in CCP1CON 4th and 5th bit )
    // (bit 3-0 11XX to set PWM Mode)
    
    // Set Timer2 prescaler and period
    T2CON = 0x04;     // Binary - 00000100, timer2 control reg - (bit 7unimplemented) (bit 6-3 postscale select bit) 
    // (bit 2 TIMER 2 ON-1, OFF 0)   (bit 1-0 Prescale select bits)   values(00->1 01->4 1x->16)        
    PR2 = 249;        // Set period for ~4 kHz PWM with 4 MHz clock

    // Start Timer2
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
    
    while (!PIR1bits.TMR2IF); // Wait until Timer2 overflows
    PIR1bits.TMR2IF = 0;      // Clear Timer2 overflow flag
}

void PWM_SetDutyCycle(unsigned int dutyCycle) {
    if (dutyCycle > 1023) {   // Ensure dutyCycle is within 10-bit range (0-1023) PWM RES 10 BIT
        dutyCycle = 1023;
    }

    // Set duty cycle
    CCPR1L = (unsigned char)(dutyCycle >> 2); // right shift duty cycle by 2 bits and store  result in CCPR1L register 8MSB bits

    CCP1CON = (CCP1CON & 0xCF) | ((dutyCycle & 0x03) << 4); // Clear the lower 2 bits (DC1B1 & DC1B0) of CCP1CON
}

void Motor_SetDirection(unsigned char direction) {
    if (direction) {
        HBRIDGE_IN1 = 1; // Forward IN1 = HIGH, IN2 = LOW
        HBRIDGE_IN2 = 0;
    } else {
        HBRIDGE_IN1 = 0; // Reverse IN1 = LOW, IN2 = HIGH
        HBRIDGE_IN2 = 1;
    }
}
