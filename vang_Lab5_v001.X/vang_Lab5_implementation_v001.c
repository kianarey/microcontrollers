/* Date:                  July 21, 2019, 9:25 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 5
 * File Name:             vang_Lab5_implementation_v001.c
 * File Description:      Consists of function methods to implement code in
 *                        vang_Lab5_main_v001.c file. 
 */

#include "xc.h"
#include "p24FJ64GA002_HeaderFile.h"
#include "vang_Lab5_header_v001.h"
#include <stdio.h>
#include <string.h>

#define CONTRAST 32

// Function Definitions
/* Function:        void delay(int delay_in_ms)
 * Purpose:         To delay and perform no operation for a given time
 * Pre-condition:   An integer value is passed in as delay_in_ms.
 * Post-condition:  kv_wait_1ms() is called "delay_in_ms" number of times. */
void delay(int delay_in_ms){
    int i;
    for (i = 1; i <= delay_in_ms; i++){
        kv_wait_1ms();
    }
}

/* Function:        void lcd_cmd(char command)
 * Purpose:         Takes a single byte/char command and write it out to the I2C
 *                  bus. It consists of START bit, address with R/nW byte,
 *                  control byte, command/data byte, and STOP bit.
 * Pre-condition:   Takes a char variable by value.
 * Post-condition:  Completes command. */
void lcd_cmd(char command){
  
    // Write to I2C bus    
    I2C2CONbits.SEN = 1;            // Initiate start condition
    while(I2C2CONbits.SEN == 1);    // Wait for SEN == 0; SEN will clear when
                                    // Start bit is complete
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01111100;           // 8-bits slave address and R/nW bit
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b00000000;           // 8-bits control byte, not writing
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = command;              // 8-bits command/data byte
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2CONbits.PEN = 1;            // Stop bit
    while (I2C2CONbits.PEN == 1);   // Wait for PEN == 0; PEN will clear when
                                    // Stop bit is complete
}

/* Function:        void lcd_init(void)
 * Purpose:         Initialize LCD
 * Pre-condition:   None
 * Post-condition:  LCD configurations are set. */
void lcd_init(void){
    delay(50);                      // wait 50ms
    lcd_cmd(0b00111000);            // Function set, normal instruction mode
    lcd_cmd(0b00111001);            // Function set, extended instruction  mode
    lcd_cmd(0b00010100);            // Internal OSC Frequency
    lcd_cmd(0b01110000 | (CONTRAST & 0b11110000));        // Contrast C3-C0
    
    lcd_cmd(0b01011100 | ((CONTRAST & 0b00110000) >> 4)); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100);            // Follower Control
    delay(200);                     // wait 200ms                          
    lcd_cmd(0b00111000);            // Function set, normal instruction mode
    lcd_cmd(0b00001100);            // Display ON
    lcd_cmd(0b00000001);            // Clear Display
    delay(2);                       // wait 2 ms
}

/* Function:        void lcd_setCursor(char x, char y)
 * Purpose:         Consists of a single lcd_cmd() statement with a masked and
 *                  calculated command to set cursor to row x and column y.
 * Pre-condition:   Takes in char values for x and y.
 * Post-condition:  Cursor is set. */
void lcd_setCursor(char x, char y){
    lcd_cmd(0x80 | ((0x40 * x) + y)); // page 13 of lab manual
}

/* Function:        void lcd_printChar(char myChar)
 * Purpose:         Prints out a single character via LCD.
 * Pre-condition:   Takes myChar and writes it out to the I2C bus. It consists 
 *                  of START bit, address with R/nW byte, control byte, 
 *                  command/data byte, and STOP bit.
 * Post-condition:  myChar is printed via LCD. */
void lcd_printChar(char myChar){ 
    I2C2CONbits.SEN = 1;            // Initiate start condition
    while (I2C2CONbits.SEN == 1);   // Wait for SEN == 0; SEN will clear when
                                    // Start bit is complete
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01111100;           // 8-bits slave address and R/nW bit
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01000000;           // 8-bits control byte
                                    // CO = 0, RS = 1 for writing
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = myChar;               // 8-bits consisting of data
    while (_MI2C2IF == 0);          // Wait
    _MI2C2IF = 0;                   // Clear flag
    I2C2CONbits.PEN = 1;            // Stop bit
    while (I2C2CONbits.PEN == 1);   // Wait for PEN == 0; PEN will clear when
                                    // Stop bit is complete
}

// Take an arbitrary length and send to LCD. This will require multiple command/
// data byte pairs with the RS and CO bits controlling when the packet ends. 
// Don't forget to finish the packet with a STOP bit.
/* Function:        void lcd_printStr(const char *s)
 * Purpose:         Takes an arbitrary length of characters and send to LCD. It 
 *                  includes multiple command/data byte paired with the RS and 
 *                  CO bits controlling when the packet ends. It finishes with a
 *                  STOP bit. 
 * Pre-condition:   Takes in a constant char pointer s, which stores the address 
 *                  and first element of array passed in.
 * Post-condition:  Length of characters is printed via LCD. */
void lcd_printStr(const char *s){ // a pointer s to constant char type
    
    char i;
    const char SIZE = strlen(s);
    
    I2C2CONbits.SEN = 1;            // Initiate start condition
    while (I2C2CONbits.SEN == 1);   // Wait for SEN == 0; SEN will clear when
                                    // Start bit is complete
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01111100;           // 8-bits slave address and R/nW bit
    while (_MI2C2IF == 0);          // Wait
    
    for (i = 0; i < (SIZE - 1); i++){  // Sending every char except last char
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = 0b11000000;          // 8-bits control byte
                                       // CO = 0, RS = 1 for writing
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = s[i];                // 8-bits consisting of data
        while (_MI2C2IF == 0);         // Wait 
    }
        // Sending last byte of data
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = 0b01000000;          // 8-bits control byte
                                       // CO = 0, RS = 1 for writing
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = s[SIZE - 1];         // 8-bits consisting of data
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2CONbits.PEN = 1;           // Stop bit
        while (I2C2CONbits.PEN == 1);  // Wait for PEN == 0; PEN will clear when
                                       // Stop bit is complete
}
