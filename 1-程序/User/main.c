#include "stm32f10x.h"
#include "exti.h"
#include "systick.h"
#include "usart.h"
#include "iic.h"
#include "Font.h"
#include "OLED_IIC.h"
#include "18b20.h"
#include "MAX30102.h"
#include "algorithm.h"
#include "blood.h"
#include "lcd.h"
#include "adc.h"
int main(void)
{	
	int i=0;
	USART_CONFIG();
	printf("这是串口调试助手\r\n");
	
	IIC_GPIO_INIT();
	
  OLED_Init();	
	fill_picture(0x00);
	Adc_Init();    //初始化ADC
	Ds18b20_Init();
	DS18B20_Read_Temperature();//初始化ds18b20
	LCD1602_Init();
	MAX30102_GPIO();//初始化心率传感器
	LCD1602_Init();//初始化LCD
	beep=1;
	Max30102_reset();//复位传感器
	
	MAX30102_Config();

	for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//读取FIFO
			max30102_read_fifo();
		}
	}
	while(1)
	{	
	
		deal_Temp();//读取温度
		blood_Loop();//读取脉搏血压
	}
}
