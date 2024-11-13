#include <LPC17xx.H>
#include "lcd.h"

// Delay Function
void delay(unsigned int count) {
    unsigned int j = 0, k = 0;
    for (j = 0; j < count; j++) {
        for (k = 0; k < 12000; k++); // Rough delay loop
    }
}

// Initialize LCD
void init_lcd(void) {
    lcd_command_write(0x38); // 8-bit, 2-line display, 5x7 font
    lcd_command_write(0x0C); // Display ON, cursor OFF
    lcd_command_write(0x06); // Entry mode set, increment cursor
    lcd_command_write(0x01); // Clear display
    delay(10);
}

// Send Command to LCD
void lcd_command_write(unsigned char command) {
    LPC_GPIO2->FIOPIN = command;
    LPC_GPIO0->FIOCLR = (1 << 28); // RS = 0 (Command mode)
    LPC_GPIO0->FIOSET = (1 << 27); // Enable high
    delay(100);
    LPC_GPIO0->FIOCLR = (1 << 27); // Enable low
    delay(100);
}

// Send Data to LCD
void LCD_DATA(unsigned char val) {
    LPC_GPIO2->FIOPIN = val;
    LPC_GPIO0->FIOSET = (1 << 28); // RS = 1 (Data mode)
    LPC_GPIO0->FIOSET = (1 << 27); // Enable high
    delay(100);
    LPC_GPIO0->FIOCLR = (1 << 27); // Enable low
    delay(100);
}

// Clear LCD Display
void lcd_clear(void) {
    lcd_command_write(0x01); // Clear display command
    delay(10);
}

// Display String on LCD
void lcd_display_string(const char *str) {
    while (*str) {
        LCD_DATA(*str++);
        delay(100);
    }
}
