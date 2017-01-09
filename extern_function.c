/*	懒死算啦，哈哈哈
	Based on first version	*/

#include <STC89C52.h>
#include <intrins.h>
#include "global_head.h"

void Mode_Set(void)
	{
			switch(K1_bit)		 				//模式选择
				{
					case 0:
						{
							Display0();			//显示时间
							Display_YMD();
							Check_Alarm();
							KEY_Close_Alarm();
							if(Refresh_TRH>=1)
							{Refresh_TRH=0;
								Display_TRH();}
							break;
						}
					case 1:
						{
							Display1();	 		//显示秒表
							KEY_MiaoBiao();
							break;
						}
					case 2:
							{
								Display2();		//设置时间
								KEY_Time_Set();
								break;
							}
					case 3:
					{
															//设置年月日
								Display_YMD();
								KEY_YMD_Set();
						    Display_Weekday();
								break;

					}
					case 4:
							{
								Alarm_bit=0;
								Display3();		//设置闹钟
								KEY_Alarm_Set();
								break;
							}
				}
	}

void KEY_Mode_Set(void)									//模式选择 默认显示时间
{
	if(K1==0)
		{
			Delay(10);
			if(K1==0)
				{
					K1_bit++;
					if(K1_bit==5)
						{
							K1_bit=0;
						}
					while(!K1);
				}
		}
}
void KEY_MiaoBiao()								//秒表按键
{
	if(K1_bit==1)								//判断是否为秒表模式
		{
			if(K2==0)
				{
					Delay(10);
					if(K2==0)
						{
							TR1=~TR1;			//暂停或开始秒表
							while(!K2);
						}
				}
			if(K3==0)
				{
					Delay(10);
					if(K3==0)	 				//当K3按下时秒表所有数据清零，并停止定时器1
						{
							TR1=0;	 			//停止定时器1
							Seconds_0=0; 		//清零数据
							Seconds_1=0;
							Seconds_2=0;
							Seconds_3=0;
							Seconds_4=0;
							while(!K3);
						}
				}
		}
}

void KEY_Time_Set(void)	   							//设置时间按键
{
	if(K1_bit==2)
		{
			if(K2==0)
				{
					Delay(10);
					if(K2==0)
						{
							if(Set0==0)
								{
									Minutes++;
									if(Minutes==60)
										Minutes=0;
								}
							else
								{
									Hours++;
									if(Hours==24)
										Hours=0;
								}
							while(!K2);
						}
				}
			if(K3==0)
				{
					Delay(10);
					if(K3==0)
						{
							if(Set0==0)
								{
									Minutes--;
									if(Minutes==-1)
										Minutes=59;
								}
							else
								{
									Hours--;
									if(Hours==-1)
										Hours=23;
								}
							while(!K3);
						}
				}
			if(K4==0)
				{
					Delay(10);
					if(K4==0)
						{
							Set0=~Set0;
							while(!K4);
						}
				}
		}
}

void KEY_YMD_Set(void)		//年月日设置
{

	if(K1_bit==3)
	{
	if(K2==0)
				{
					Delay(10);
					if(K2==0)
						{
							switch(Set_YMD)
							{
								case 0:
								{
									Years++;
									if(Years==2100)
										Years=2016;
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
								case 1:
								{
									Months++;
									if(Months==13)
										Months=1;
									if(Days>Day_per_Month())
										Days=Day_per_Month();
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
								case 2:
								{
									Days++;
									if(Days>Day_per_Month())
										Days=1;
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
							}
							while(!K2);
						}
				}
	if(K3==0)
				{
					Delay(10);
					if(K3==0)
						{
							switch(Set_YMD)
							{
								case 0:
								{
									Years--;
									if(Years==2015)
										Years=2099;
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
								case 1:
								{
									Months--;
									if(Months==0)
										Months=12;
									if(Days>Day_per_Month())
										Days=Day_per_Month();
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
								case 2:
								{
									Days--;
									if(Days==0)
										Days=Day_per_Month();
									//LCD_write_com(0x01);
									//Display_YMD();
									break;
								}
							}
							while(!K3);
						}
				}
	if(K4==0)
				{
					Delay(10);
					if(K4==0)
						{
							Set_YMD++;
							if(Set_YMD>2)
								Set_YMD=0;
							while(!K4);
						}
				}

	}
}
void KEY_Alarm_Set(void)		//闹钟设置
{
	if(K1_bit==4)
		{
			if(K2==0)
				{
					Delay(10);
					if(K2==0)
						{
							if(Set0==0)
								{
									Set_Alarm=1;
									Alarm_minutes++;
									if(Alarm_minutes==60)
										Alarm_minutes=0;
								}
							else
								{
									Set_Alarm=1;
									Alarm_hours++;
									if(Alarm_hours==24)
										Alarm_hours=0;
								}
							while(!K2);
						}
				}
			if(K3==0)
				{
					Delay(10);
					if(K3==0)
						{
							if(Set0==0)
								{
									Set_Alarm=1;
									Alarm_minutes--;
									if(Alarm_minutes==-1)
										Alarm_minutes=59;
								}
							else
								{
									Set_Alarm=1;
									Alarm_hours--;
									if(Alarm_hours==-1)
										Alarm_hours=23;
								}
							while(!K3);
						}
				}
			if(K4==0)
				{
					Delay(10);
					if(K4==0)
						{
							Set0=~Set0;
							Set_Alarm=1;
							while(!K4);
						}
				}
		}
}

void KEY_Close_Alarm(void)
{
	if(K4==0)
	{
	Delay(10);
	if(K4==0)
		{
			Alarm_bit=0;
		}
	}
}
void Check_Alarm(void)		//检查闹钟哦
{
	if(Set_Alarm==1)
	{
		if(Hours==Alarm_hours)
		{
			if(Minutes==Alarm_minutes)
				{
					if(seconds>=0&&seconds<=3)
					Alarm_bit = 1;
				}
		}
	}
	if(Alarm_bit==1)
		Buzz = 0;
	else
		Buzz = 1;
}

void Display0(void)		//时间显示
{

	Write_Para_Data(N_1[seconds%10]);
	Write_Bit_Data(Digital_Bit[6]);
	Delay(1);
	Write_Bit_Data(0xff);

	Write_Para_Data(N_1[seconds/10]);
	Write_Bit_Data(Digital_Bit[5]);
	Delay(1);
	Write_Bit_Data(0xff);

	Write_Para_Data(N_2[Minutes%10]);
	Write_Bit_Data(Digital_Bit[4]);
	Delay(1);
	Write_Bit_Data(0xff);

	Write_Para_Data(N_1[Minutes/10]);
	Write_Bit_Data(Digital_Bit[3]);
	Delay(1);
	Write_Bit_Data(0xff);

	Write_Para_Data(N_2[Hours%10]);
	Write_Bit_Data(Digital_Bit[2]);
	Delay(1);
	Write_Bit_Data(0xff);

	Write_Para_Data(N_1[Hours/10]);
	Write_Bit_Data(Digital_Bit[1]);
	Delay(1);
	Write_Bit_Data(0xff);

//	LCD_Setaddress(2,3);
//	LCD_write_dat(0X30+(Hours/10));
//	LCD_write_dat(0X30+(Hours%10));
//	LCD_Print(":");
//	LCD_write_dat(0X30+(Minutes/10));
//	LCD_write_dat(0X30+(Minutes%10));
//	LCD_Print(":");
//	LCD_write_dat(0X30+(seconds/10));
//	LCD_write_dat(0X30+(seconds%10));
//
}

void Display1(void)		//秒表显示
{

			Write_Para_Data(N_1[Seconds_1%10]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_2[Seconds_2%10]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Seconds_2/10]);
			Write_Bit_Data(Digital_Bit[4]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_2[Seconds_3%10]);
			Write_Bit_Data(Digital_Bit[3]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Seconds_3/10]);
			Write_Bit_Data(Digital_Bit[2]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Seconds_4%10]);
			Write_Bit_Data(Digital_Bit[1]);
			Delay(2);
			Write_Bit_Data(0xff);
}

void Display2(void)		//设置时间
{
	if(Set0==0)							//判断是否为设置时还是分
		{
			Write_Para_Data(N_1[seconds%10]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[seconds/10]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//分钟以0.5秒的频率闪烁
				{
					Write_Para_Data(N_2[Minutes%10]);
					Write_Bit_Data(Digital_Bit[4]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(N_1[Minutes/10]);
					Write_Bit_Data(Digital_Bit[3]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
			else
				{
					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[4]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[3]);
					Delay(2);
					Write_Bit_Data(0xff);
				}

			Write_Para_Data(N_2[Hours%10]);
			Write_Bit_Data(Digital_Bit[2]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Hours/10]);
			Write_Bit_Data(Digital_Bit[1]);
			Delay(2);
			Write_Bit_Data(0xff);
		}

	else
		{
			Write_Para_Data(N_1[seconds%10]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[seconds/10]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_2[Minutes%10]);
			Write_Bit_Data(Digital_Bit[4]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Minutes/10]);
			Write_Bit_Data(Digital_Bit[3]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//小时以0.5秒的频率闪烁
				{
					Write_Para_Data(N_2[Hours%10]);
					Write_Bit_Data(Digital_Bit[2]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(N_1[Hours/10]);
					Write_Bit_Data(Digital_Bit[1]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
			else
				{
					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[2]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[1]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
		}
}

void Display3(void)		//设置闹钟
{
	if(Set0==0)			//判断是否为设置时还是分
		{
			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//同上面函数
				{
					Write_Para_Data(N_2[Alarm_minutes%10]);
					Write_Bit_Data(Digital_Bit[4]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(N_1[Alarm_minutes/10]);
					Write_Bit_Data(Digital_Bit[3]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
			else
				{
					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[4]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[3]);
					Delay(2);
					Write_Bit_Data(0xff);
				}

			Write_Para_Data(N_2[Alarm_hours%10]);
			Write_Bit_Data(Digital_Bit[2]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Alarm_hours/10]);
			Write_Bit_Data(Digital_Bit[1]);
			Delay(2);
			Write_Bit_Data(0xff);
		}

	else
		{
			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_2[Alarm_minutes%10]);
			Write_Bit_Data(Digital_Bit[4]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[Alarm_minutes/10]);
			Write_Bit_Data(Digital_Bit[3]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//同上面函数
				{
					Write_Para_Data(N_2[Alarm_hours%10]);
					Write_Bit_Data(Digital_Bit[2]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(N_1[Alarm_hours/10]);
					Write_Bit_Data(Digital_Bit[1]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
			else
				{
					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[2]);
					Delay(2);
					Write_Bit_Data(0xff);

					Write_Para_Data(0x00);
					Write_Bit_Data(Digital_Bit[1]);
					Delay(2);
					Write_Bit_Data(0xff);
				}
		}
}

void Display_YMD(void)		//设置年月日 显示
{

		LCD_Setaddress(1,1);

		LCD_write_dat(0X30+(2));
		LCD_write_dat(0X30+(0));
		LCD_write_dat(0X30+((Years%100)/10));
		LCD_write_dat(0X30+((Years%10)));
		LCD_Print("年  ");

		LCD_write_dat(0X30+(Months/10));
		LCD_write_dat(0X30+(Months%10));
		LCD_Print("月");

		LCD_write_dat(0X30+(Days/10));
		LCD_write_dat(0X30+(Days%10));
		LCD_Print("日");

}

Uint8 CaculateWeekDay(Uint16 y,Uint8 m, Uint8 d)		//计算当前为星期几
																										//使用基姆拉尔森计算公式
																										//参考：http://blog.csdn.net/ycrao/article/details/3825
{
	int week = 0;
	if(m == 1 | m == 2)
	{
		m += 12;
		--y;
	}
	week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 -y / 100 +y / 400) % 7 + 1;
	return week;
}

void Display_Weekday(void)		//显示当前为星期几
{
switch(CaculateWeekDay(Years,Months,Days))
		{
			case 1:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  一");
				break;
			}
			case 2:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  二");
				break;
			}
			case 3:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  Ⅲ");
				break;
			}
			case 4:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  四");
				break;
			}
			case 5:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  五");
				break;
			}
			case 6:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  六");
				break;
			}
			case 7:
			{
				LCD_Setaddress(2,2);
				LCD_Print("星  期  日");
				break;
			}
			default:		//其实没啥用，就怕万一抽风算不出来了
			{
				LCD_Setaddress(2,2);
				LCD_Print("呵  呵  哒");
				break;
			}
		}
}
void Delay(Uint8 x)		//延迟延时，萌萌哒
{
	Uint8 i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
	 _nop_();
}

void Write_Para_Data(unsigned char dat)		//写段选数据
{
	 Uint8 x;
	 Select_para_Rck=0;
	 for(x=0;x<8;x++)
	 {
	   Select_para_Sck=0;
     Select_para_Sid=(dat<<x)&0x80;		//写数据后按位移入寄存器然后置入锁存器
     Select_para_Sck=1;
	 }
	 Select_para_Rck=1;
}
void Write_Bit_Data(unsigned char dat)		//写位选数据
{
	 Uint8 x;
	 Select_bit_Rck=0;
	 for(x=0;x<8;x++)
	 {
	   Select_bit_Sck=0;
     Select_bit_Sid=(dat<<x)&0x80;	  //写数据后按位移入寄存器然后置入锁存器
     Select_bit_Sck=1;
	 }
	 Select_bit_Rck=1;
}

void Timer_Init(void)		//中断初始化
{
	EA=1;
	TMOD=0X11;

	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	ET0=1;
	TR0=1;

	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	ET1=1;
	TR1=0;


}

void Time0(void) interrupt 1 					//定时器0函数
{
	TH0=(65536-45872)/256;	   				//重装初值
	TL0=(65536-45872)%256;
	Time0_bit++;
	if((Time0_bit%10)==0)					//每溢出10次Time0_bit取反一次
		Set_Time=~Set_Time;	  				//0.5秒闪烁一次

	if(Time0_bit==20)						//以下为时间数据处理
		{
			Time0_bit=0;
			seconds++;
			Refresh_TRH++;
			if(seconds==60)
				{
					seconds=0;
					Minutes++;
					if(Minutes==60)
						{
							Minutes=0;
							Hours++;
							if(Hours==24)
								{
									Hours=0;
									Days++;
									if(Days>Day_per_Month())
									{
										Days=1;
										Months++;
										if(Months>12)
										{
											Months=1;
											Years++;
										  if(Years>2100)
											{
												Years=2016;
											}
										}
									}
								}
						}
				}

		}
}

void Time1(void) interrupt 3  			//定时器1函数
{
	TH1=(65536-45872)/256;			//重装初值
	TL1=(65536-45872)%256;

	Seconds_0++;
	if(Seconds_0==2)				//以下为秒表数据处理
		{
			Seconds_0=0;
			Seconds_1++;	 		//Seconds_1每加1次为100ms，
			if(Seconds_1==10)
				{
					Seconds_1=0;
					Seconds_2++;
					if(Seconds_2==60)
						{
							Seconds_2=0;
							Seconds_3++;
							if(Seconds_3==60)
								{
									Seconds_3=0;
									Seconds_4++;
									if(Seconds_4==10)
										Seconds_4=0;
								}
						}
				}
		}
}


Uint8 Day_per_Month(void)		//我就是算算每个月有多少天而已啦
	{
    switch(Months) {
    case 2:
        if((Years%4==0&&(Years%100)!=0)||Years%400==0) {
            return 29;
        }else{
            return 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11: return 30; break;
    default: return 31; break;
    }
}

void LCD_sendbyte(Uint8 byte)		//发字节数据
{
   Uint8 i;
   for(i=0;i<8;i++)
    {
   LCD_SCLK=0;               //拉低时钟线
   _nop_();
   LCD_SID=(bit)(byte&0x80);    //发送最高位数据
   LCD_SCLK=1;               //上升沿发送数据
   byte=byte<<1;                  //左移一位
 }
}

void LCD_write_com(Uint8 com)		//写命令
{
   LCD_sendbyte(0xf8);       		//11111,RW(0),RS(0),0
   LCD_sendbyte(0xf0&com);       //取高四位，数据分两次传送，
                                 //每个字节的内容被送入两个字节
																//高四位放在第一个字节的高四位
   LCD_sendbyte(0xf0&(com<<4));        //低四位放在第二个字节的高四位
  Delay(10);
}

void LCD_write_dat(Uint8 dat)		//写数据
{
   LCD_sendbyte(0xfa);        //11111,RW(0),RS(1),0
   LCD_sendbyte(0xf0&dat);       //取高四位，数据分两次传送，
                                 //每个字节的内容被送入两个字节
																//高四位放在第一个字节的高四位
   LCD_sendbyte(0xf0&(dat<<4));        //低四位放在第二个字节
	_nop_();
}

void LCD_init(void)		//初始化啦
{
 LCD_write_com(0x30);             //基本指令集
 LCD_write_com(0x0c);       //开显示，无游标，不反白
 LCD_write_com(0x01);       //清屏
 Delay(5);
 LCD_write_com(0x02);       //清DDRAM位址
 LCD_write_com(0x06);       //光标右移，显示不动
}

void LCD_Print(Uint8 *s)		//写字符串
{
    while(*s!='\0')
    {
       LCD_write_dat(*s);
       s++;
    }
}

void LCD_Setaddress(Uint8 x,Uint8 y)		//指定位置写字符串
{              //地址从第1行第1列开始
  Uint8 addr;
  switch(x)
  {
   case 1: addr=0x80+y-1;
           break;
   case 2: addr=0x90+y-1;
           break;
   case 3: addr=0x88+y-1;
           break;
   case 4: addr=0x98+y-1;
           break;
   default : break;
  }
   LCD_write_com(addr);
}

void LCD_Putstring( Uint8 x, Uint8 y, Uint8 *pData )		//指定位置呢 从（1，1）开始哦。。
{
 LCD_Setaddress(x,y);
 while( *pData != '\0' )
 {
   LCD_write_dat( *pData++ );
 }
}

void Delay_10us(void)		//延迟10us
{
    Uint8 i;
		i = 2;
		while (--i);
}

void DHT11_COM(void)		//DHT11读数据
{
    Uint8 i;
    for(i=0; i<8; i++)
    {
        Uint8FLAG=2;
        while((!DHT11_Data)&&Uint8FLAG++);
        Delay_10us();
        Delay_10us();
        Delay_10us();
        Uint8temp=0;
        if(DHT11_Data)Uint8temp=1;
        Uint8FLAG=2;
        while((DHT11_Data)&&Uint8FLAG++);
        if(Uint8FLAG==1)break;
        Uint8comdata<<=1;
        Uint8comdata|=Uint8temp;
}
}

void Display_TRH(void)		//显示温湿度
{

    DHT11_Data=0;
    Delay(34);
    DHT11_Data=1;
    Delay_10us();
    Delay_10us();
    Delay_10us();
    Delay_10us();
    DHT11_Data=1;
    if(!DHT11_Data)
    {
        Uint8FLAG=2;
        while((!DHT11_Data)&&Uint8FLAG++);
        Uint8FLAG=2;
        while((DHT11_Data)&&Uint8FLAG++);
        DHT11_COM();
        Uint8RH_data_H_temp=Uint8comdata;
        DHT11_COM();
        Uint8RH_data_L_temp=Uint8comdata;
        DHT11_COM();
        Uint8T_data_H_temp=Uint8comdata;
        DHT11_COM();
        Uint8T_data_L_temp=Uint8comdata;
        DHT11_COM();
        Uint8checkdata_temp=Uint8comdata;
        DHT11_Data=1;
        Uint8temp=(Uint8T_data_H_temp+Uint8T_data_L_temp+Uint8RH_data_H_temp+Uint8RH_data_L_temp);
        if(Uint8temp==Uint8checkdata_temp)
        {
            Uint8RH_data_H=Uint8RH_data_H_temp;
            Uint8RH_data_L=Uint8RH_data_L_temp;
            Uint8T_data_H=Uint8T_data_H_temp;
            Uint8T_data_L=Uint8T_data_L_temp;
            Uint8checkdata=Uint8checkdata_temp;
        }
        RH_High=Uint8RH_data_H/10;
        RH_Low=Uint8RH_data_H%10;
        T_High=Uint8T_data_H/10;
        T_Low=Uint8T_data_H%10;
    }
    LCD_Setaddress(3,1);
		LCD_Print("T:");
		LCD_write_dat(0X30+T_High);
		LCD_write_dat(0X30+T_Low);
		LCD_Print("    RH:");
		LCD_write_dat(0X30+RH_High);
		LCD_write_dat(0X30+RH_Low);
}
