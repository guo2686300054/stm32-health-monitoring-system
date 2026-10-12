#ifndef __1602_H 
#define __1602_H 

#include "systick.h"

#define rs PCout(13) 
#define rw PCout(14)
#define en PCout(15) 
#define beep PBout(11) 
void LCD1602_Init(void); 
void LCD_Write_Command(unsigned char com); 
void LCD_Write_Date(unsigned char date);  
//void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal); 

#endif

