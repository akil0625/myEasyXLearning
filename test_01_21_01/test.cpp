#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;

#define NUMOFPEOPLE 1000
#define PERSENTAGE 50
#define SLEEPTIME 0

time_t tstart, tend;
int width = 800;
int height = 800;
int R = 2;
int contectnum = 0;

int randBetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

void setfilllinecolor(int cl)
{
	setlinecolor(cl);
	setfillcolor(cl);
}

class Person
{
public:
	Person()
	{
		this->m_Isill = 0;
		this->m_X = randBetween(0, width);
		this->m_Y = randBetween(0, height);
		this->m_Vx = randBetween(-10, 10);
		this->m_Vy = randBetween(-10, 10);
	}
	int m_Isill;
	float m_X;
	float m_Y;
	float m_Vx;
	float m_Vy;
};

Person ps[NUMOFPEOPLE];


void startup()
{
	initgraph(width, height,1);
	setbkcolor(DARKGRAY);
	cleardevice();
	setfilllinecolor(BLUE);
	//setfillcolor(BLUE);
	ps[0].m_Isill = 1;
	tstart = clock();
}

void update()
{
	for (int i = 0; i < NUMOFPEOPLE; i++)
	{
		ps[i].m_X += ps[i].m_Vx;
		ps[i].m_Y += ps[i].m_Vy;
	}
	for (int i = 0; i < NUMOFPEOPLE; i++)
	{
		if ((ps[i].m_X - R <= 0 && ps[i].m_Vx < 0) || (ps[i].m_X + R >= width && ps[i].m_Vx > 0))
		{
			ps[i].m_Vx = -ps[i].m_Vx;
		}
		if ((ps[i].m_Y - R <= 0 && ps[i].m_Vy < 0) || (ps[i].m_Y + R >= height && ps[i].m_Vy > 0))
		{
			ps[i].m_Vy = -ps[i].m_Vy;
		}
	}
	for (int i = 0; i < NUMOFPEOPLE - 1; i++)
		for (int j = i + 1; j < NUMOFPEOPLE; j++)
		{
			if (pow(ps[i].m_X - ps[j].m_X,2)+pow(ps[i].m_Y - ps[j].m_Y, 2) <= pow(R+R, 2))
			{
				if (ps[i].m_Isill || ps[j].m_Isill)
				{
					if (rand() % 100 < PERSENTAGE)
					{
						if (ps[i].m_Isill == 0)
						{
							contectnum++;
							printf("%d号被感染了!!!\n", i);
						}
						else if (ps[j].m_Isill == 0)
						{
							contectnum++;
							printf("%d号被感染了!!!\n", j);
						}
						ps[i].m_Isill = 1;
						ps[j].m_Isill = 1;
					}
					else
					{
						if (!ps[i].m_Isill || !ps[j].m_Isill)
						{
							contectnum++;
						}
					}
				}
			}
		}
}
void isEnd()
{
	int num = 0;
	for (int i = 0; i < NUMOFPEOPLE; i++)
	{
		if (ps[i].m_Isill)
			num++;
	}
	if (num == NUMOFPEOPLE)
	{
		tend = clock();
		printf("所有人都被感染了!!!\n");
		//printf("至此花费了%dms", (tend - tstart) / 1000);
		cout << "至此花费了" << (tend - tstart) / 1000 << "s" << endl;
		printf("疫情传播率为百分之%d\n", PERSENTAGE);
		printf("实际传播率为百分之%f", 100*(NUMOFPEOPLE - 1.0) / contectnum);
		system("pause");
	}
		
}
void show()
{
	BeginBatchDraw();
	cleardevice();
	for (int i = 0; i < NUMOFPEOPLE; i++)
	{
		if (ps[i].m_Isill == 1)
			setfilllinecolor(RED);
		else
			setfilllinecolor(BLUE);
		fillcircle(ps[i].m_X, ps[i].m_Y, R);
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
		Sleep(SLEEPTIME);
		show();
		isEnd();
	}
	return 0;
}