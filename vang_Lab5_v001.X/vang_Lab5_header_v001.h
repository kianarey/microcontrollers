/* 
 * File:   vang_Lab5_header_v001.h
 * Author: kiavang
 *
 * Created on July 21, 2019, 9:22 PM
 */

#ifndef VANG_LAB5_HEADER_V001_H
#define	VANG_LAB5_HEADER_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    void delay(int delay_in_ms);
    void lcd_cmd(char command);
    void lcd_init(void);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_printStr(const char *s);
#ifdef	__cplusplus
}
#endif

#endif	/* VANG_LAB5_HEADER_V001_H */

