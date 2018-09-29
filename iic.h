# ifndef __IIC_H
# define __IIC_H

# define IIC_GPIO_RCC  RCC_AHB1Periph_GPIOB
# define IIC_GPIO_what      GPIOB
# define IIC_SDA_ping       GPIO_Pin_7
# define IIC_SCL_ping       GPIO_Pin_6
# define IIC_SDA_out   PBout(7)
# define IIC_SCL_out   PBout(6)
# define IIC_SDA_in    PBin(7)
# define IIC_SCL_in    PBin(6)

void iic_init_out();
void IIC_WrRigist(unsigned char  addr,unsigned char num);
unsigned char IIC_ReRigist(unsigned char addr);
void iic_delay();

# endif