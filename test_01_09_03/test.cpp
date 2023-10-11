#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#define PI 3.14159

//Ðý×ªÉß´í¾õ

void drawarc(int x, int y, int R, int b, int e)
{
	solidpie(x - R, y - R, x + R, y + R,b*2*PI/360, e * 2 * PI / 360);
}

void drawrainbowcircle(int x, int y, int R)
{
	int color;
	int step = R / 5;
	color = rand() % 180;

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 20; i++)
		{

			setfillcolor(RGB(255, 255, 255));
			setlinecolor(RGB(255, 255, 255));
			drawarc(x, y, R, j * 9 + i * 18 + 0, j * 9 + i * 18 + 3);


			setfillcolor(HSVtoRGB(color, 1, 1));
			setlinecolor(HSVtoRGB(color, 1, 1));
			drawarc(x, y, R, j * 9 + i * 18 + 3, j * 9 + i * 18 + 9);

			setfillcolor(RGB(0, 0, 0));
			setlinecolor(RGB(0, 0, 0));
			drawarc(x, y, R, j * 9 + i * 18 + 9, j * 9 + i * 18 + 12);

			setfillcolor(HSVtoRGB(color + 180, 1, 1));
			setlinecolor(HSVtoRGB(color + 180, 1, 1));
			drawarc(x, y, R, j * 9 + i * 18 + 12, j * 9 + i * 18 + 18);
		}
		R -= step;
	}

	
	
}

int main()
{
	int R = 150;
	srand((unsigned int)time(NULL));
	initgraph(1200, 800);
	setbkcolor(RGB(127, 127, 127));
	again:
	cleardevice();
	BeginBatchDraw();
	for (int x = R; x < 1200; x += (2 * R))
		for (int y = R; y < 800; y += (2 * R))
		{
			drawrainbowcircle(x, y, R);
		}
	FlushBatchDraw();

	system("pause");
	goto again;
	return 0;
}