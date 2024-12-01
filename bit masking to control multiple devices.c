#pragma config FOSC = HS     // Oscillator Selection
#pragma config WDTE = OFF    // Watchdog Timer Enable
#pragma config PWRTE = OFF   // Power-up Timer Enable
#pragma config CP = OFF      // Code Protection
#pragma config BOREN = ON    // Brown-out Reset Enable
#pragma config LVP = OFF     // Low Voltage Programming
#pragma config CPD = OFF     // Data EEPROM Memory Code Protection
#pragma config WRT = OFF     // Flash Program Memory Write Enable

#define _XTAL_FREQ 6000000  

#include <stdio.h>

#define D1 0
#define D2 1
#define D3 2

int main() {
    unsigned char devices = 0x00;  //bin 0000 0000
    
    //turn on device 1 and 3
    devices |= (1 << D1);  
    // value of D1 =0
    // (1<<0) left shift = 0000 00001
    // 0000 0000
    // 0000 0001
    // perform OR
    // 0000 0001  device 1 is ON others off
    devices |= (1 << D3);
    // (1<<2) left shift 
    // (0000 0001 << 2)
    // 0000 0100
    // 0000 0001
    // Perform OR
    // 0000 0101 device 1 & 3 is ON 
    if (devices & (1 << D2)) {
        // (0000 0001 << 1) left shift 
        // 0000 0010
        // 0000 0101  value at devices
        // perform AND 
        // 0000 0000
        printf("Device 2 is ON\n");
    } else {
        printf("Device 2 is OFF\n");  // output D2 is Off
    }

    devices &= ~(1 << D1);
    // turn device 1 off
    // (0000 0001 << 0)
    // ~(1111 1110)
    // perform AND 
    // 0000 0101
    // 1111 1110
    // 0000 0100  // device 1 gets off
    devices ^= (1 << D3);
    //to toggle device 3
    // (0000 0001 << 2)
    // 0000 0100
    // do XOR
    // 0000 0100
    // 0000 0000  all devices are OFF
    printf("Devices state: %d\n", devices);
    return 0;
}
