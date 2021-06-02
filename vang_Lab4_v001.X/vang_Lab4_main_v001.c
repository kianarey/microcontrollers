/* Date:                  July 6, 2019, 9:43 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 4, Week 1
 * File Name:             vang_Lab4_main_v001.c
 * File Description:      A program to create a double-click detector that 
 *                        controls the position of a servo motor. Timers 2 and 
 *                        3, Input Capture and Output Compare peripherals and 
 *                        interrupt service routines are used in this lab.
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "p24FJ64GA002_HeaderFile.h"
#include "vang_Lab4_header_v001.h"
#include "stdint.h"
#include "stdio.h"

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

volatile unsigned long int rollover = 0;
volatile int flag = 0;

// Timer 2 Interrupt
void __attribute__((interrupt, auto_psv)) _T2Interrupt(){
    _T2IF = 0;                      // Clear interrupt flag
    rollover++;                     // Keep track of rollover 
}

int main(void) {
    
    unsigned long int timeDiff = 0, curEvent, prevState = 0, curState;
    
    initServo();
    initPushButton();
    
    while(1){
        // Read
        prevState = curState;
        curState = _RB7;
        if (curState == 0 && prevState == 1){ // Read in, if low

            curEvent = (unsigned long int) TMR2;    // Static cast & record time
            //prevEvent = curEvent;
            timeDiff = (curEvent + ((PR2 + 1) * rollover));
            
            // Debounce
            // If timeDiff is less than 100ms, ignore noise, reset TMR2/rollover
            if (timeDiff > 5250){ // timeDiff is greater than 100ms
                if (flag == 0){ // Check if first falling edge
                    flag = 1;   // if yes, then set to 1
                } 
                else{ // if not first falling edge, check double click
                // Update setting of servo
                    if (timeDiff < 15550){      // double-click, less 192ms
                        setServo(2000);         // 1ms pulse width turn left
                        delay(2000);            // wait 2 seconds
                        setServo(4500);         // 2ms, turn right
                        flag = 0;  
                    }
                }
                TMR2 = 0;               // reset TMR2
                rollover = 0;           // reset rollover
            }   
        }  
    }
        
    return 0;
}
