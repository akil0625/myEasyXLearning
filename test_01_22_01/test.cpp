#include <iostream>
#include <conio.h>
#include <math.h>
#include <graphics.h>
using namespace std;

#define ROW 32
#define COL 32
#define MAXFOODNUM 1

int width = 800;
int height = 600;
int board[ROW][COL];
char wayStatu = 0;
int X = 0;
int Y = 0;
int gameOver = 0;
char snakeLen = 0;


void show();

void setfilllinecolor(int cl)
{
	setfillcolor(cl);
	setlinecolor(cl);
}

int randBetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

int search(int target, char direct = wayStatu, int  x = X, int y = Y)
{
	int i = 0;
	switch (direct)
	{
	case 'w':
		y--;
		if (y == 0)
			y = ROW - 2;
		break;
	case 's':
		y++;
		if (y == ROW - 1)
			y = 1;
		break;
	case 'a':
		x--;
		if (x == 0)
			x = COL - 2;
		break;
	case 'd':
		x++;
		if (x == COL - 1)
			x = 1;
		break;
	case 'A':
		if (board[y - 1][x] == target || board[y + 1][x] == target || board[y][x - 1] == target || board[y][x + 1] == target)
			i++;
		break;
	default:
		break;
	}
	if (board[y][x] == target)
		i++;
	return i;
}

void putSnake()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = 0;
		}
	x = randBetween(1, COL-2);
	y = randBetween(1, ROW-2);
	X = x;
	Y = y;
	board[y][x] = 1;
	while (!search(1, 'A', x, y) || board[y][x] != 0)
	{
		x = randBetween(1, COL - 2);
		y = randBetween(1, ROW - 2);
	}
	board[y][x] = 2;
	while (!search(2, 'A', x, y) || board[y][x] != 0)
	{
		x = randBetween(1, COL - 2);
		y = randBetween(1, ROW - 2);
	}
	board[y][x] = 3;
	while (!search(3, 'A', x, y) || board[y][x] != 0)
	{
		x = randBetween(1, COL - 2);
		y = randBetween(1, ROW - 2);
	}
	board[y][x] = 4;
	snakeLen = 4;
}

void startup()
{
	srand((unsigned int)time(NULL));
	initgraph(width, height);
	setbkcolor(DARKGRAY);
	setlinecolor(BLACK);
	cleardevice();
	putSnake();
}

void delMax()
{
	int Max = -1;
	int x = 0;
	int y = 0;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] > Max&&board[i][j]!=901)
			{
				y = i;
				x = j;
				Max = board[i][j];
			}
		}
	board[y][x] = 0;
}


void moveSnake()
{
	int eat = 0;
	if (wayStatu != 'w' && wayStatu != 'a' && wayStatu != 's' && wayStatu != 'd')
		return;
	if (!(search(0) || search(1) || search(snakeLen) || search(2) || search(901)))
	{
		gameOver = 1;
		return;
	}
	if (search(2))
		return;
	if (search(901) || search(snakeLen) || search(0))
	{
		if (!search(0))
		{
			eat = 1;
			if(search(901))
			snakeLen++;
		}
		switch (wayStatu)
		{
		case 'w':
			board[Y - 1][X] = 1;
			Y--;
			break;
		case 's':
			board[Y + 1][X] = 1;
			Y++;
			break;
		case 'a':
			board[Y][X - 1] = 1;
			X--;
			break;
		case 'd':
			board[Y][X + 1] = 1;
			X++;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if ((i != Y || j != X) && board[i][j] != 0&& board[i][j]!=901)
				board[i][j]++;
		}
	if (!eat)
		delMax();
	for (int i = 1; i < ROW - 1; i++)
	{
		if (board[i][0])
		{
			board[i][COL - 2] = board[i][0];
			board[i][0] = 0;
		}
		if (board[i][COL - 1])
		{
			board[i][1] = board[i][COL - 1];
			board[i][COL - 1] = 0;
		}
	}
	for (int j = 1; j < COL - 1; j++)
	{
		if (board[0][j])
		{
			board[ROW - 2][j] = board[0][j];
			board[0][j] = 0;
		}
		if (board[ROW - 1][j])
		{
			board[1][j] = board[ROW - 1][j];
			board[ROW - 1][j] = 0;
		}
	}
	if (Y == 0)
		Y = ROW - 2;
	if (X == 0)
		X = COL - 2;
	if (Y == ROW - 1)
		Y = 1;
	if (X == COL - 1)
		X = 1;
	eat = 0;
}

int i = 0;
int j = 0;
void goWithoutInput()
{
	i++;
	if (i == 50)
	{
		i = 0;
		//j++;
		//if (j == 29)
		//{
		//	j = 0;
		//	if (wayStatu == 'w')
		//	{
		//		wayStatu = 'a';
		//		moveSnake();
		//		wayStatu = 's';
		//		moveSnake();
		//	}
		//	else if(wayStatu == 's')
		//	{
		//		wayStatu = 'a';
		//		moveSnake();
		//		wayStatu = 'w';
		//		moveSnake();
		//	}
		//}
		//else
		//{
		//	moveSnake();
		//}
		moveSnake();
	}
}

void goWithInput()
{
	char tmp = 0;
	if (_kbhit())
	{
		tmp = _getch();
		if (tmp == 'w' || tmp == 'a' || tmp == 's' || tmp == 'd')
		{
			if (!search(2, tmp))
				wayStatu = tmp;
		}
		if (tmp == wayStatu || tmp == ' ')
		{
			moveSnake();
			i = 0;
		}
	}
}

void putFood()
{
	int foodNum = 0;
	for (int i = 1; i < ROW - 1; i++)
		for (int j = 1; j < COL - 1; j++)
		{
			if (board[i][j] == 901)
				foodNum++;
		}
	if (foodNum >= MAXFOODNUM)
		return;
	int x = randBetween(1, COL - 2);
	int y = randBetween(1, ROW - 2);
	while (board[y][x])
	{
		x = randBetween(1, COL - 2);
		y = randBetween(1, ROW - 2);
	}
	board[y][x] = 901;
}


void update()
{
	goWithInput();
	goWithoutInput();
	putFood();
	if (gameOver)
	{
		setfilllinecolor(RED);
		setlinestyle(BS_SOLID, 2);
		circle(X * 20+100-10, Y * 20-10, 35);
		FlushBatchDraw();
		while (1);
	}
}

void show()
{
	BeginBatchDraw();
	cleardevice();
	setfillcolor(DARKGRAY);
	fillrectangle(100, 0, 700, 600);
	for (int i = 1; i < ROW-1; i++)
		for (int j = 1; j < COL-1; j++)
		{
			if (board[i][j] == 0)
				setfillcolor(WHITE);
			else if (board[i][j] == 901)
				setfillcolor(BROWN);
			else
				setfillcolor(HSVtoRGB((180+board[i][j]*(360/(COL-2)))%360, 1, 1));
			fillrectangle((j - 1) * 20 + 100, (i - 1) * 20 ,  j * 20 + 100, i * 20);
		}
	FlushBatchDraw();
}

int main()
{
	startup();
	while (1)
	{
		update();
		show();
	}
	return 0;
}