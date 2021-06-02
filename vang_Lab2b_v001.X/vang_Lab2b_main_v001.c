/* File:   vang_lab2b_main_v001.c
 * Author: kiavang
 *
 * Created on June 23, 2019, 6:02 PM
 */

#include "xc.h"
#include <p24Fxxxx.h>
#include "stdint.h"
#include "stdio.h"
#include "vang_Lab2b_asmLib_v001.h"
#include "p24FJ64GA002_HeaderFile.h"
#define PERIOD 7

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
// Function Definitions
/* Function:        void setup(void)
 * Purpose:         To set up PIC to correct state
 * Pre-condition:   None
 * Post-condition:  PIC is set to correct state, see below. */
void setup(void)
{
    CLKDIVbits.RCDIV = 0;           // Set RCDIV=1:1 (default 2:1) 32MHz or 
                                    // FCY/2=16M.
    AD1PCFG = 0x9fff;               // Set all pins to digital I/O.
    TRISA = 0b0000000000011110;     // Set port A to inputs, except first bit
    // TRISB = 0b0000000000000011;  // and port B to outputs.
    LATA = 0x0001;                  // Set RA0 of port A to HIGH to read RAO
    // LATB = 0xffff;               // and all of port B to HIGH.
}

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

/* Function:        void writeColor(char r, char g, char b)
 * Purpose:         To write color depending on values passed in for red, blue, 
 *                  and green. These values range from 0-255.
 * Pre-condition:   Three char values are passed in; Each for red, green and
 *                  blue.
 * Post-condition:  Each char values are bit-masked with value 0x80 and then
 *                  stored in flag. Flag determines whether to call write_1() or
                    write_0(). */
void writeColor(char r, char g, char b)
{
    char i;
    char flag = 0;
    char mask = 0b10000000;
    char temp_r = r;
    char temp_g = g;
    char temp_b = b;
    
    for (i = 0; i < 8; i++){
        flag = mask & temp_r;
        
        if (flag){ // if TRUE aka 1, write_1, else FALSE aka 0, write_0
        write_1();
        }
        else{
        write_0();
        }
        
        temp_r = (temp_r << 1);
    }
    
    for (i = 0; i < 8; i++){
        flag = mask & temp_g;
        
        if (flag){
        write_1();
        }
        else{
        write_0();
        }
        
        temp_g = (temp_g << 1);
    }
    
    for (i = 0; i < 8; i++){
        flag = mask & temp_b;
        
        if (flag){
        write_1();
        }
        else{
        write_0();
        }
        
        temp_b = (temp_b << 1);
    }
}

/* Function:        uint32_t packColor(unsigned char Red,unsigned char Grn, 
 *                  unsigned char Blu)
 * Purpose:         To pack RGB values into their correct 8-bit position.
 * Pre-condition:   Three unsigned char values are passed in for red, green, and
 *                  blue.
 * Post-condition:  unsigned char values are packed into one single RGB variable
 *                  and this value is returned. */
uint32_t packColor(unsigned char Red,unsigned char Grn, unsigned char Blu){
    unsigned long int RGBval = 0;
    RGBval = ((long) Red << 16) | ((long) Grn << 8) | ((long) Blu);
    return RGBval;
}

/* Function:        uint32_t Wheel(unsigned char WheelPos)
 * Purpose:         Input a value 0-255 to get a color value.
 * Pre-condition:   An unsigned char value is passed in from main as WheelPos.
 * Post-condition:  This value is subtracted from 255 and stored in WheelPos.
 *                  Depending on its value, it is passed into packColor as 3 new 
 *                  arguments. packColor function packs these values and returns 
 *                  one unsigned long integer value. This one value is then 
 *                  returned to main. */
uint32_t Wheel(unsigned char WheelPos){
    
    WheelPos = 255 - WheelPos;

    if(WheelPos < 85) {
        return packColor(255 - WheelPos * 3, 0, WheelPos * 3);
        
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return packColor(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return packColor(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/* Function:        unsigned char getR(uint32_t RGBval)
 * Purpose:         Unpacks unsigned long int RGB value to red.
 * Pre-condition:   Unsigned long int RGBval is passed as value.
 * Post-condition:  RGBval is static-casted to unsigned char and bit-shifted to 
 *                  the right 16 times to get an unsigned char value. This value
 *                  then is returned. */
unsigned char getR(uint32_t RGBval){
    unsigned char Red = 0;
    Red = (unsigned char) (RGBval >> 16);
    return Red;
}

/* Function:        unsigned char getG(uint32_t RGBval)
 * Purpose:         Unpacks unsigned long int RGB value to green.
 * Pre-condition:   Unsigned long int RGBval is passed as value.
 * Post-condition:  RGBval is static-casted to unsigned char and bit-shifted to 
 *                  the right 8 times to get an unsigned char value. This value
 *                  then is returned. */
unsigned char getG(uint32_t RGBval){
    unsigned char Green = 0;
    Green = (unsigned char) (RGBval >> 8);
    return Green;
}

/* Function:        unsigned char getB(uint32_t RGBval)
 * Purpose:         Unpacks unsigned long int RGB value to blue.
 * Pre-condition:   Unsigned long int RGBval is passed as value.
 * Post-condition:  RGBval is static-casted to unsigned char and bit-shifted to 
 *                  the right 0 times to get an unsigned char value. This value
 *                  then is returned. */
unsigned char getB(uint32_t RGBval){
    unsigned char Blue = 0;
    Blue = (unsigned char) (RGBval >> 0);
    return Blue; 
}

/* Function:        void colorCycler(int i)
 * Purpose:         Creates a continuous change from one color to another (often
 *                  called a gradient). 
 *                  Red -> Purple -> Blue -> Purple -> Red. 
 * Pre-condition:   An integer value of 0 is passed by value.
 * Post-condition:  A gradient effect is created. Color starts at red, changes 
                    to purple, then to blue, back to purple and then red. */
void colorCycler(int i){
        // Red -> Purple
        for (i = 0; i < 256; i++){
            writeColor(255, 0, i);
            delay(PERIOD);
        }
        
        // Purple -> Blue
        for (i = 0; i < 256; i++){
            writeColor(255-i, 0, 255);
            delay(PERIOD);
        }
        
        // Blue -> Purple
        for (i = 0; i < 256; i++){
            writeColor(i, 0, 255);
            delay(PERIOD);
            
        }
        
         // Purple -> Red
        for (i = 0; i < 256; i++){
            writeColor(255, 0, 255-i);
            delay(PERIOD);
        }
}

int main(void) {
    setup();
    /* Color cycler program
     * To test it, you must comment out Wheel program below */
    
    //int in = 0;
    //while(1) {
      //  colorCycler(in);
    //}
    
    /* Wheel Program
     * To test it, you must comment out color cycler program above */
    
    unsigned char i, red, green, blue;
    unsigned long int RGBval;
    
    while(1){
       for (i = 0; i < 256; i++){
           
           RGBval = Wheel(i);
           red = getR(RGBval);
           green = getG(RGBval);
           blue = getB(RGBval);
           
           writeColor(red, green, blue);
           //delay(PERIOD);
        } 
    }
    
    return 0;
} 