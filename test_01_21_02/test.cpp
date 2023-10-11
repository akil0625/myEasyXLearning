#include <iostream>
using namespace std;
#include <conio.h>
#include <graphics.h>
#include <math.h>

//生命游戏出错版 (但挺好看)

#define PERSENTAGE 1

int  width = 800;
int height = 600;

constexpr auto row = 102;
constexpr auto col = 77;

int lifes[row][col];


void startup()
{
	initgraph(width, height);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	setfillcolor(GREEN);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
		{
			if (rand() % 100 < PERSENTAGE)
				lifes[i][j] = 1;
			else
				lifes[i][j] = 0;

		}
}

void update()
{
	int num = 0;
	for (int i = 1; i < col-1; i++)
	{
		for (int j = 1; j < row-1; j++)
		{
			num = 0;
			if (lifes[i-1][j-1] == 1)
				num++;
			if (lifes[i-1][j] == 1)
				num++;
			if (lifes[i-1][j+1] == 1)
				num++;
			if (lifes[i][j-1] == 1)
				num++;
			if (lifes[i][j+1] == 1)
				num++;
			if (lifes[i+1][j-1] == 1)
				num++;
			if (lifes[i+1][j] == 1)
				num++;
			if (lifes[i+1][j+1] == 1)
				num++;
			if (num == 2 || num == 3)
				lifes[i][j] = 1;
			else
				lifes[i][j] = 0;
		}
	}
}

void show()
{
	BeginBatchDraw();
	cleardevice();
	for (int i = 1; i < col - 1; i++)
		for (int j = 1; j < row - 1; j++)
		{
			if (lifes[i][j] == 1)
				fillrectangle((j - 1) * 8, (i - 1) * 8, j * 8, i * 8);
		}
	FlushBatchDraw();
}

int main()
{
	startup();
	while (1)
	{
		update();
		//Sleep(1000);
		show();
	}
	return 0;
}