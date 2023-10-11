#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159


int main()
{
	initgraph(800, 800);
	setbkcolor(YELLOW);
	cleardevice();
	setlinecolor(GREEN);
	setfillcolor(GREEN);
	int i = 0;
	int r1 = rand() / 360;
	int r2 = rand() / 360;
	int r3 = rand() / 360;
	int r4 = rand() / 360;
	int r5 = rand() / 360;
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		fillcircle(400 + 50 * sin((r1 + i) * PI / 180), 400 + 50 * cos((r1 + i) * PI / 180), 40);
		fillcircle(200 + 50 * cos((r2 + i) * PI / 180), 200 + 50 * sin((r2 + i) * PI / 180), 20);
		fillcircle(200 + 50 * cos((r3 + i) * PI / 180), 600 + 50 * sin((r3 + i) * PI / 180), 30);
		fillcircle(600 + 50 * cos((r4 + i) * PI / 180), 200 + 50 * sin((r4 + i) * PI / 180), 25);
		fillcircle(600 + 50 * sin((r5 + i) * PI / 180), 600 + 50 * cos((r5 + i) * PI / 180), 10);
		i++;
		if (i == 360)
			i = 1;
		FlushBatchDraw();
		for (int i = 0; i < 6000000; i++);
	}

	return 0;
}