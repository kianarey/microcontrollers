/*
 * File:   vang_lab3_implementation_v001.c
 *         File library that contains functions for other Lab 3 methods
 * Author: kiavang
 *
 * Created on July 3, 2019, 8:21 PM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "stdint.h"
#include "stdio.h"
#include "vang_Lab3_header_v001.h"

// Function Definitions
/* Function:        void delay(int delay_in_ms)
 * Purpose:         To delay representation of color.
 * Pre-condition:   An integer value is passed in as delay_in_ms.
 * Post-condition:  kv_wait_1ms() is called "delay_in_ms" number of times. */
void delay(int delay_in_ms) {
    int i;
    for (i = 1; i <= delay_in_ms; i++){
        kv_wait_1ms();
    }
}

/* Function:        char decoder(int input)
 * Purpose:         Takes in value from readKeyPadRAW(), translates, and returns
 *                  char to be displayed via 7-segment.
 * Pre-condition:   Takes in an integer value.
 * Post-condition:  A char variable is returned to main to be displayed via 
 *                  7-segment display. */
char decoder(int input){
    int temp_input = input;
    switch(temp_input){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'b';
        case 12:
            return 'C';
        case 13:
            return 'd';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return -1;
    }
}



