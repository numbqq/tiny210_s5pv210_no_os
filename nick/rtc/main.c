#include "int.h"
#include "stdio.h"
#include "rtc.h"

void uart_init(void);

int main(void)
{
	int c = 0;

	// 初始化串口
	uart_init();

	// 中断相关初始化
	system_initexception();						

	// 打印菜单
	while(1)
	{
		printf("\r\n###############rtc test##############\r\n");
		printf("[d] Display rtc realtime(hour:min:sec:weekday date/month/year)\r\n");
		printf("[s] Reset rtc realtime(12:0:0:Tuesday 1/1/2012) \r\n");
		printf("Enter your choice:");
		c = getc();
		printf("%c\r\n",c);
		switch(c)
		{
			case 'd':
				// 打印时间
				rtc_realtime_display();
				break;
			case 's':
				// 重置时间
				rtc_settime();
				break;
		}
	}
	return 0;
}
