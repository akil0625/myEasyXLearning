#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include <conio.h>
#include <graphics.h>
#include <queue>

vector<vector<int>>board;
vector<bool>pointflags;
float RE = 23;//RE*RE��С���Թ�

void show();
void check(pair<int, int>a);

string directs;

vector<int>tmp;
vector<vector<int>>tmp2;//��¼�Ƿ��߹�


int i = 0;
double X1 = 6;
double Y1 = 6;
double dis = X1;
double d;//ÿ���ߵľ���
bool yes = false;//�Ƿ�鿴�滭����

queue<pair<int, int>>points;

class Rec
{
public:
	Rec(int x1, int y1, int x2, int y2)
	{
		m_X1 = x1;
		m_Y1 = y1;
		m_X2 = x2;
		m_Y2 = y2;
	}
	int m_X1;
	int m_Y1;
	int m_X2;
	int m_Y2;

};

vector<Rec>Recs;



void setfilllinecolor(COLORREF color)
{
	setlinecolor(color);
	setfillcolor(color);
}


void init()
{
	system("mode con: cols=20 lines=10");
	printf("�������Ѷ�10~100\n");
	while (true)
	{
		cin >> RE;
		if (RE <= 100 && RE >= 10)
			break;
		else
			printf("Are you kiding me?");
	}
	printf("�Ƿ񿴻滭����<y,n>,������Ĭ��Ϊno\n");
	char ans;
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
		yes = true;
	tmp = vector<int>(RE, 0);
	tmp2 = vector<vector<int>>(RE, tmp);
	d = 600 / RE;//ÿ���ߵľ���
	dis = (600 / RE+1)/2;
	X1 = dis;
	Y1 = dis;
	srand((unsigned int)time(NULL));
	vector<int>tmp(RE, 0);
	vector<vector<int>>tmp2(RE, tmp);
	board = tmp2;
	initgraph(601, 601);
	BeginBatchDraw();
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	cleardevice();
	setlinestyle(PS_ENDCAP_SQUARE, 600 / RE-1);
	check(pair<int, int>(0, 0));
}

void setzero()
{
	for (int i = 0; i < tmp2.size(); i++)
	{
		for (int j = 0; j < tmp2[i].size(); j++)
		{
			tmp2[i][j] = 0;
		}
	}
}

void check(pair<int, int>a)//�������̽������ÿ�ι���ʱ����r(���ر�־�Իص���ǵ�)
{
	board[a.second][a.first] = 1;
	vector<int>ret = { 0,1,2,3 };
	int i = 0;
	random_shuffle(ret.begin(), ret.end());
	while (true)
	{
		if (i < 4)
		{
			switch (ret[i])
			{
			case 0:
				if (a.first != 0 &&board[a.second][a.first - 1] != 1)//̽Ѱ���
				{
					directs += 'a';
					check(pair<int, int>(a.first - 1, a.second));
					directs += 'r';
					points.push(a);
				}
				break;
			case 1:
				if (a.first != RE - 1 &&board[a.second][a.first + 1] != 1)//̽Ѱ�ұ�
				{
					directs += 'd';
					check(pair<int, int>(a.first + 1, a.second));
					directs += 'r';
					points.push(a);
				}
				break;
			case 2:
				if (a.second != 0 &&board[a.second - 1][a.first] != 1)//̽Ѱ�ϱ�
				{
					directs += 'w';
					check(pair<int, int>(a.first, a.second - 1));
					directs += 'r';
					points.push(a);
				}
				break;
			case 3:
				if (a.second != RE - 1 &&board[a.second + 1][a.first] != 1)//̽Ѱ�±�
				{
					directs += 's';
					check(pair<int, int>(a.first, a.second + 1));
					directs += 'r';
					points.push(a);
				}
				break;
			default:
				break;
			}
		}
		else
		{
			return;
		}
		i++;
	}
}
void update()
{
	while (i < directs.size())
	{
		switch (directs[i])
		{
		case 'a':
			Recs.push_back(Rec(X1, Y1, X1-d, Y1));
			X1 -= d;
			break;
		case 'd':
			Recs.push_back(Rec(X1, Y1, X1 + d, Y1));
			X1 += d;
			break;
		case 'w':
			Recs.push_back(Rec(X1, Y1, X1, Y1-d));
			Y1 -= d;
			break;
		case 's':
			Recs.push_back(Rec(X1, Y1, X1, Y1+d));
			Y1 += d;
			break;
		case 'r':
			X1 = dis + points.front().first * d;
			Y1 = dis + points.front().second * d;
			points.pop();
			break;
		default:
			break;
		}
		//�⿪ע������ʾ�滭����
		if(yes)
			show();
		i++;
	}
}


void show()
{
	for (int i = 0; i < Recs.size(); i++)
	{
		line(Recs[i].m_X1, Recs[i].m_Y1, Recs[i].m_X2, Recs[i].m_Y2);
	}
	FlushBatchDraw();
	if (i == directs.size())
		Sleep(1000000000);
}


int main()
{
	init();
	while (true)
	{
		show();
		update();
	}
	closegraph();
	return 0;
}