#include <graphics.h>
#include <conio.h>
#include <stdio.h>

int main()
{
	int radius1 = 0;
	int radius2 = 200;
	initgraph(800,600);
	while (true)
	{
   		BeginBatchDraw();
		circle(400, 300,radius1+=10);
		circle(400, 300, radius2 += 10);
		EndBatchDraw();
		FlushBatchDraw();
		//1
		if (radius1 > 500)
		{
			radius1 = 0;
		}
		//2
		if (radius2 > 500)
		{
			radius2 = 0;
		}
		Sleep(1);
		cleardevice();
	}
	return 0;
}