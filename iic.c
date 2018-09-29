# include "stm32f4xx.h"
# include "stm32f4xx_rcc.h"
# include "stm32f4xx_gpio.h"
# include "iic.h"
# include "sys.h"
# include "delay.h"
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
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;                                   
	gpio_iic.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_iic.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
	
	IIC_SCL_out=1;
	iic_delay();
	IIC_SDA_out=1;
	iic_delay();
	
	IIC_SCL_out=0;
	iic_delay();
	IIC_SDA_out=0;
	iic_delay();

}

void iic_init_in()
{
	GPIO_InitTypeDef gpio_iic;
	gpio_iic.GPIO_Pin = IIC_SDA_ping|IIC_SCL_ping;
	gpio_iic.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_iic.GPIO_OType= GPIO_OType_PP;
	gpio_iic.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_iic.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(IIC_GPIO_what,&gpio_iic);
}

void iic_start()                            //iic开始信号
{
	IIC_SCL_out=0;
	iic_delay();
	IIC_SDA_out=1;
	iic_delay();
	IIC_SCL_out=1;
	iic_delay();
	IIC_SDA_out=0;
	iic_delay();
	IIC_SCL_out=0;
	iic_delay();
}

void iic_stop()
{
	IIC_SDA_out=0;
	iic_delay();
	IIC_SCL_out=1;
	iic_delay();
	IIC_SDA_out=1;
	iic_delay();
	IIC_SCL_out=0;
	iic_delay();
	
}

void iic_ack()
{
	int i=0;
	IIC_SCL_out=0;
	iic_delay();
	IIC_SDA_out=1;
	iic_delay();
	IIC_SCL_out=1;
//	while((IIC_SDA_in==0)&&i<255)
//	{
//		i++;
//	}
	iic_delay();
	IIC_SDA_out=0;
	iic_delay();
	IIC_SCL_out=0;
	iic_delay();
}

void iic_waitack()
{
	int i;
	IIC_SCL_out=0;
	iic_delay();
	IIC_SDA_out=1;
	iic_delay();
IIC_SCL_out=1;
	while(((IIC_SDA_out)==1)&&i<255)
		i++;
	
	iic_delay();
}

void IIC_write_bit(unsigned char num)            //写一个字节
{
	unsigned char i,j=0;
	IIC_SDA_out=0;
	for(i=0;i<8;i++)
	{
		j=0x80&num;
		if(j!=0)
		    IIC_SDA_out=1;
 		IIC_SCL_out=1;
		iic_delay();

		iic_delay();
		IIC_SCL_out=0;
		iic_delay();
		IIC_SDA_out=0;
		iic_delay();
		num=num<<1;
	}
	
}

unsigned  char IIC_read_bit()    //读一个字节-
{
	unsigned char i,j=0,k=0;
	IIC_SDA_out=1;iic_delay();
	for(i=0;i<8;i++)
	{ 
		IIC_SCL_out=1;
		iic_delay();
		k=IIC_SDA_in;
		j=(j<<1)|k;
	  IIC_SCL_out=0;
		iic_delay();
	}
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
	unsigned num;
	iic_start();
	IIC_write_bit(0x68<<1);iic_waitack();
	IIC_write_bit(addr);iic_waitack();
	iic_start();
	IIC_write_bit(0x68*2+0x01);iic_waitack();
	num=IIC_read_bit();iic_ack();
	iic_stop();
	return num;
}


