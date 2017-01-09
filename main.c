/*第二版半？算啦~
  Good luck~~~
	By Aspirin
	2016年12月14日21:47:28	*/
#include "extern_function.c"

//主程序
void main(void)
{

	LCD_init();		//初始化LCD12864
	Timer_Init();		//初始化定时器
	LCD_Putstring(4,1,a);		//打印一下“萌萌哒”
	Display_Weekday();		//先算一下周几嘛，省得刷新
	while(1)									//循环
		{
			//Check_Alarm();		//检查闹钟
			KEY_Mode_Set();		//检测按键切换模式
			Mode_Set();		//根据按键输入判断模式
		}
}