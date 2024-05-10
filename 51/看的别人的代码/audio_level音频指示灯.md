#include <stdlib.h>
#include <reg52.h>

typedef unsigned int u16;   //对系统默认数据类型进行重定义
typedef unsigned char u8;

#define SEG_PORT P0	//使用宏定义数码管段码口

//管脚定义
sbit DOUT = P3^7;   //输出
sbit CLK  = P3^6;   //时钟
sbit DIN  = P3^4;   //输入
sbit CS   = P3^5;   //片选
sbit LSA=P2^2;  //定义数码管位选信号控制脚
sbit LSB=P2^3;
sbit LSC=P2^4;

void xpt2046_wirte_data(u8 dat)
{
    u8 i;
    CLK = 0;
    for(i=0;i<8;i++)//循环8次，每次传输一位，共一个字节
    {
        DIN = dat >> 7;//先传高位再传低位
        dat <<= 1;//将低位移到高位
        CLK = 0;//CLK由低到高产生一个上升沿，从而写入数据
        CLK = 1;
    }
}

u16	xpt2046_read_data(void)
{
    u8 i;
    u16 dat=0;
    CLK = 0;
    for(i=0;i<12;i++)//循环12次，每次读取一位，大于一个字节数，所以返回值类型是u16
    {
        dat <<= 1;
        CLK = 1;
        CLK = 0; //CLK由高到低产生一个下降沿，从而读取数据
        dat |= DOUT;//先读取高位，再读取低位。	
    }
    return dat;	
}

u16 xpt2046_read_adc_value(u8 cmd)
{
    u8 i;
    u16 adc_value=0;

    CLK = 0;//先拉低时钟
    CS  = 0;//使能XPT2046
    xpt2046_wirte_data(cmd);//发送命令字
    for(i=6; i>0; i--);//延时等待转换结果
    CLK = 1;
    CLK = 0;//发送一个时钟，清除BUSY
    adc_value=xpt2046_read_data();
    CS = 1;//关闭XPT2046
    return adc_value;
}

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

void seg_display_level(u8 level)
{
    static u8 dis_buf[8];
    u8 i = 0, n, half;

    if (level > 16) level = 16;
    half = level & 1;
    n = level >> 1;
    for(i=0; i<n; i++) {
        dis_buf[i] = 0x36;
    }
    if (half) {
        dis_buf[i++] = 0x30;
    }
    n += half;

    for(i=0;i<n;i++)
    {
        switch(i)//位选
        {
            case 0: LSC=1;LSB=1;LSA=1;break;
            case 1: LSC=1;LSB=1;LSA=0;break;
            case 2: LSC=1;LSB=0;LSA=1;break;
            case 3: LSC=1;LSB=0;LSA=0;break;
            case 4: LSC=0;LSB=1;LSA=1;break;
            case 5: LSC=0;LSB=1;LSA=0;break;
            case 6: LSC=0;LSB=0;LSA=1;break;
            case 7: LSC=0;LSB=0;LSA=0;break;
        }
        SEG_PORT = dis_buf[i];
        delay_10us(100);
        SEG_PORT = 0x00;
    }
}

void main()
{
    u16 adc_value=0;
    while(1)
    {
        adc_value=xpt2046_read_adc_value(0xE4);//测量外部输入通道AIN3
        seg_display_level(abs(adc_value - 1024) / 60);		
    }
}


