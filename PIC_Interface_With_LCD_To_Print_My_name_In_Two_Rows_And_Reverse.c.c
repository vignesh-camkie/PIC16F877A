// PIC16F877A Configuration Bit Settings
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000      // clock freq 6 MHz

void begin(void);                           // begin function declaration
void lcd_config_fun(unsigned char j);       // Lcd_config_fun declaration
void send_my_name(unsigned char k);         // send_my_name function declaration

unsigned char name[7] = "VIGNESH";      // array to store my name, array size = 7 elements
unsigned char x,a;                      // global variable x,a

void main(void) 
{
    begin();                           // call begin function with no arguments
    
    lcd_config_fun(0x82);              // starting address is set as 0x82
    for(x = 0; x < 7; x++) {           // for loop iterates from index 0 to 6
        send_my_name(name[x]);         // send my name to array [x] 1 by 1 from 0 to 7 characters
    }

    a = 0xCD;                           // starting address is set as 0xCD in 2nd Line
    for(x = 6; x <= 6; x--) {           // for loop iterates from index 6 to 0
        lcd_config_fun(a);              // starting address is set to 0xCD
        send_my_name(name[6-x]);        // prints from, here 6-6 = 0 to 6-0 = 6 from index 0 to 6 of name array
        a--;                            // decrement 1 by 1
        if(x == 0)
        break;                          // break loop when x reaches 0
    }
    
    while(1);                      // always true
}

void begin(void) {
    TRISC = 0x00;           // PORTC - output, binary 0000 0000, RC0 for Enable RC3 for RS
    TRISD = 0x00;           // PORTD - output to send data to LCD, We use 8 Data Lines
    
    lcd_config_fun(0x30);      // passing command 0x30 to config_function as per LCD dataset in 8 bit initialization
    __delay_ms(100);           // delay for 100 ms     
    
    lcd_config_fun(0x30);      // passing command 0x30 to config_function 
    __delay_ms(100);         
    
    lcd_config_fun(0x30);      // passing command 0x30 to config_function
    __delay_ms(100);         
    
    // Function set in LCD dataset - N = no of lines N=1 for 2 lines / F = char font F=0 for 5x7
    // DL = Data Length, DL = 1 for 8 bit length
    
    lcd_config_fun(0x38);      // 001DL NFxx, binary 0011 1000 for 0x38
    __delay_ms(100);
    
    lcd_config_fun(0x06);      // left to right shift
    __delay_ms(100);
    
    lcd_config_fun(0x0C);      // display on, cursor off
    __delay_ms(100);
    
    lcd_config_fun(0x01);      // Clear display
    __delay_ms(100);
}

void lcd_config_fun(unsigned char j) {
    RC3 = 0;                // RS = 0 for command mode
    PORTD = j;              // Save value of i in PORTD variable
    RC0 = 1;                // EN = 1 to Enable pulse to send command
    __delay_ms(100);        // Delay for 100 ms
    RC0 = 0;                // EN = 0 to off pulse
    __delay_ms(100);        // Delay for 100 ms
}

void send_my_name(unsigned char k) {
    RC3 = 1;                // RS = 1 data mode
    PORTD = k;              // Save value of k in PORTD variable
    RC0 = 1;                // EN = 1 to Enable pulse to send data
    __delay_ms(100);        // Delay for 100 ms
    RC0 = 0;                // EN = 0 to off pulse
    __delay_ms(100);        // Delay for 100 ms
}
