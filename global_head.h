#ifndef __global_head_h__
#define __global_head_h__

#include <STC89C52.h>
#include <intrins.h>

typedef unsigned char Uint8;
typedef unsigned int Uint16;

//DHT11
sbit DHT11_Data = P1^3;  //DHT11���ݵ�����

//LCD12864
sbit  LCD_SID=P2^1;          //����������
sbit  LCD_SCLK=P2^0;         //����ʱ������
Uint8 code a[]={"�о��Լ�������"};      //����һ�£���֪��Ϊɶ����д�����������������

//����� ����595����
sbit Select_bit_Sck = P0^0;				//λѡ
sbit Select_bit_Rck = P0^1;
sbit Select_bit_Sid = P0^2;
sbit Select_para_Sck = P0^3;				//��ѡ
sbit Select_para_Rck = P0^4;
sbit Select_para_Sid = P0^5;

//������ 0�� 1��
sbit Buzz = P1^2;

//�ĸ�����
sbit K1=P1^7;
sbit K2=P1^6;
sbit K3=P1^5;
sbit K4=P1^4;

//�����޵�
Uint8 N_1[]=
{
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

//�����е�
Uint8 N_2[]=
{
0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef
};

//λѡ
Uint8 Digital_Bit[]=
{
0x00,0x7f,0xbf,0xdf,0xef,0xf7,0xfb
};

Uint8 Day_per_Month(void);		//����ÿ������������
Uint8 CaculateWeekDay(Uint16 y,Uint8 m, Uint8 d);		//���㵱ǰ����Ϊ���ڼ�������

Uint8 Uint8FLAG,Uint8temp,Uint8comdata,Refresh_TRH,RH_High,RH_Low,T_High,T_Low,
Uint8T_data_H,Uint8T_data_L,Uint8RH_data_H,Uint8RH_data_L,Uint8checkdata,
Uint8T_data_H_temp,Uint8T_data_L_temp,Uint8RH_data_H_temp,Uint8RH_data_L_temp,Uint8checkdata_temp;
char Hours=0,Minutes=0,seconds=0,Months=1,Days=1;		//ʱ���֡��롢�¡���
Uint16 Years=2016;		//���
bit Set_Time=0,Set0=0,Set_Alarm=0;				//Set_Time ����ʱ,��˸ʱ���ı�־λ
																					//Set0����ʱ���־��ȷ�������á��֡������á�ʱ��
																					//Ȼ�������������룬����Ҳ׼ȷ��������ȥ
Uint8 Time0_bit=0,Set_YMD=0,K1_bit=0;			//Time0_bit���ڶ�ʱ��0�������־
                                            //Set_YMD�����ж������껹���»�����
																						//K1��־λ���ж�ģʽ
Uint8 Seconds_0,Seconds_1,Seconds_2,Seconds_3,Seconds_4;		//�������ı���
Uint8 Alarm_hours,Alarm_minutes,Alarm_bit;		//��������ʱ����趨

void Write_Para_Data(Uint8 dat);		//595д��ѡ����
void Write_Bit_Data(Uint8 dat);			//595дλѡ����
void Delay(Uint8 x);		//��ʱ������
void Display0(void); 		//ʱ����ʾ
void Display1(void); 		//�����ʾ
void Display2(void);		//ʱ��������ʾ
void Display3(void);		//����������ʾ
void Display_YMD(void);		//��������ʾ
void Display_SetYMD(void);		//����������ʾ
void Display_Weekday(void);		//���ڼ���ʾ
void Timer_Init(void); 			//�жϳ�ʼ��
void Mode_Set(void);		//ģʽѡ��
void KEY_Mode_Set(void);			//ģʽ�л�
void KEY_MiaoBiao(void);	//�����
void KEY_Time_Set(void);	 //ʱ�����ð���
void KEY_Alarm_Set(void);		//�������ð���
void KEY_YMD_Set(void);		//���������ð���
void Check_Alarm(void);		//��⵱ǰʱ���Ƿ�Ϊ����ʱ��
void KEY_Close_Alarm(void);		//��ⰴ���ر�����
void LCD_sendbyte(Uint8 byte);		//LCD����һ���ֽ�����
void LCD_write_com(Uint8 com);		//LCD��������
void LCD_write_dat(Uint8 dat);		//LCD��������
void LCD_init(void);		//LCD��ʼ��
void LCD_Print(Uint8 *s);		//LCD��ӡ�ַ���
void LCD_Setaddress(Uint8 x,Uint8 y);		//LCD������ʾλ�� ��ʼλ�ã�1��1��
void LCD_Putstring( Uint8 x, Uint8 y, Uint8 *pData );		//LCD��ָ��λ�ô�ӡ�ַ���
void Delay_10us(void);		//�ӳ�10us
void DHT11_COM(void);		//DHT11������
void Display_TRH(void);		//��ʪ����ʾ

#endif
