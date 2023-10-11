#include <iostream>
using namespace std;
#include <conio.h>
#include <graphics.h>
#include <math.h>

#define PERSENTAGE 30
#define SLEEPTIME 0

int  width = 800;
int height = 600;

constexpr auto row = 202;
constexpr auto col = 152;

int lifes[row][col];
int board[row][col];


void startup()
{
	initgraph(width, height/*, 1 */ );
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	if (width / (row - 2) <= 3)
		setlinecolor(GREEN);
	setfillcolor(GREEN);
	srand((unsigned int)time(NULL));
	for (int i = 1; i < col - 1; i++)
		for (int j = 1; j < row - 1; j++)
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
	for (int i = 1; i < col - 1; i++)
		for (int j = 1; j < row - 1; j++)
		{
			board[i][j] = 0;
		}
	for (int i = 1; i < col - 1; i++)
	{
		for (int j = 1; j < row - 1; j++)
		{
			num = 0;
			if (lifes[i - 1][j - 1] == 1)
				num++;
			if (lifes[i - 1][j] == 1)
				num++;
			if (lifes[i - 1][j + 1] == 1)
				num++;
			if (lifes[i][j - 1] == 1)
				num++;
			if (lifes[i][j + 1] == 1)
				num++;
			if (lifes[i + 1][j - 1] == 1)
				num++;
			if (lifes[i + 1][j] == 1)
				num++;
			if (lifes[i + 1][j + 1] == 1)
				num++;
			//cout << num << endl;
			if (num == 3)
				board[i][j] = 1;
			else if (num <= 1 || num >= 4)
				board[i][j] = 0;
			else
				board[i][j] = lifes[i][j];
		}
	}
	for (int i = 1; i < col - 1; i++)
		for (int j = 1; j < row - 1; j++)
		{
			lifes[i][j] = board[i][j];
		}
	if (_kbhit())
	{
		_getch();
		for (int i = 1; i < col - 1; i++)
			for (int j = 1; j < row - 1; j++)
			{
				if (rand() % 100 < PERSENTAGE)
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
				fillrectangle((j - 1) * 4, (i - 1) * 4, j * 4, i * 4);
		}
	EndBatchDraw();
	FlushBatchDraw();
}

int main()
{
	startup();
	while (1)
	{
		show();
		update();
		Sleep(SLEEPTIME);
	}
	return 0;
}