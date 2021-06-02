/* 
 * File:   vang_Lab3_header_v001.h
 * Author: kiavang
 *
 * Created on June 26, 2019, 8:52 AM
 */

#define PERIOD 1

#ifndef VANG_LAB3_HEADER_V001_H
#define	VANG_LAB3_HEADER_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    void kv_wait_100us(void);
    void kv_wait_1ms(void);
    void delay(int delay_in_ms);
    void init7seg(void);
    void initKeyPad(void);
    int readKeyPadRAW(void);
    char decoder(int input);
    void showChar7seg(char myChar, int myDigit);
    void vangTest7seg(void);
#ifdef	__cplusplus
}
#endif

#endif	/* VANG_LAB2B_HEADER_V001_H */

