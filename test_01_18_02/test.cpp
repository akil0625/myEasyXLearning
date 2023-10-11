#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <ctime>

#define BALLNUM 50

/*
BLUE ---- 1
GREEN --- 2
RED  ---- 3
PINK ---- 4
BLUE ---- 5
BLACK			0
BLUE			0xAA0000
GREEN			0x00AA00
CYAN			0xAAAA00
RED				0x0000AA
MAGENTA			0xAA00AA
BROWN			0x0055AA
LIGHTGRAY		0xAAAAAA
DARKGRAY		0x555555
LIGHTBLUE		0xFF5555
LIGHTGREEN		0x55FF55
LIGHTCYAN		0xFFFF55
LIGHTRED		0x5555FF
LIGHTMAGENTA	0xFF55FF
YELLOW			0x55FFFF
WHITE			0xFFFFFF
*/

typedef struct ball
{
	float R;
	float x;
	float y;
	float vx;
	float vy;
	int collor;
}nall;

int width = 800;
int height = 800;
ball balls[BALLNUM];

int randBetween(int l, int r)
{
	return rand() % (r - l+1) + l;
}

int issame(float l, float r)
{
	if ((l > 0 && r > 0) || (l == 0 && r == 0) || (l < 0 && r < 0))
		return 1;
	return 0;
}

//int realVal(int a)
//{
//	if (a >= 0)
//		return a;
//	return -a;
//}

void setfilllinecolor(int cl)
{
	setlinecolor(cl);
	setfillcolor(cl);
}

void startup()
{
	initgraph(width, height);

	setbkcolor(YELLOW);
	setfilllinecolor(GREEN);
	cleardevice();

	for (int i = 0; i < BALLNUM; i++)
	{
		balls[i].R = randBetween(10, 30);
		balls[i].x = randBetween(0 + balls[i].R, 800 - balls[i].R);
		balls[i].y = randBetween(0 + balls[i].R, 800 - balls[i].R);
		balls[i].vx = randBetween(-10, 10);
		balls[i].vy = randBetween(-10, 10);
		balls[i].collor = randBetween(1, 5);
	}
}

void update()
{
	for (int i = 0; i < BALLNUM; i++)
	{
		balls[i].x += balls[i].vx;
		balls[i].y += balls[i].vy;
	}
	for (int i = 0; i < BALLNUM; i++)
	{
		if (balls[i].x - balls[i].R <= 0 && balls[i].vx < 0)
		{
			balls[i].vx = -balls[i].vx;
		}
		if (balls[i].y - balls[i].R <= 0 && balls[i].vy < 0)
		{
			balls[i].vy = -balls[i].vy;
		}
		if (balls[i].x + balls[i].R >= width && balls[i].vx > 0)
		{
			balls[i].vx = -balls[i].vx;
		}
		if (balls[i].y + balls[i].R >= height && balls[i].vy > 0)
		{
			balls[i].vy = -balls[i].vy;
		}
	}
	float tmpv = 0;
	for (int i = 0; i < BALLNUM - 1; i++)
		for (int j = i + 1; j < BALLNUM; j++)
		{
			if (pow(balls[j].x - balls[i].x, 2) + pow(balls[j].y - balls[i].y, 2) <= pow(balls[i].R + balls[j].R, 2)
				&&((issame(balls[j].vx,balls[i].x- balls[j].x)&& issame(balls[i].vx, balls[j].x - balls[i].x))
				|| (issame(balls[j].vy, balls[i].y - balls[j].y) && issame(balls[i].vy, balls[j].y - balls[i].y))))
			{
				//balls[i].vx = balls[i].vy = balls[j].vx = balls[j].vy = 0;
				tmpv = balls[i].vx;
				balls[i].vx = 0;
				balls[j].vx -= tmpv;
				balls[i].vx = (2 * balls[j].R / (balls[j].R + balls[i].R)) * balls[j].vx + tmpv;
				balls[j].vx = ((balls[j].R - balls[i].R) / (balls[j].R + balls[i].R)) * balls[j].vx + tmpv;

				tmpv = balls[i].vy;
				balls[i].vy = 0;
				balls[j].vy -= tmpv;
				balls[i].vy = (2 * balls[j].R / (balls[j].R + balls[i].R)) * balls[j].vy + tmpv;
				balls[j].vy = ((balls[j].R - balls[i].R) / (balls[j].R + balls[i].R)) * balls[j].vy + tmpv;
			}
		}

}

void show()
{
	cleardevice();
	BeginBatchDraw();
	for (int i = 0; i < BALLNUM; i++)
	{
		switch (balls[i].collor)
		{
		case 1:
			setfilllinecolor(BLUE);
			break;
		case 2:
			setfilllinecolor(GREEN);
			break;
		case 3:
			setfilllinecolor(RED);
			break;
		case 4:
			setfilllinecolor(RGB(255,192,203));
			break;
		case 5:
			setfilllinecolor(BROWN);
			break;
		default:
			setfilllinecolor(YELLOW);
			break;
		}
		fillcircle(balls[i].x, balls[i].y, balls[i].R);
	}
	FlushBatchDraw();
}

int main()
{
	srand((unsigned int)time(NULL));
	startup();
	while (1)
	{
		update();
		show();
		Sleep(1);
	}
	return 0;
}