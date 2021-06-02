/*
 * File:   arman018_library_v001.c
 * Author: hnyma
 *
 * Created on April 16, 2019, 4:59 PM
 */

#include "xc.h"
#include "ee3102_section009_main_v001.h"
#include <string.h>
#include <p24FJ64GA002.h>
#include "p24FJ64GA002_HeaderFile.h"
#define Buffer_Size 1024
#define NUMSAMPLES 128


volatile int readIdx = 0, writeIdx = 0, numEleminBuff = 0;
volatile unsigned int buffer[Buffer_Size];
int buffer_index = 0;

void wait_1ms(void){

    asm("repeat #15999");
    asm("nop");
    
    return;
}

void __attribute__((__interrupt__,__auto_psv__)) _INT0Interrupt(void)
{
    _INT0IF = 0;
    if(numEleminBuff < Buffer_Size)
    {
        buffer[writeIdx++] = PORTB;
        writeIdx %= Buffer_Size;
        ++numEleminBuff;
    }
    else{       
    }
}

void setup(void){ 
//Fcy=16 MHz
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0xFFFE;
    //AD1PCFGbits.PCFG0 = 0;
    LATB = 0x0000;                
//AD1CON1/ADC setup
    AD1CON1bits.ADON = 0;
    AD1CON1bits.ADSIDL = 0;
    AD1CON1bits.FORM1 = 0; //
    AD1CON1bits.FORM0 = 0; //
    AD1CON1bits.SSRC2 = 0; //
    AD1CON1bits.SSRC1 = 1; //
    AD1CON1bits.SSRC0 = 0; //
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.SAMP = 0;
//ADC setup (pt. 2)  
    AD1CON2bits.VCFG2 = 0; //
    AD1CON2bits.VCFG1 = 0; //
    AD1CON2bits.VCFG0 = 0; //
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.BUFS = 0;        
    AD1CON2bits.SMPI = 0xf; //       
    AD1CON2bits.BUFM = 0;        
    AD1CON2bits.ALTS = 0;     
//ADC setup (pt. 3)    
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 1; //
    AD1CON3bits.ADCS = 1; //
//ADC setup (pt. 4)
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SB = 0;       
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0;

//PIC setup  
    TRISA = 1;             
    TRISB = 0b1111111111111011;
//Timer 3 Setup   
    TMR3 = 0;
    T3CON = 0x0020;
    PR3 = 15624;
    T3CONbits.TON = 1;
//I2C Setup
    
    I2C2CONbits.I2CEN=0; //Disable the I2C2 Module
    I2C2BRG = 0x9D; //Set the Baud-Rate Generator Frequency to 100 kHz, the Code for this is on pg 153 of Family Datasheet 
    
    _MI2C2IF = 0; //Clearing the Interrupt Flag
    I2C2CONbits.I2CEN=1; //Enable the Module
    
    _AD1IF = 0; // clear the ADC ISR flag
    IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1;
}

void initBuffer(void)
{
    int i=0;
    for(i=0; i <= Buffer_Size; i++){
        buffer[i] = 0;
    }
}

unsigned char readFromBuff()
{
    unsigned char x;
    x = buffer[readIdx++];
    readIdx %= Buffer_Size;
    --numEleminBuff;
    
    return x;
}

void putVal(float newVal) // store value in buffer
{
    if(writeIdx > Buffer_Size - 1){
        writeIdx = 0;
    }
    
    buffer[writeIdx++] = newVal;
    return;
}

unsigned long int getAvg(void)
{
    /*unsigned long int total=0;
    unsigned long int avg=0;
    int i=0;
    
    for(i=0; i < Buffer_Size; i++){
        
        total += buffer[i];
    }
    
    avg = total/Buffer_Size;
    
    */
    
    unsigned int average = 0;
    long sum = 0;
    int buffer_index_copy = buffer_index - 1;
    int i;
    for(i=0; i < NUMSAMPLES; i++){
        if( (buffer_index_copy - i) >= 0 )
            sum += buffer[buffer_index_copy - i];
        else
            sum += buffer[Buffer_Size + (buffer_index_copy - i)];
    }
    //average = (unsigned int) (sum / NUMSAMPLES);
    average = (sum / NUMSAMPLES);
    return average;
    
    //return(avg);
}


void lcd_cmd(char command){

    I2C2CONbits.SEN = 1;	//Initiate Start condition
    while(I2C2CONbits.SEN == 1);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0; //Flag needs to be cleared each time

    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2TRN = command; // 8-bits consisting of the data byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
    //_MI2C2IF = 1;
}

void lcd_initi(void){
    
    int count;
    for( count = 0; count < 50; count++){
   
        wait_1ms();
    }
    
    lcd_cmd(0b00111000);
    
    lcd_cmd(0b00111001);
    
    lcd_cmd(0b00010100);
    
    lcd_cmd(0b01110000);
    
    lcd_cmd(0b01010110);
    
    lcd_cmd(0b01101100);
    
   for( count = 0; count < 200; count++){
   
        wait_1ms();
    }
    
    lcd_cmd(0b00111000);
    
    lcd_cmd(0b00001100);
    
    lcd_cmd(0b00000001);
    
  for( count = 0; count < 2; count++){
   
        wait_1ms();
    }
    
    return;
}

void lcd_setCursor(char x, char y){

    char position;
    position = ((x+0x40)*y)+0x80;
    lcd_cmd(position);

}

void lcd_printChar(char myChar){
    
    I2C2CONbits.SEN = 1;	//Initiate Start condition
    while(I2C2CONbits.SEN == 1);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0; //Flag needs to be cleared each time

    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2TRN = 0b01000000; // 8-bits consisting of control byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2TRN = myChar; // 8-bits consisting of the data byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
    //_MI2C2IF = 0;
}
    
void lcd_printStr(const char *s){

    int i;
    unsigned int length;

    length = strlen(s);

    I2C2CONbits.SEN = 1;	//Initiate Start condition
    while(I2C2CONbits.SEN == 1);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0; //Flag needs to be cleared each time

    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    for(i = 0; i < length; i++){

    I2C2TRN = 0b11000000; // 8-bits consisting of control byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;    

    I2C2TRN = s[i]; // 8-bits consisting of the data byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    }

    I2C2TRN = 0b01000000; // 8-bits consisting of control byte
    while(_MI2C2IF == 0);  // SEN will clear when Start Bit is complete
    _MI2C2IF = 0;

    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
    //_MI2C2IF = 0; 
        return;
}  































