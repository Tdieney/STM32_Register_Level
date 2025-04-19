#ifndef __LCD_HD44780_H
#define __LCD_HD44780_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"
void lcd_init (void);
void lcd_command(char cmd);  
void lcd_data (char data);  
void lcd_string (char *str);  
void lcd_goto_xy(int row, int col);
void lcd_16x2_2line_num(unsigned char so, unsigned char x) ;
void lcd_20x4_2line_num(unsigned char so, unsigned char x,unsigned char y) ;
void lcd_20x4_4line_num(unsigned char  so, unsigned char x);
void lcd_clear();
#ifdef __cplusplus
}
#endif
#endif 

