/*
 * File:   vang_lab3_main_v001.c
 * Author: kiavang
 *
 * Created on June 26, 2019, 8:45 AM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "stdint.h"
#include "stdio.h"
#include "vang_Lab3_header_v001.h"

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
int main(void) {
    init7seg();                 // Initialize 7-segment display
    initKeyPad();               // Initialize keypad
    
    int prevInput, newInput;    // Variables to store inputs
    char MSB, LSB, myChar;      // Variables to store chars to show on 7-seg
    

    while(1){                   
        newInput = readKeyPadRAW(); // Scans for input
        myChar = decoder(newInput); // Decodes input and store in myChar
        
        // Execute when newInput returns a value that is not default case (-1)
        // AND when newInput is not previous input
        // Default case: No key has been pressed.
        if (newInput != -1 && newInput != prevInput){           
            MSB = LSB;      // Shift char in LSB to MSB                  
            LSB = myChar;   // Shift new myChar into LSB
        }
        
        prevInput = newInput;   // Store new input as previous input
        
        // Display inputs via 7-segment display
        showChar7seg(MSB, 1);
        delay(PERIOD);
        showChar7seg(LSB, 0);
        delay(PERIOD);
    }
    
    return 0;
}
