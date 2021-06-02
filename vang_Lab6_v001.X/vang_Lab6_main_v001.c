 /*
 * File:   vang_Lab6_main_v001.c
 * Author: kiavang
 *
 * Created on April 16, 2019, 2:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "vang_Lab6_header_v001.h"
#include "xc.h"
#include <p24Fxxxx.h>
#include "p24FJ64GA002_HeaderFile.h"
#define Buffer_Size 1024

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
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL

volatile float curVoltage;
volatile float curAvg;

void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;  // could have used _T2IF    
    putVal(ADC1BUF0);
    putVal(ADC1BUF1);
    putVal(ADC1BUF2);
    putVal(ADC1BUF3);
    putVal(ADC1BUF4);
    putVal(ADC1BUF5);
    putVal(ADC1BUF6);
    putVal(ADC1BUF7);
    putVal(ADC1BUF8);
    putVal(ADC1BUF9);
    putVal(ADC1BUFA);
    putVal(ADC1BUFB);
    putVal(ADC1BUFC);
    putVal(ADC1BUFD);
    putVal(ADC1BUFE);
    putVal(ADC1BUFF); 
}

void main(void) {

    setup(); 
    lcd_initi();
    lcd_setCursor(0,0);
    
    int i;
    while(1){
    
        for(i=0; i < 100; i++){     
            wait_1ms();  
        }

        unsigned long int adValue;
        char adStr[20];

            adValue = getAvg();
            sprintf(adStr, "%6.4f V", (3.3/1024) * adValue);

        lcd_setCursor(0,0);
        lcd_printStr(adStr);    
 
    }
    
    return;
}

