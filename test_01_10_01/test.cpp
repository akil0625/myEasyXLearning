#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")//引用库文件
using namespace std;
#include "net.h"

#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int width = 700;
int height = 700;
int step = width / 8;
int R = width / 8 / 2;
char manTable[8][8];
char from[8][8];
int fi = -2;
int fj = -2;
char isfromready;
char to[8][8];
int ti = -2;
int tj = -2;
char istoready;
int movemode;//0 是走  1 是跳走
int flag = 0;

void setfilllinecolor(int r, int g, int b)
{
	setlinecolor(RGB(r, g, b));
	setfillcolor(RGB(r, g, b));
}



void cleartrip()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			from[i][j] = '0';
			to[i][j] = '0';
		}
	ti = tj = fi = fj = -2;
	isfromready = 0;
	istoready = 0;
}

void clearfrom()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			from[i][j] = '0';
		}
	fi = fj = -2;
	isfromready = 0;
}

void clearto()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			to[i][j] = '0';
		}
	ti = tj = -2;
	istoready = 0;
}

void takestep()
{
	clearfrom();
	from[ti][tj] = '1';
	fi = ti;
	fj = tj;
	isfromready = 1;
	clearto();
}

int realval(int val)
{
	if (val > 0)
		return val;
	return -val;
}

void showBoard()
{
	setfilllinecolor(0, 0, 0);
	for (int x = step; x < width; x += step)
		for (int y = step; y < height; y += step)
		{
			if ((x + y) % (step * 2) == step)
				fillrectangle(x - step, y - step, x, y);
		}
}

void showMan()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			setfilllinecolor(255, 228, 205);
			if (manTable[i][j] == '#' || manTable[i][j] == '*')
				fillcircle(R + j * step, R + i * step, R);
			if (manTable[i][j] == '#')
			{
				setfilllinecolor(255, 0, 0);
				fillcircle(R + j * step, R + i * step, 10);
			}
			if (manTable[i][j] == '*')
			{
				setfilllinecolor(0, 0, 255);
				fillcircle(R + j * step, R + i * step, 10);
			}
		}
	}
}

void showfrom()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			setfilllinecolor(0, 0, 255);
			if (from[i][j] == '1')
				circle(R + j * step, R + i * step, R);
		}
	}
}

void showto()
{
	int x1 = 0;
	int y1 = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			x1 = R + j * step;
			y1 = R + i * step;
			setfilllinecolor(67, 142, 219);
			if (to[i][j] == '1')
				rectangle(x1 - R, y1 - R, x1 + R, y1 + R);
		}
	}
}

void startup()
{
	cout << "IP:";
	cin >> objIP;
	initgraph(width, height);
	setbkcolor(RGB(172, 172, 172));
	cleardevice();
	//putTable
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 1 && i < 3)
				manTable[i][j] = '*';
			else if ((i + j) % 2 == 1 && i > 4)
				manTable[i][j] = '#';
			else if ((i + j) % 2 == 1)
				manTable[i][j] = '1';
			else
				manTable[i][j] = '0';
		}
	cleartrip();
	while (!initnet());
}

void show()
{
	BeginBatchDraw();
	cleardevice();
	showBoard();
	showMan();
	showfrom();
	showto();
	FlushBatchDraw();
}

void nshow()
{
	BeginBatchDraw();
	cleardevice();
	showBoard();
	showMan();
	showfrom();
	showto();
}

int issame(int a, int b)
{
	return (a < 0 && b < 0) || (a > 0 && b > 0) || (a == 0 && b == 0);
}

void move()
{
	from[fi][fj] = '0';
	to[ti][tj] = '0';
	char tmp = manTable[fi][fj];
	manTable[fi][fj] = '1';
	int fx = R + fj * step;
	int fy = R + fi * step;
	int tx = R + tj * step;
	int ty = R + ti * step;
	int x = fx;
	int y = fy;
	int vx = (tx - fx) / 11;
	int vy = (ty - fy) / 11;
	while (!issame(x - tx, x - fx))
	{
		x += vx;
		y += vy;
		nshow();
		setfilllinecolor(255, 228, 205);
		fillcircle(x, y, R);
		if (tmp == '#')
			setfilllinecolor(255, 0, 0);
		if (tmp == '*')
			setfilllinecolor(0, 0, 255);
		fillcircle(x, y, 10);
		FlushBatchDraw();
		Sleep(1);
	}
	manTable[ti][tj] = tmp;
	if (movemode)
	{
		manTable[(fi + ti) / 2][(fj + tj) / 2] = '1';
		takestep();
		istoready = 0;
	}
	else
	{
		flag = 1;
		cleartrip();
	}
}
int iscontinue()
{
	int x1 = 0;
	int y1 = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			x1 = R + j * step;
			y1 = R + i * step;
			if (manTable[i][j] == '1' && realval(i - fi) == 2 && realval(fj - j) == 2 && manTable[(fi + i) / 2][(fj + j) / 2] == '*')
				return 1;
		}
	return 0;
}

void sendmove()
{
	buffs[0] = 7 - fi + 48;
	buffs[1] = 7 - fj + 48;
	buffs[2] = 7 - ti + 48;
	buffs[3] = 7 - tj + 48;
	send(sockClient, buffs, sizeof(char) * 5, 0);
}

void update()
{
	MOUSEMSG m;
	int x1 = 0;
	int y1 = 0;
	while (1)
	{
		if (flag)
			break;
		m = GetMouseMsg();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				x1 = R + j * step;
				y1 = R + i * step;
				if (pow((m.x - x1), 2) + pow((m.y - y1), 2) < 1914.0625 && (manTable[i][j] == '#'))//光标指向自己的棋子
				{
					nshow();
					setfilllinecolor(0, 255, 0);
					circle(R + j * step, R + i * step, R);
					FlushBatchDraw();
					while (pow((m.x - x1), 2) + pow((m.y - y1), 2) < 1914.0625 && (manTable[i][j] == '#'))//光标指向自己的棋子
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							cleartrip();
							from[i][j] = '1';
							fi = i;
							fj = j;
							isfromready = 1;
						}
					}
				}
				else if (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 1 && realval(fj - j) == 1)//指向相邻的可走方格
				{
					nshow();
					setfilllinecolor(67, 142, 219);
					rectangle(x1 - R, y1 - R, x1 + R, y1 + R);
					FlushBatchDraw();
					while (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 1 && realval(fj - j) == 1)//指向相邻的可走方格
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							if (to[i][j] != '1')
							{
								clearto();
								to[i][j] = '1';
							}
							else
							{
								ti = i;
								tj = j;
								istoready = 1;
								movemode = 0;
							}
						}
						if (istoready)
							break;
					}
				}//指向不相邻的可走方格
				else if (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 2 && realval(fj - j) == 2 && manTable[(fi + i) / 2][(fj + j) / 2] == '*')
				{
					nshow();
					setfilllinecolor(67, 142, 219);
					rectangle(x1 - R, y1 - R, x1 + R, y1 + R);
					FlushBatchDraw();//指向不相邻的可走方格
					while (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 2 && realval(fj - j) == 2 && manTable[(fi + i) / 2][(fj + j) / 2] == '*')
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							if (to[i][j] != '1')
							{
								clearto();
								to[i][j] = '1';
							}
							else
							{
								istoready = 1;
								ti = i;
								tj = j;
								movemode = 1;
							}
						}
						if (istoready)
							break;
					}
				}
				else
				{
					if (m.uMsg == WM_LBUTTONDOWN)
					{
						cleartrip();
						show();
					}
				}
				if (istoready)
					break;
			}
			if (istoready)
				break;
		}
		if (istoready)
			break;
	}
	if (flag)//对方
	{
		while (1)
		{
			recv(sockClient, buff, sizeof(char) * 5, 0);
			if ((int)buff[4] - 48==1)
			{
				flag = 0;
				buff[4] = 0 - 48;
				cleartrip();
				break;
			}
			fi = (int)buff[0] - 48;
			fj = (int)buff[1] - 48;
			ti = (int)buff[2] - 48;
			tj = (int)buff[3] - 48;
			if (realval(ti - fi) == 2)
				movemode = 1;
			else
				movemode = 0;
			isfromready = 1;
			istoready = 1;
			move();
			show();
			cleartrip();
		}
	}
	else//我方
	{
		buffs[4] = 0 + 48;
		sendmove();
		move();
		show();
		while (iscontinue() && !flag)
		{
			m = GetMouseMsg();
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					x1 = R + j * step;
					y1 = R + i * step;
					if (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 2 && realval(fj - j) == 2 && manTable[(fi + i) / 2][(fj + j) / 2] == '*')
					{
						nshow();
						setfilllinecolor(67, 142, 219);
						rectangle(x1 - R, y1 - R, x1 + R, y1 + R);
						FlushBatchDraw();//指向不相邻的可走方格
						while (realval(m.x - x1) <= R && realval(m.y - y1) <= R && manTable[i][j] == '1' && realval(i - fi) == 2 && realval(fj - j) == 2 && manTable[(fi + i) / 2][(fj + j) / 2] == '*')
						{
							m = GetMouseMsg();
							if (m.uMsg == WM_LBUTTONDOWN)
							{
								if (to[i][j] != '1')
								{
									clearto();
									to[i][j] = '1';
								}
								else
								{
									istoready = 1;
									ti = i;
									tj = j;
									movemode = 1;
								}
							}
							if (istoready)
								break;
						}
					}
					if (istoready)
						break;
				}
				if (istoready)
					break;
			}
			if (istoready)
			{
				buffs[4] = 0 + 48;
				sendmove();
				move();
				show();
			}
		}
		Sleep(30);
		buffs[4] = 1 + 48;
		sendmove();
		cleartrip();
		show();
		flag = 1;
	}
}


int main()
{
	startup();
	while (1)
	{
		show();
		FlushBatchDraw();
		update();
	}
	return 0;
}