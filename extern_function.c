/*	����������������
	Based on first version	*/

#include <STC89C52.h>
#include <intrins.h>
#include "global_head.h"

void Mode_Set(void)
	{
			switch(K1_bit)		 				//ģʽѡ��
				{
					case 0:
						{
							Display0();			//��ʾʱ��
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
							Display1();	 		//��ʾ���
							KEY_MiaoBiao();
							break;
						}
					case 2:
							{
								Display2();		//����ʱ��
								KEY_Time_Set();
								break;
							}
					case 3:
					{
															//����������
								Display_YMD();
								KEY_YMD_Set();
						    Display_Weekday();
								break;

					}
					case 4:
							{
								Alarm_bit=0;
								Display3();		//��������
								KEY_Alarm_Set();
								break;
							}
				}
	}

void KEY_Mode_Set(void)									//ģʽѡ�� Ĭ����ʾʱ��
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
void KEY_MiaoBiao()								//�����
{
	if(K1_bit==1)								//�ж��Ƿ�Ϊ���ģʽ
		{
			if(K2==0)
				{
					Delay(10);
					if(K2==0)
						{
							TR1=~TR1;			//��ͣ��ʼ���
							while(!K2);
						}
				}
			if(K3==0)
				{
					Delay(10);
					if(K3==0)	 				//��K3����ʱ��������������㣬��ֹͣ��ʱ��1
						{
							TR1=0;	 			//ֹͣ��ʱ��1
							Seconds_0=0; 		//��������
							Seconds_1=0;
							Seconds_2=0;
							Seconds_3=0;
							Seconds_4=0;
							while(!K3);
						}
				}
		}
}

void KEY_Time_Set(void)	   							//����ʱ�䰴��
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

void KEY_YMD_Set(void)		//����������
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
void KEY_Alarm_Set(void)		//��������
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
void Check_Alarm(void)		//�������Ŷ
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

void Display0(void)		//ʱ����ʾ
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

void Display1(void)		//�����ʾ
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

void Display2(void)		//����ʱ��
{
	if(Set0==0)							//�ж��Ƿ�Ϊ����ʱ���Ƿ�
		{
			Write_Para_Data(N_1[seconds%10]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[seconds/10]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//������0.5���Ƶ����˸
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

			if(Set_Time)				//Сʱ��0.5���Ƶ����˸
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

void Display3(void)		//��������
{
	if(Set0==0)			//�ж��Ƿ�Ϊ����ʱ���Ƿ�
		{
			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[6]);
			Delay(2);
			Write_Bit_Data(0xff);

			Write_Para_Data(N_1[0]);
			Write_Bit_Data(Digital_Bit[5]);
			Delay(2);
			Write_Bit_Data(0xff);

			if(Set_Time)				//ͬ���溯��
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

			if(Set_Time)				//ͬ���溯��
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

void Display_YMD(void)		//���������� ��ʾ
{

		LCD_Setaddress(1,1);

		LCD_write_dat(0X30+(2));
		LCD_write_dat(0X30+(0));
		LCD_write_dat(0X30+((Years%100)/10));
		LCD_write_dat(0X30+((Years%10)));
		LCD_Print("��  ");

		LCD_write_dat(0X30+(Months/10));
		LCD_write_dat(0X30+(Months%10));
		LCD_Print("��");

		LCD_write_dat(0X30+(Days/10));
		LCD_write_dat(0X30+(Days%10));
		LCD_Print("��");

}

Uint8 CaculateWeekDay(Uint16 y,Uint8 m, Uint8 d)		//���㵱ǰΪ���ڼ�
																										//ʹ�û�ķ����ɭ���㹫ʽ
																										//�ο���http://blog.csdn.net/ycrao/article/details/3825
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

void Display_Weekday(void)		//��ʾ��ǰΪ���ڼ�
{
switch(CaculateWeekDay(Years,Months,Days))
		{
			case 1:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  һ");
				break;
			}
			case 2:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			case 3:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			case 4:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			case 5:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			case 6:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			case 7:
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
			default:		//��ʵûɶ�ã�������һ����㲻������
			{
				LCD_Setaddress(2,2);
				LCD_Print("��  ��  ��");
				break;
			}
		}
}
void Delay(Uint8 x)		//�ӳ���ʱ��������
{
	Uint8 i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
	 _nop_();
}

void Write_Para_Data(unsigned char dat)		//д��ѡ����
{
	 Uint8 x;
	 Select_para_Rck=0;
	 for(x=0;x<8;x++)
	 {
	   Select_para_Sck=0;
     Select_para_Sid=(dat<<x)&0x80;		//д���ݺ�λ����Ĵ���Ȼ������������
     Select_para_Sck=1;
	 }
	 Select_para_Rck=1;
}
void Write_Bit_Data(unsigned char dat)		//дλѡ����
{
	 Uint8 x;
	 Select_bit_Rck=0;
	 for(x=0;x<8;x++)
	 {
	   Select_bit_Sck=0;
     Select_bit_Sid=(dat<<x)&0x80;	  //д���ݺ�λ����Ĵ���Ȼ������������
     Select_bit_Sck=1;
	 }
	 Select_bit_Rck=1;
}

void Timer_Init(void)		//�жϳ�ʼ��
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

void Time0(void) interrupt 1 					//��ʱ��0����
{
	TH0=(65536-45872)/256;	   				//��װ��ֵ
	TL0=(65536-45872)%256;
	Time0_bit++;
	if((Time0_bit%10)==0)					//ÿ���10��Time0_bitȡ��һ��
		Set_Time=~Set_Time;	  				//0.5����˸һ��

	if(Time0_bit==20)						//����Ϊʱ�����ݴ���
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

void Time1(void) interrupt 3  			//��ʱ��1����
{
	TH1=(65536-45872)/256;			//��װ��ֵ
	TL1=(65536-45872)%256;

	Seconds_0++;
	if(Seconds_0==2)				//����Ϊ������ݴ���
		{
			Seconds_0=0;
			Seconds_1++;	 		//Seconds_1ÿ��1��Ϊ100ms��
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


Uint8 Day_per_Month(void)		//�Ҿ�������ÿ�����ж����������
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

void LCD_sendbyte(Uint8 byte)		//���ֽ�����
{
   Uint8 i;
   for(i=0;i<8;i++)
    {
   LCD_SCLK=0;               //����ʱ����
   _nop_();
   LCD_SID=(bit)(byte&0x80);    //�������λ����
   LCD_SCLK=1;               //�����ط�������
   byte=byte<<1;                  //����һλ
 }
}

void LCD_write_com(Uint8 com)		//д����
{
   LCD_sendbyte(0xf8);       		//11111,RW(0),RS(0),0
   LCD_sendbyte(0xf0&com);       //ȡ����λ�����ݷ����δ��ͣ�
                                 //ÿ���ֽڵ����ݱ����������ֽ�
																//����λ���ڵ�һ���ֽڵĸ���λ
   LCD_sendbyte(0xf0&(com<<4));        //����λ���ڵڶ����ֽڵĸ���λ
  Delay(10);
}

void LCD_write_dat(Uint8 dat)		//д����
{
   LCD_sendbyte(0xfa);        //11111,RW(0),RS(1),0
   LCD_sendbyte(0xf0&dat);       //ȡ����λ�����ݷ����δ��ͣ�
                                 //ÿ���ֽڵ����ݱ����������ֽ�
																//����λ���ڵ�һ���ֽڵĸ���λ
   LCD_sendbyte(0xf0&(dat<<4));        //����λ���ڵڶ����ֽ�
	_nop_();
}

void LCD_init(void)		//��ʼ����
{
 LCD_write_com(0x30);             //����ָ�
 LCD_write_com(0x0c);       //����ʾ�����α꣬������
 LCD_write_com(0x01);       //����
 Delay(5);
 LCD_write_com(0x02);       //��DDRAMλַ
 LCD_write_com(0x06);       //������ƣ���ʾ����
}

void LCD_Print(Uint8 *s)		//д�ַ���
{
    while(*s!='\0')
    {
       LCD_write_dat(*s);
       s++;
    }
}

void LCD_Setaddress(Uint8 x,Uint8 y)		//ָ��λ��д�ַ���
{              //��ַ�ӵ�1�е�1�п�ʼ
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

void LCD_Putstring( Uint8 x, Uint8 y, Uint8 *pData )		//ָ��λ���� �ӣ�1��1����ʼŶ����
{
 LCD_Setaddress(x,y);
 while( *pData != '\0' )
 {
   LCD_write_dat( *pData++ );
 }
}

void Delay_10us(void)		//�ӳ�10us
{
    Uint8 i;
		i = 2;
		while (--i);
}

void DHT11_COM(void)		//DHT11������
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

void Display_TRH(void)		//��ʾ��ʪ��
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
