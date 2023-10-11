#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
int main()
{
	int height = 500;
	int width = 500;
	initgraph(height, width);
	int interval = 10;
	float counttime = 0;
	setfillcolor(GREEN);
	setlinecolor(BLACK);
	while (1)
	{
		cleardevice();
		BeginBatchDraw();
		for (int y = interval / 2; y < 500; y += interval)
		{
			for (int x = interval / 2; x < 500; x += interval)
			{
				counttime += 0.186048;
				fillcircle(x, y, 0.5 * (sin(counttime) + 1) * 15+1);
			}
			counttime -= 49 * 0.186048;
		}
		counttime -= 49 * 0.186048;
		FlushBatchDraw();
		Sleep(100);
	}
	return 0;
}