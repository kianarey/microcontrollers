/* File:   vang_lab1_main_v001.c
 * Author: kiavang
 *
 * Created on June 12, 2019, 9:03 AM
 */


#include "xc.h"
#include "p24FJ64GA002_HeaderFile.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void)
{
    CLKDIVbits.RCDIV = 0;       // Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b0000000000011111;  //set port A to inputs,
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATA = 0xffff;               //Set all of port A to HIGH
    LATB = 0xffff;               //and all of port B to HIGH
}

void delay(void) {
    long int curCount = 0;
    
    while(curCount < 80000)
    {
        curCount++;
    }
}
int main(void) {
    setup();
    
    LATB = 0x7FFF; // This will turn on the most significant LED
    
    int i;
    int j;
    
    while(1) {
        // Execute repeatedly forever and ever and ever and ever ...
        for(i = 1; i < 4; i++){
           delay(); //This pauses execution so the shifts are visible
           delay();
           delay();
           LATB = LATB >> 1; // This shifts the LATB register
           LATB |= 0x8000;
        } 
        
        for (j = 1; j < 4; j++){
           delay(); //This pauses execution so the shifts are visible
           delay();
           delay();
           LATB = LATB << 1; 
           LATB |= 0x0001;
        }
        
        LATB = 0x7FFF;
    }
    return 0;
} 
 
