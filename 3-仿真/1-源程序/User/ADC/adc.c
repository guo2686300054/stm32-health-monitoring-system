#include "adc.h"

void ADC1_GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);	//使能ADC1，GPIOC时钟
 	  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//为什么没有配置这个？？？？
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//模拟输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PC4
}


void ADC_Config(void)
{
	

  ADC_InitTypeDef ADC_InitStructure;//ADC结构体变量//注意在一个语句快内变量的声明要放在可执行语句的前面，否则出错，因此要放在ADC1_GPIO_Config();前面
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode =	DISABLE; //使能扫描
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADC转换工作在连续模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//由软件控制转换,不使用外部触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//转换数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;//转换通道为1
  ADC_Init(ADC1, &ADC_InitStructure); //初始化ADC
	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
  ADC_Cmd(ADC1, ENABLE);//使能ADC1
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);


	
}

