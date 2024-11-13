#ifndef LCD_H
#define LCD_H

#include <LPC17xx.H>

// Function Prototypes
void delay(unsigned int count);
void init_lcd(void);
void lcd_command_write(unsigned char command);
void LCD_DATA(unsigned char val);
void lcd_clear(void);
void lcd_display_string(const char *str);

#endif
