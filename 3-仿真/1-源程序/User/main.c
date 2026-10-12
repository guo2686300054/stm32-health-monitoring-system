#include "stm32f10x.h"
#include "bsp-lcd1602.h"
#include "delay.h"
#include "sys.h"
#include "adc.h"
#include "ds18b20.h"
#include <stdio.h>
#include "math.h"
#define BEEP PAout(9)
#define KEY1	PCin(1)  //定义LED引脚
#define KEY2	PCin(2)  //定义LED引脚
short tem,tem1;
 u8 a,b,c,t;
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 


void Delay_DS18B20(int num)
{
	while(num--) ;
}
void BEEP_Init(void)
{   
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOD3,6
  
		GPIO_SetBits(GPIOA,GPIO_Pin_9);	
}
void key_init(void)
{
		//新建初始化结构体
	GPIO_InitTypeDef GPIO_InintStruct;
	
		//使能PA,PC端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	GPIO_InintStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InintStruct.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOC, &GPIO_InintStruct);
	

}
int main(void)
	
{
int xueya,maibo=60,t=0,num=0;
	SystemCoreClockUpdate ();
 	LCD1602_Init();
	LCD1602_ShowStr(2,0,"tempe=000.0C",13);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Speed = GPIO_Speed_10MHz;
	g.GPIO_Pin = GPIO_Pin_8  ;
	GPIO_Init(GPIOC,&g);
 	GPIO_SetBits(GPIOC,GPIO_Pin_8);    //输出1

   t=DS18B20_DQ_IN;
while(t){
		DS18B20_IO_OUT(); 	//SET PG11 OUTPUT

    DS18B20_DQ_OUT=0; 	//拉低DQ
	  Delay_DS18B20(750);     	//拉低750us
    DS18B20_DQ_OUT=1; 	//DQ=1 
	  Delay_DS18B20(15);     	//15US
		DS18B20_IO_IN();	//SET PG11 INPUT	 
    Delay_DS18B20(100);
		t=DS18B20_DQ_IN;

}
 tem=DS18B20_Get_Temp();

 ADC1_GPIO_Config();
  ADC_Config(); 
key_init();BEEP_Init();
KEY1=KEY2=1;
while(1)
	{	
		xueya=(float)ADC_GetConversionValue(ADC1)*(3.4/4096)*50;
		if(KEY1==0) 		
		{
		maibo++;if(maibo>999) maibo=999;
		}
		if(KEY2==0) 		
		{
		maibo--;if(maibo<0) maibo=0;
		}
    tem=DS18B20_Get_Temp();
		if(	tem>0)
		{	a=tem/100;
		b=tem%100/10;
		c=tem%10;
		LCD_ShowChar(8,0,'+');
	LCD_ShowNum(9,0,a);	
	LCD_ShowNum(10,0,b);
	LCD_ShowNum(12,0,c);
	
	LCD_ShowChar(0,1,'M');
	LCD_ShowChar(1,1,'B');
	LCD_ShowChar(2,1,'=');
	LCD_ShowNum(3,1,maibo/100);
	LCD_ShowNum(4,1,maibo%100/10);
	LCD_ShowNum(5,1,maibo%10);		

			
			
	LCD_ShowChar(10,1,'X');
	LCD_ShowChar(11,1,'Y');
	LCD_ShowChar(12,1,'=');
	LCD_ShowNum(13,1,xueya/100);
	LCD_ShowNum(14,1,xueya%100/10);
	LCD_ShowNum(15,1,xueya%10);		  
		}
	else 
	{	
//		tem1=(int)tem;
//		tem1=abs(tem1);
		tem1=-(tem);
		tem1=tem1+1;
		a=tem1/100;
		b=tem1%100/10;
		c=tem1%10;
	LCD_ShowChar(8,0,'-');
	LCD_ShowNum(9,0,a);	
	LCD_ShowNum(10,0,b);
	LCD_ShowNum(12,0,c);
		
	}
Delay_DS18B20_1us(10000);
	if(tem>380||maibo>60||maibo<60||xueya>140||xueya<40) BEEP=0;
	else BEEP=1;
  }



}

