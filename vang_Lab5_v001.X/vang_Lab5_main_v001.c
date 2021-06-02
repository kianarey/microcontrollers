/* Date:                  July 21, 2019, 9:25 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 5
 * File Name:             vang_Lab4_main_v001.c
 * File Description:      A program that uses I2C to write a single or length of
 *                        character(s) to ST7032 LCD Display.
 */

#include "xc.h"
#include "p24FJ64GA002_HeaderFile.h"
#include "vang_Lab5_header_v001.h"
#include <stdio.h>
#include <string.h>

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1           // Comm Channel Select (Emulator EMUC1/EMUD1 
                                    // pins are shared with PGC1/PGD1).
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is 
                                    // disabled).
#pragma config GWRP = OFF           // General Code Segment Write Protect 
                                    // (Writes to program memory are allowed).
#pragma config GCP = OFF            // General Code Segment Code Protect (Code 
                                    // protection is disabled).
#pragma config JTAGEN = OFF         // JTAG Port Enable (JTAG port is disabled).

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI        // I2C1 Pin Location Select (Use default 
                                    // SCL1/SDA1 pins).
#pragma config IOL1WAY = OFF        // IOLOCK Protection (IOLOCK may be changed 
                                    // via unlocking seq).
#pragma config OSCIOFNC = ON        // Primary Oscillator I/O Function 
                                    // (CLKO/RC15 functions as I/O pin).
#pragma config FCKSM = CSECME       // Clock Switching and Monitor (Clock 
                                    // switching is enabled, Fail-Safe Clock 
                                    // Monitor is enabled).
#pragma config FNOSC = FRCPLL       // Oscillator Select (Fast RC Oscillator 
                                    // with PLL module (FRCPLL)).

void setup(void){
    CLKDIVbits.RCDIV = 0;           // Set RCDIV=1:1 (default 2:1) 32MHz or 
                                    // FCY/2=16M.
    AD1PCFG = 0x9fff;               // Set all pins to digital I/O.
    
    // Set up I2C
    I2C2CONbits.I2CEN = 0;          // Turn off I2C
    I2C2BRG = 0x9D;                 // Baud Rate Generator 100 kHz ; 16 MHz
    I2C2CONbits.I2CEN = 1;          // Turn ON I2C
    
    // I2C Interrupt
    IFS3bits.MI2C2IF = 0;           // Clear Master I2C interrupt flag
    
}

int main(void) {
    setup();                        // Set up Master - PIC24
    lcd_init();                     // Set up Slave - LCD
    
    char arr[] = "Hello World!";    // Char array
    lcd_cmd(0b00110100);            // Command to set font to fill two lines
    lcd_setCursor(0,0);             // Set cursor
    lcd_printStr(arr);              // Function call to print string
    
    //lcd_printChar(0x41);
    
    while(1){
        lcd_cmd(0b00011000);        // Command to shift display to left
        delay(200);                 // Delay to slow down animation speed
    }
    return 0;
}
