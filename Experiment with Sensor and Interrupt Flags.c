#pragma config FOSC = HS     // Oscillator Selection
#pragma config WDTE = OFF    // Watchdog Timer Enable
#pragma config PWRTE = OFF   // Power-up Timer Enable
#pragma config CP = OFF      // Code Protection
#pragma config BOREN = ON    // Brown-out Reset Enable
#pragma config LVP = OFF     // Low Voltage Programming
#pragma config CPD = OFF     // Data EEPROM Memory Code Protection
#pragma config WRT = OFF     // Flash Program Memory Write Enable

#define _XTAL_FREQ 6000000  // Replace with your MCU's frequency

#include <stdio.h>

#define HIGH_TEMP 0
#define LOW_TEMP 1
#define SYS_FAIL 2

void checkAlerts(unsigned char flags) {
    if (flags & (1 << HIGH_TEMP)) {
        // 0000 0001
        // 0000 0101
        // 0000 0001 
        printf("High temperature alert!\n");
    }
    if (flags & (1 << LOW_TEMP)) {
        // 0000 0010
        // 0000 0101
        // 0000 0000 
        printf("Low temperature alert!\n");
    }
    if (flags & (1 << SYS_FAIL)) {
        // 0000 0100
        // 0000 0101
        // 0000 0100
        printf("System failure!\n");
    }
}

int main() {
    unsigned char sensorFlags = 0x00; // 0000 0000

    // Simulate alerts
    sensorFlags |= (1 << HIGH_TEMP);
    // (0000 0001 << 0)
    // 0000 0001
    // perform OR
    // 0000 0001
    // 0000 0000
    // 0000 0001  value at sensorflags
    sensorFlags |= (1 << SYS_FAIL);
    // (0000 0001 << 2)
    // 0000 0100
    // do OR
    // 0000 0100
    // 0000 0001
    // 0000 0101  value at sensorflags
    // Check active alerts
    checkAlerts(sensorFlags); // calls checkalerts function with current value of sensorflag
    // Clear the HIGH_TEMP flag
    sensorFlags &= ~(1 << HIGH_TEMP);
    // 0000 0001
    // After NOT
    // 1111 1110
    // perform AND
    // 1111 1110
    // 0000 0101
    // 0000 0100  output in hex 0x04
    printf("Updated sensor flags: 0x%02X\n", sensorFlags);
    return 0;
}
