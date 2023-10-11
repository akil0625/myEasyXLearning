#include <iostream>
#include <conio.h>
#include <graphics.h>
using namespace std;

enum
{
	insertway,
	bubbleway,
	choiseway
};

int way = choiseway;

class Data
{
public:
	void operator=(Data d)
	{
		this->val = d.val;
		this->cl = d.cl;
	}
	int val;
	int cl;
};

#define LENOFNUM 1540
Data arr[LENOFNUM];
int width = 1920;
int height = 700;

void setfilllinecolor(int cl)
{
	setfillcolor(cl);
	setlinecolor(cl);
}

void startup()
{
	initgraph(width, height);
	setbkcolor(RGB(87,250,255));
	srand((unsigned int)time(NULL));
	int ret = 0;
	for (int i = 0; i < LENOFNUM; i++)
	{
		arr[i].val = rand() % 700+1;
		ret = arr[i].val / 100;
		switch (ret)
		{
		case 0:
			arr[i].cl = RED;
			break;
		case 1:
			arr[i].cl = RGB(255, 165, 0);
			break;
		case 2:
			arr[i].cl = YELLOW;
			break;
		case 3:
			arr[i].cl = GREEN;
			break;
		case 4:
			arr[i].cl = RGB(0, 0, 255);
			break;
		case 5:
			arr[i].cl = RGB(75, 0, 130);
			break;
		case 6:
			arr[i].cl = RGB(128, 0, 128);
			break;
		default:
			arr[i].cl = RGB(128, 0, 128);
			break;
		}
	}
}

void insert(int in, int k)
{
	Data tmp = arr[in];
	for (int i = in; i > k; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[k] = tmp;
}

int in = 1;
void insertSort()
{
	if (in == LENOFNUM)
		while (1)
		{
			FlushBatchDraw();
		}
	for (int i = 0; i < in;i++)
	{
		if (arr[in].val < arr[i].val)
			insert(in, i);
	}
	in++;
}



int bu = 0;
void bubbleSort()
{
	Data tmp;
	int num = 0;
	for (int i = 0; i < LENOFNUM-bu-1; i++)
	{
		if (arr[i].val > arr[i + 1].val)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			num++;
		}
	}
	if (num == 0)
		while (1)
		{
			FlushBatchDraw();
		}
	bu++;
}

int ch = 0;
void choiseSort()
{
	if (ch == LENOFNUM)
		while (1)
		{
			FlushBatchDraw();
		}
	int min = ch;
	Data tmp;
	for (int i = ch; i < LENOFNUM; i++)
	{
		if (arr[min].val > arr[i].val)
			min = i;
	}
	if (min != ch)
	{
		tmp = arr[min];
		arr[min] = arr[ch];
		arr[ch] = tmp;
	}
	ch++;
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
	for (int i = 0; i < LENOFNUM; i++)
	{
		setfilllinecolor(arr[i].cl);
		line(i, 0.5 * height - arr[i].val*0.5, i, 0.5 * height + arr[i].val*0.5);
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
}