/* 
 * File:   vang_Lab6_header_v001.h
 * Author: kiavang
 *
 * Created on February 7, 2020, 11:43 AM
 */

#ifndef VANG_LAB6_HEADER_V001_H
#define	VANG_LAB6_HEADER_V001_H

#ifdef	__cplusplus
extern "C" {
#endif

void wait_1ms(void);
void putVal(float newValue);
void setup(void);
unsigned long int getAvg(void);
void initBuffer(void);
void lcd_cmd(char command);
void lcd_initi(void);
void lcd_setCursor(char x, char y);
void lcd_printChar(char myChar);
void lcd_printStr(const char *s);


#ifdef	__cplusplus
}
#endif

#endif	/* VANG_LAB6_HEADER_V001_H */

