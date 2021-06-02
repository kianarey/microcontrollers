/* Date:                  July 6, 2019, 9:43 PM
 * Name:                  Kia Vang
 * Student ID:            4020602
 * Course Number:         EE 2361
 * Term:                  Summer 2019
 * Lab/Assignment Number: Lab 4, Week 1
 * File Name:             vang_Lab4_header_v001.c
 * File Description:      A header file that contains function prototypes for 
 *                        Lab 4 programs.
 */

#ifndef VANG_LAB4_HEADER_V001_H
#define	VANG_LAB4_HEADER_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    void kv_wait_100us(void);
    void kv_wait_1ms(void);
    void delay(int delay_in_ms);
    void initServo(void);
    void setServo(int val);
    void initPushButton(void);   
#ifdef	__cplusplus
}
#endif

#endif	/* VANG_LAB4_HEADER_V001_H */

