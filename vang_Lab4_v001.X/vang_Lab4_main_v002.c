/* Date:                  July 6, 2019, 9:43 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 4, Week 2
 * File Name:             vang_Lab4_main_v002.c
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
volatile unsigned long int period = 0;

// IC1 Interrupt
void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void){
    _IC1IF = 0;                     // Clear interrupt flag
    unsigned long int curEdge;
    
    curEdge = IC1BUF; // Stores TMR2
    period = (curEdge + ((PR2 + 1) * rollover));
    
    if (period > 5250){
        if (flag == 0){
            flag = 1;
        }
        TMR2 = 0;
        rollover = 0;
    } 
    /*_IC1IF = 0;
    static long int prevEdge = 0;
    static long int curEdge = 0;
    static long int curPeriod = 0;
    curEdge = IC1BUF + (PR2*rollover);
    curPeriod = curEdge - prevEdge;
    if (!(curPeriod < 6250)){        // Only do this if greater than 100ms
        period = curPeriod;
        //prevEdge = curEdge;
        rollover = 0;
        TMR2 = 0;
    }*/

}

// Timer 2 Interrupt
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void){
    _T2IF = 0;                      // Clear interrupt flag
    rollover++;                     // Keep track of rollover 
}

int main(void) {

    initServo();
    initPushButton();

    while(1){
        /*
        setServo(30000);
        delay(2000);
        setServo(10000);
        delay(2000);*/
        if (flag == 1){ // period is greater than 100ms
            if(period > 6250 && period < 13500){
            // if (period > 5250 && period < 15550){ // double-click, less 192ms
                setServo(2000);         // 1ms pulse width turn left -> -90 degrees?
                delay(2000);            // wait 2 seconds
                setServo(4500);         // 2ms, turn right -> +90 degrees?
                flag = 0;  
                //TMR2 = 0;
                //rollover = 0;
                }
            }
        
        /*if(TMR2+PR2*(long int)rollover > 62500){// Reset servo if greater than 2sec
            setServo(10);
        }
        else if(period < 15625){        // Double click if less than 0.25sec
            setServo(30000);
        }*/

        }      
    return 0;
}
