/*�ڶ���룿����~
  Good luck~~~
	By Aspirin
	2016��12��14��21:47:28	*/
#include "extern_function.c"

//������
void main(void)
{

	LCD_init();		//��ʼ��LCD12864
	Timer_Init();		//��ʼ����ʱ��
	LCD_Putstring(4,1,a);		//��ӡһ�¡������ա�
	Display_Weekday();		//����һ���ܼ��ʡ��ˢ��
	while(1)									//ѭ��
		{
			//Check_Alarm();		//�������
			KEY_Mode_Set();		//��ⰴ���л�ģʽ
			Mode_Set();		//���ݰ��������ж�ģʽ
		}
}