 #include <LPC17xx.H>
 #include <stdio.h>
 #include "lcd.h"
 void delay(unsigned int count)
 {
 unsigned int j=0,k=0;
 for(j=0;j<count;j++)
 {
 for(k=0;k<12000;k++);
 }
 }
 void LCD_DATA(unsigned char val)
 {
 LPC_GPIO2->FIOPIN= val;
 LPC_GPIO0->FIOSET=(1<<28);
 LPC_GPIO0->FIOSET=(1<<27);
 delay(100);
 LPC_GPIO0->FIOCLR=(1<<27);
 delay(100);
 }
 void col_write( unsigned char data )
 {
 unsigned int temp=0;
 temp=(data << 14) & 0X0003C000;
 LPC_GPIO1->FIOCLR = 0X0003C000;
 LPC_GPIO1->FIOSET = temp;
 }
 int main()
 {
 unsigned char array[100]={"PRESSED KEY IS"};
 
 unsigned char i,j,key,key1;
 unsigned char rval[ ] = {0x7,0xB,0xD,0xE,0x0}; 
unsigned char keyPadMatrix[ ] = { 
'C','8','4','0',
 'D','9','5','1',
 ‘E','A','6','2',
 'F','B','7','3‘    
LPC_GPIO0->FIODIR =0X18000000;
 LPC_GPIO2->FIODIR=0x000000FF;
 LPC_GPIO1->FIODIR=0X0003C000;
 LPC_GPIO1->FIODIR&=~0X003C0000;
 init_lcd();
 for(j=0; j<14; j++)
 {
 key1=array[j];
 LCD_DATA(key1);
 delay(100);
 }
 while(1)
 {
 key = 0;
 for( i = 0; i < 4; i++ )
 {
 col_write(rval[i]);
 if (!(LPC_GPIO1->FIOPIN & (1<<18)))
 break;
 key++;
 if (!(LPC_GPIO1->FIOPIN & (1<<19)))
 break;
 key++;
 if (!(LPC_GPIO1->FIOPIN & (1<<20)))
 break;
 key++;
 };
 
 if (!(LPC_GPIO1->FIOPIN & (1<<21)))
 break;
 key++;
 }
 lcd_command_write(0xC8);
 if (!(key == 0x10))
 LCD_DATA(keyPadMatrix[key]);
 delay(10);
 }
 }
