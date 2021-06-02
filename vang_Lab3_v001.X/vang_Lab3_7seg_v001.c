/*
 * File:   vang_Lab3_7seg_v001.c
 *         File library that contains functions for 7-segment display
 * Author: kiavang
 *
 * Created on July 4, 2019, 12:27 AM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "stdint.h"
#include "stdio.h"
#include "vang_Lab3_header_v001.h"

/* Function:        void init7seg(void)
 * Purpose:         To set device to digital I/O and port B to HIGH.
 * Pre-condition:   None.
 * Post-condition:  Configuration for 7-segment display is set correctly. */
void init7seg(void){
    CLKDIVbits.RCDIV = 0;           // Set RCDIV=1:1 (default 2:1) 32MHz or 
                                    // FCY/2=16M.
    AD1PCFG = 0x9fff;               // Set all pins to digital I/O.
    TRISB = 0b1111000000000011;     // Set port B (RB<11:10>) to HIGH
                                    // and RB<9:2> to LOW
}

/* Function:        void showChar7seg(char myChar, int myDigit)
 * Purpose:         Takes char value returned from decoder() to display either
 *                  on LEFT or RIGHT, which is determined by myDigit.
 * Pre-condition:   Takes in a char and integer variable.
 * Post-condition:  Displays the char via 7-segment display. */
void showChar7seg(char myChar, int myDigit){
    char c = myChar;    // myChar is the character being displayed
    int num = myDigit;  // myDigit indicates LEFT (1) or RIGHT (0)
    switch(c){
        case '0':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010000001100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:4> to LOW (0) = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100000001100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:4> to LOW (0) = Turn on
            }
            break;
        case '1':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000011001111100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<8:7> to LOW (0) = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000101001111100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<8:7> to LOW (0) = Turn on
            }
            break;
        case '2':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010010010100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9, RB8, RB6, RB5, RB3 to 
                                            // LOW (0) = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100010010100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9, RB8, RB6, RB5, RB3 to 
                                            // LOW (0) = Turn on
            }
            break;
        case '3':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010000110100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:6> and RB3 to LOW (0)
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100000110100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:6> and RB3 to LOW (0)
            }
            break;
        case '4':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000011001100100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<8:7> and RB<4:3> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000101001100100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<8:7> and RB<4:3> to LOW
            }
            break;
        case '5':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010100100100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9, RB7, RB6, RB4, RB3 to 0
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100100100100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9, RB7, RB6, RB4, RB3 to 0
            }
            break;
        case '6':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010100000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9 and RB<7:3> to LOW (0)
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100100000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9 and RB<7:3> to LOW (0)
            }
            break;
        case '7':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010001111100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:7> to LOW (0) = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100001111100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:7> to LOW (0) = Turn on
            }
            break;
        case '8':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010000000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:3> to LOW (0) = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100000000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:3> to LOW (0) = Turn on
            }
            break;
        case '9':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010001100100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:7> and RB<4:3> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100001100100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:7> and RB<4:3> to LOW
            }
            break;
        case 'A':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010001000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<9:7> and RB<5:3> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100001000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<9:7> and RB<5:3> to LOW
            }
            break;
        case 'b':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000011100000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<7:3> to LOW = Turn on
            }
            else{
                // show char on RIGHT
                LATB = 0b0000101100000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<7:3> to LOW = Turn on
            }
            break;
        case 'C':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010110001100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9 and RB<6:4> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100110001100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9 and RB<6:4> to LOW
            }
            break;
        case 'd':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000011000010100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB<8:5> and RB3 to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000101000010100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB<8:5> and RB3 to LOW
            }
            break;
        case 'E':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010110000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9 and RB<6:3> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100110000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9 and RB<6:3> to LOW
            }
            break;
        case 'F':
            if(num == 1){
                // show char on LEFT
                LATB = 0b0000010111000100;  // Set RB10 to HIGH (1) = Turn on L
                                            // Set RB9 and RB<5:3> to LOW
            }
            else{
                // show char on RIGHT
                LATB = 0b0000100111000100;  // Set RB11 to HIGH (1) = Turn on R
                                            // Set RB9 and RB<5:3> to LOW
            }
            break;
        default:
            // Do nothing
            break;
    }
}

/* Function:        void vangTest7seg(void)
 * Purpose:         Test function for showChar7seg().
 * Pre-condition:   None.
 * Post-condition:  Displays an example char via 7-segment display. */
void vangTest7seg(void){
    char MSB = 1;   // Show on left
    char LSB = 0;   // Show on right
    showChar7seg('0', MSB);
    //delay(PERIOD);
    showChar7seg('0', LSB);  
}      
