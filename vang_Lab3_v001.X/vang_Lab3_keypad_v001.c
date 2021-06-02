/*
 * File:   vang_Lab3_keypad_v001.c
 *         File library that contains functions for keypad
 * Author: kiavang
 *
 * Created on July 4, 2019, 12:29 AM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "stdint.h"
#include "stdio.h"
#include "vang_Lab3_header_v001.h"

/* Function:        void initKeyPad(void)
 * Purpose:         To set the right bits in port A to inputs (1) and port B 
 *                  to outputs (0), and enable pull-up resistors (RA<3:0>). 
 * Pre-condition:   None.
 * Post-condition:  Configuration for keypad is set correctly. */
void initKeyPad(void){
    TRISA = 0b0000000000001111;     // Set port A (RA<3:0>) to inputs (1)
    TRISB &= 0b0000111111111111;    // Set port B (RB<15:12>) to outputs (0)
    CNPU1bits.CN2PUE = 1;           // Pull up resister for CN2(RA0) 
    CNPU1bits.CN3PUE = 1;           // Pull up resister for CN3(RA1)
    CNPU2bits.CN29PUE = 1;          // Pull up resister for CN29(RA2)
    CNPU2bits.CN30PUE = 1;          // Pull up resister for CN30(RA3)
}

/* Function:        int readKeyPadRAW(void)
 * Purpose:         Determines the raw button that is pressed on keypad. Rows 
 *                  are sequentially set LOW and all four inputs are read. If
 *                  an input is read as LOW, this means a button has been 
 *                  pressed.
 * Pre-condition:   None.
 * Post-condition:  The integer value for the pressed key is returned to main to 
 *                  be decoded. */
int readKeyPadRAW(void){
    // All rows of keypad have been set to low. See initKeyPad TRISB
    unsigned int row;                   // To store row that was pressed
    
    // Scan Row 1
    LATB |=0xF000;                      // Set LATB to HIGH
    LATB &= 0b1110111111111111;         // Bit mask to change RB12 to LOW
    delay(PERIOD); 
    row = PORTA & 0b0000000000001111;   // Read from PORTA, bit mask because we 
                                        // only want to read the last 4 bits
    switch(row){
        // Col 1
        case 7:     // (0111) 1 is pressed
            return 1;
        // Col 2
        case 11:    // (1011) 2 is pressed
            return 2;
        // Col 3
        case 13:    // (1101) 3 is pressed
            return 3;
        // Col 4
        case 14:    // (1110) A is pressed
            return 10;       
    }
    
    // Done scanning Row 1. Change all 4 MSBs back to HIGH to be re-scanned.
    LATB |= 0x1000;                 
    
    // Scan Row 2
    LATB &= 0b1101111111111111;         // Change RB13 to low
    delay(PERIOD);
    row = PORTA & 0b0000000000001111;
    
    switch(row){
        // Col 1
        case 7:     // 4 is pressed
            return 4;
        // Col 2
        case 11:    // 5 is pressed
            return 5;
        // Col 3
        case 13:    // 6 is pressed
            return 6;
        // Col 4
        case 14:    // B is pressed
            return 11;
    }
    
    // Done scanning Row 2. Change all 4 MSBs back to HIGH to be re-scanned.
    LATB |= 0x2000;
    
    // Scan Row 3
    LATB &= 0b1011111111111111;         // Change RB14 to LOW
    delay(PERIOD);
    row = PORTA & 0b0000000000001111; 
    
    switch(row){
       // Col 1
        case 7:     // 7 is pressed
            return 7;
        // Col 2
        case 11:    // 8 is pressed
            return 8;
        // Col 3
        case 13:    // 9 is pressed
            return 9;
        // Col 4
        case 14:    // C is pressed
            return 12;
    }
    
    // Done scanning Row 3. Change all 4 MSBs back to HIGH to be re-scanned.
    LATB |= 0x4000;
    
    // Scan Row 4
    LATB &= 0b0111111111111111;         // Change RB15 to LOW
    delay(PERIOD);
    row = PORTA & 0b0000000000001111;
    
    switch(row){
    // Col 1
        case 7:     // * is pressed = E
            return 14;
        // Col 2
        case 11:    // 0 is pressed
            return 0;
        // Col 3
        case 13:    // # is pressed = F
            return 15;
        // Col 4
        case 14:    // D is pressed
            return 13;
    }
   
    return -1;      // Nothing was pressed. Return -1
}
