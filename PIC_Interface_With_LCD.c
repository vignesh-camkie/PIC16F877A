
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000               // clock freq 6 MHz

void init();                             // init function declaration
void Lcd_command(unsigned char);         // Lcd_command function declaration
void Lcd_data(unsigned char);            // Lcd_data function declaration

unsigned char x;                         // global variable x
unsigned char array[11] = {"HELLO WORLD"};   // char array to store 11 elements

void main()                             // main function starts
{
    init();                             // call init function with no arguments
    Lcd_command(0x80);                  // starting address is set as 0x8

    for(x = 0; x < 11; x++)             // for loop iterates from index 0 to 10
    {
        Lcd_data(array[x]);             // call lcd_data function that takes arguments in array from 0 to 10
    }

    while(1);                           // Always True Infinite loop 
}

void init()
{
    TRISC = 0x00;        // PORTC - output, binary 0000 0000, RC0 for Enable RC3 for RS
    TRISD = 0x00;        // PORTD - output to send data to LCD, We use 8 Data Lines

    Lcd_command(0x30);     // passing command 0x30 to function as per LCD dataset in 8 bit initilization
    __delay_ms(100);       // Delay for 100 ms

    Lcd_command(0x30);     // passing command 0x30 to function 
    __delay_ms(100);       // Delay for 100 ms

    Lcd_command(0x30);     // passing command 0x30 to function
    __delay_ms(100);       // Delay for 100 ms

    // Function set in LCD dataset - N = no of lines N=1 for 2 lines / F = char font F=0 for 5x7
    // DL = Data Length , DL = 1 for 8 bit length
    Lcd_command(0x38);      // 001DL NFxx , binary 0011 1000 for 0x38
    __delay_ms(100);        // Delay for 100 ms

    Lcd_command(0x06);      // left to right shift
    __delay_ms(100);        // Delay for 100 ms

    Lcd_command(0x0C);      // display on, cursor off
    __delay_ms(100);        // Delay for 100 ms

    Lcd_command(0x01);      // Clear display
    __delay_ms(100);        // Delay for 100 ms
}

void Lcd_data(unsigned char i)  // function to send lcd data
{
    RC3 = 1;             // RS = 1 
    PORTD = i;           // Save value of i in PORTD variable
    RC0 = 1;             // EN = 1 to Enable pulse to send data
    __delay_ms(100);     // Delay 100 ms
    RC0 = 0;             // EN = 0 to off pulse
    __delay_ms(100);     // Delay 100 ms
}

void Lcd_command(unsigned char i)  // function to configure lcd command
{
    RC3 = 0;             // RS = 0 for command mode
    PORTD = i;           // Save value of i in PORTD variable
    RC0 = 1;             // EN = 1 to Enable pulse to send command
    __delay_ms(100);     // Delay 100 ms
    RC0 = 0;             // EN = 0 to off pulse
    __delay_ms(100);     // Delay 100 ms
}
