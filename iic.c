# include "stm32f4xx.h"
# include "stm32f4xx_rcc.h"
# include "stm32f4xx_gpio.h"
# include "iic.h"
# include "sys.h"
# include "delay.h"
# include "usart.h"

void iic_delay()
{
	
	int i=72;
	while(i--);
		
}

void iic_init_out()
{
	//delay_init(9000);
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SDA_ping|IIC_SCL_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_2MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;                                   
//	gpio_iic.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_iic.GPIO_PuPd=GPIO_PuPd_UP;
	gpio_iic.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
	
//	IIC_SCL_out=1;
//	iic_delay();
//	IIC_SDA_out=1;
//	iic_delay();
//	
//	IIC_SCL_out=0;
//	iic_delay();
//	IIC_SDA_out=0;
//	iic_delay();

}

void iic_init_in()
{
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SDA_ping|IIC_SCL_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;
	gpio_iic.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_iic.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
}

void iicSCL_init_in()
{
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SCL_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;
	gpio_iic.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_iic.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
}
void iicSDA_init_in()
{
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SDA_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;
	gpio_iic.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_iic.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
}
void iicSCL_init_out()
{
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SCL_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;
	gpio_iic.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_iic.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
}

void iicSDA_init_out()
{
	//delay_init(9000);
	RCC_AHB1PeriphClockCmd(IIC_GPIO_RCC,ENABLE);
	
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SDA_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_2MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;                                   
	gpio_iic.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_iic.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
	

}


int iic_start()                            //iic开始信号
{
	
	SCL_L;iic_delay();//while((GPIOB->ODR  & GPIO_Pin_7)==0);
	
	SDA_H;iic_delay();
	
	SCL_H;iic_delay();
	
	if((SCL_read)==0){return 0;} iic_delay();
	
	SDA_L;iic_delay();
	
	SCL_L;iic_delay();
	
	return 1;
	
}

void iic_stop()
{
  SDA_L;iic_delay();
	
	SCL_H;iic_delay();
	
	SDA_H;iic_delay();
	
	SCL_L;iic_delay();
	
}

void iic_ack()      //应答信号
{
	int i=0;
	
	SCL_L;iic_delay();
	
	SDA_L;iic_delay();
	
	SCL_H;iic_delay();
	
  SCL_L;iic_delay();
	
	SCL_L;iic_delay();
	
}

void iic_noack()
{
	
	SCL_L;iic_delay();
	
	SDA_H;iic_delay();
	
	SCL_H;iic_delay();
	
	SCL_L;iic_delay();
	
}

int iic_waitack()
{
	int i;
	
	SCL_L;iic_delay();
	
	SDA_H;iic_delay();
	
	SCL_H;iic_delay();
  
	if(SDA_read)
	{
		
		SCL_L;iic_delay();
		
		return 0;
	}
	
	SCL_L;iic_delay();
	
	return 1;
}

void IIC_write_bit(unsigned char num)            //写一个字节
{
	unsigned char i,j=0;
	unsigned char k;
	k=num;
	SCL_L;iic_delay();
	SDA_L;iic_delay();
	for(i=0;i<8;i++)
	{
		j=0x80&k;
		
		if(j!=0)
			
 		      {SDA_H;iic_delay();}
		
		if (j==0)
			
			    {SDA_L;iic_delay();}
		
		SCL_H;iic_delay();
		
		SCL_L;iic_delay();
		
		k=k<<1;
		
	}
	
}

unsigned  char IIC_read_bit()    //读一个字节-
{
	unsigned char i,j=0,k=0;
	
	SCL_L;iic_delay();
  SDA_H;iic_delay();
	for(i=0;i<8;i++)
	
	{ 
		
		SCL_H;iic_delay();
		
		k=SDA_read;iic_delay();
		
		j=(j<<1);
		
		if(k!=0){j=j|1;}
		
		SCL_L;iic_delay();
		
	}
	
//	    iicSDA_init_out();iic_delay();
	
	return j;
}

void IIC_WrRigist(unsigned char  addr,unsigned char num)    //往一个寄存器写一个字节
{
	
	iic_start();
	
	IIC_write_bit(0x68<<1);iic_waitack();
	
	IIC_write_bit(addr);iic_waitack();
	
	IIC_write_bit(num); iic_waitack();
	
	iic_stop();
	
}

unsigned char IIC_ReRigist(unsigned char addr)             //从一个寄存器读一个字节
{
	unsigned char num=0;
	
	int k;
	
	iic_start();//printf("%d ",k);
	
	IIC_write_bit((0x68)<<1);iic_waitack();
	
	IIC_write_bit(addr);iic_waitack();
	
	iic_start();
	
	IIC_write_bit((0x68)<<1|0x01);iic_waitack();
	
	num=IIC_read_bit();//iic_ack();
//	USART_SendData(UART4,num);
	
//	iic_noack();
	iic_stop();
	
	return num;
}


