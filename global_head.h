#ifndef __global_head_h__
#define __global_head_h__

#include <STC89C52.h>
#include <intrins.h>

typedef unsigned char Uint8;
typedef unsigned int Uint16;

//DHT11
sbit DHT11_Data = P1^3;  //DHT11数据单总线

//LCD12864
sbit  LCD_SID=P2^1;          //串行数据线
sbit  LCD_SCLK=P2^0;         //串上时钟输入
Uint8 code a[]={"感觉自己萌萌哒"};      //测试一下，不知道为啥就想写个这个，可能是任性

//数码管 两个595控制
sbit Select_bit_Sck = P0^0;				//位选
sbit Select_bit_Rck = P0^1;
sbit Select_bit_Sid = P0^2;
sbit Select_para_Sck = P0^3;				//段选
sbit Select_para_Rck = P0^4;
sbit Select_para_Sid = P0^5;

//蜂鸣器 0开 1关
sbit Buzz = P1^2;

//四个按键
sbit K1=P1^7;
sbit K2=P1^6;
sbit K3=P1^5;
sbit K4=P1^4;

//数组无点
Uint8 N_1[]=
{
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

//数组有点
Uint8 N_2[]=
{
0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef
};

//位选
Uint8 Digital_Bit[]=
{
0x00,0x7f,0xbf,0xdf,0xef,0xf7,0xfb
};

Uint8 Day_per_Month(void);		//计算每月天数并返回
Uint8 CaculateWeekDay(Uint16 y,Uint8 m, Uint8 d);		//计算当前日期为星期几并返回

Uint8 Uint8FLAG,Uint8temp,Uint8comdata,Refresh_TRH,RH_High,RH_Low,T_High,T_Low,
Uint8T_data_H,Uint8T_data_L,Uint8RH_data_H,Uint8RH_data_L,Uint8checkdata,
Uint8T_data_H_temp,Uint8T_data_L_temp,Uint8RH_data_H_temp,Uint8RH_data_L_temp,Uint8checkdata_temp;
char Hours=0,Minutes=0,seconds=0,Months=1,Days=1;		//时、分、秒、月、日
Uint16 Years=2016;		//年份
bit Set_Time=0,Set0=0,Set_Alarm=0;				//Set_Time 设置时,闪烁时长的标志位
																					//Set0设置时间标志，确定是设置‘分’还设置‘时’
																					//然而并不想设置秒，反正也准确不到哪里去
Uint8 Time0_bit=0,Set_YMD=0,K1_bit=0;			//Time0_bit用于定时器0的溢出标志
                                            //Set_YMD用于判断设置年还是月还是日
																						//K1标志位，判断模式
Uint8 Seconds_0,Seconds_1,Seconds_2,Seconds_3,Seconds_4;		//用于秒表的变量
Uint8 Alarm_hours,Alarm_minutes,Alarm_bit;		//用于闹钟时间的设定

void Write_Para_Data(Uint8 dat);		//595写段选数据
void Write_Bit_Data(Uint8 dat);			//595写位选数据
void Delay(Uint8 x);		//延时而已嘛
void Display0(void); 		//时间显示
void Display1(void); 		//秒表显示
void Display2(void);		//时间设置显示
void Display3(void);		//闹钟设置显示
void Display_YMD(void);		//年月日显示
void Display_SetYMD(void);		//日历设置显示
void Display_Weekday(void);		//星期几显示
void Timer_Init(void); 			//中断初始化
void Mode_Set(void);		//模式选择
void KEY_Mode_Set(void);			//模式切换
void KEY_MiaoBiao(void);	//秒表按键
void KEY_Time_Set(void);	 //时间设置按键
void KEY_Alarm_Set(void);		//闹钟设置按键
void KEY_YMD_Set(void);		//年月日设置按键
void Check_Alarm(void);		//检测当前时间是否为闹钟时间
void KEY_Close_Alarm(void);		//检测按键关闭闹钟
void LCD_sendbyte(Uint8 byte);		//LCD发送一个字节数据
void LCD_write_com(Uint8 com);		//LCD发送命令
void LCD_write_dat(Uint8 dat);		//LCD发送数据
void LCD_init(void);		//LCD初始化
void LCD_Print(Uint8 *s);		//LCD打印字符串
void LCD_Setaddress(Uint8 x,Uint8 y);		//LCD设置显示位置 初始位置（1，1）
void LCD_Putstring( Uint8 x, Uint8 y, Uint8 *pData );		//LCD在指定位置打印字符串
void Delay_10us(void);		//延迟10us
void DHT11_COM(void);		//DHT11读数据
void Display_TRH(void);		//温湿度显示

#endif
