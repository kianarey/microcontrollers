/* Date:                  July 6, 2019, 9:43 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 4, Week 2
 * File Name:             vang_Lab4_implementation_v002.c
 * File Description:      Consists of function methods to implement code in
 *                        vang_Lab4_main_v002.c file. 
 */

#include "xc.h"
#include "vang_Lab4_header_v001.h"

// Function Definitions
/* Function:        void delay(int delay_in_ms)
 * Purpose:         To delay and perform no operation for a given time
 * Pre-condition:   An integer value is passed in as delay_in_ms.
 * Post-condition:  kv_wait_1ms() is called "delay_in_ms" number of times. */
void delay(int delay_in_ms) {
    int i;
    for (i = 1; i <= delay_in_ms; i++){
        kv_wait_1ms();
    }
}

/* Function:        void initServo(void)
 * Purpose:         This is an initialization function for the servo. It sets 
 *                  clock to 16 MHz, all pins to digital I/O, RB6 to output, and 
 *                  RB7 to input. It then utilizes PPS to bind IC1 to RB7/RP6 
 *                  and OC1 to RB6/RP6 and initializes Timer 3 to have a period 
 *                  of 2ms. It also sets OC1 peripheral to the proper values.
 * Pre-condition:   None
 * Post-condition:  Configurations for PIC24 and servo are set correctly. */
void initServo(void){
    CLKDIVbits.RCDIV = 0;           // Set RCDIV=1:1 (default 2:1) 32MHz or 
                                    // FCY/2=16M.
    AD1PCFG = 0x9fff;               // Set all pins to digital I/O.
    TRISB = 0b0000000100000011;     // Set port B RB6 to output (LOW) and RB7 to
                                    // input (HIGH)
    __builtin_write_OSCCONL(OSCCON & 0xBF);   // Unlock PPS
    RPINR7bits.IC1R = 8;            // Use PIN RP7 = "7", for Input Capture 1
    RPOR3bits.RP6R = 18;            // Use Pin RP6 for Output Compare 1 = "18"
    __builtin_write_OSCCONL(OSCCON | 0x40);  // Lock PPS
    
    // Timer 3 set up           
    T3CONbits.TON = 0;              // Stop Timer, Tcy source, PRE 1:8
    T3CONbits.TCKPS = 0b01;
    T3CONbits.TGATE = 0;
    T3CONbits.TCS = 0;              // Internal clock
    TMR3 = 0;                       // Initialize to zero
    PR3 = 39999;                    // PR + 1 = 40,000; period of 20ms
    OC1CON = 0;                     // Turn off for now
    OC1R = 10000;                   // Initialize Compare Register1 = 10,000
    OC1RS = 30000;
    
    // Setting up OC peripheral 
    _OC1IF = 0;
    OC1CONbits.OCTSEL = 1;          // Use Timer 3 for compare source
    OC1CONbits.OCM = 0b110;         // set PWM
    T3CONbits.TON = 1;              // Restart 16-bit Timer3  
}

/* Function:        setServo(int val)
 * Purpose:         This function takes in an integer value from main and 
 *                  assigns it to OCR1S, which is one of the OC1 core registers.
 *                  It then controls PWM and sets servo in the desired position.
 * Pre-condition:   An integer value is passed in as an argument.
 * Post-condition:  Servo is set to desired position. */
void setServo(int val){
    // change OC --> controls PWM --> controls Servo
    OC1RS = val;
}

/* Function:        void initPushButton(void)
 * Purpose:         This function sets up Input Capture with Timer 2. The IC1 
 *                  module is set up and configured to use Timer 2 and capture
 *                  falling edges. Timer 2 is initialized to have a period of no
 *                  less than 1 second to avoid overflow. IC1 is also 
 *                  initialized and enabled to perform input capture.
 * Pre-condition:   None
 * Post-condition:  Push button is set up correctly and is used to capture Timer
 *                  2 values. */
void initPushButton(void){
    // IC1 setup
    IC1CON = 0;                     // Turn off and reset internal state of IC1
    IC1CONbits.ICSIDL = 0;          // IC module will cont to operate when idle
    IC1CONbits.ICTMR = 1;           // TMR2 contents captured on capture event
    IC1CONbits.ICI = 0b00;          // Interrupt on every capture event
    IC1CONbits.ICM = 0b010;         // Capture mode, every falling edge
    _IC1IP = 3;                     // IC1 Priority flag needed? I set to 3
    _IC1IF = 0;                     // Clear IC1 ISR flag
    _IC1IE = 1;                     // Enable IC1 ISR
        
    // Timer 2 Set Up
    T2CONbits.TON = 0;              // Stop TMR2
    T2CONbits.TCKPS = 0b11;         // PRE = 256
    T2CONbits.TGATE = 0;            // Gated time accumulation is disabled
    T2CONbits.TSIDL = 0;            // Continues module operation when in Idle
    T2CONbits.TCS = 0;              // Internal Clock
    
    TMR2 = 0;                       // Clear TMR 2
    PR2 = 62499;                    // PR 62,499 + 1 = 62500; 1 sec period
    //_T2IP = 3;                    // Timer 2 interrupt priority level
    _T2IF = 0;                      // Clear Timer 2 ISR flag
    _T2IE = 1;                      // Enable Timer 2 ISR
    T2CONbits.TON = 1;              // Turn on TMR2
    CNPU2bits.CN23PUE = 1;          // Pull up resistor for button   
}