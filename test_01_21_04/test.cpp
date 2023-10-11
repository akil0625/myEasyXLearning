#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <math.h>

enum
{
insertway,
bubbleway,
choiseway
};

int way = choiseway;
int width = 800;
int height = 600;
#define NUMSLEN 1300
int len = 1;
int arr[NUMSLEN];
int i = 1;
int j = 0;
int k = 0;

void setfilllinecolor(int cl)
{
	setlinecolor(cl);
	setfillcolor(cl);
}

void startup()
{
	initgraph(2000, height);
	setbkcolor(DARKGRAY);
	setfilllinecolor(YELLOW);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < NUMSLEN; i++)
	{
		arr[i] = i/3;
	}
	int tmp = 0;
	int j = 0;
	for (int i = 0; i < NUMSLEN; i++)
	{
		j = rand() % NUMSLEN;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}

void bubbleSort()
{
	int tmp = 0;
	int num = 0;
	for (int i = 0; i < NUMSLEN - j - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			num++;
		}
	}
	if (num == 0)
		while (1);
	j++;
}

void insert(int i, int j)
{
	int tmp = arr[i];
	for (; i > j; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[j] = tmp;
}

void insertSort()
{
	if (i == NUMSLEN)
		while (1);
	for (int j = 0; j < i; j++)
	{
		if (arr[i] < arr[j])
			insert(i, j);
	}
	i++;
}

int findMin()
{
	int j = k;
	for (int i = k; i < NUMSLEN; i++)
	{
		if (arr[j] > arr[i])
			j = i;
	}
	return j;
}

void choiseSort()
{
	if (k == NUMSLEN)
		while (1);
	int tmp;
	int i = findMin();
	if (i != k)
	{
		tmp = arr[i];
		arr[i] = arr[k];
		arr[k] = tmp;
	}
	k++;
}

void update()
{
	switch (way)
	{
	case 0:
		insertSort();
		break;
	case 1:
		bubbleSort();
		break;
	case 2:
		choiseSort();
		break;
	default:
		break;
	}
}

void show()
{
	BeginBatchDraw();
	cleardevice();
	for (int i = 0; i < NUMSLEN; i++)
	{
		fillrectangle(100 + i * len,600- arr[i], 100 + (i + 1) * len, 600);
	}
	//EndBatchDraw();
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