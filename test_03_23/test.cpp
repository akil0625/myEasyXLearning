#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include <conio.h>
#include <graphics.h>

vector<vector<int>>board;
vector<pair<int, int>>points;
vector<bool>pointflags;

MOUSEMSG m;

#define RE  32

void show();

vector<int>tmp(RE, 0);
vector<vector<int>>tmp2(RE, tmp);//¼ÇÂ¼ÊÇ·ñ×ß¹ý

pair<int, int>bpoint(0, 0);

void setfilllinecolor(COLORREF color)
{
	setlinecolor(color);
	setfillcolor(color);
}

int iszero()
{
	int num = 0;
	for (vector<vector<int>>::iterator ity = board.begin(); ity != board.end(); ity++)
	{
		for (vector<int>::iterator itx = ity->begin(); itx != ity->end(); itx++)
		{
			if (*itx == 0)
				num++;
		}
	}
	return num;
}

bool have(pair<int,int> p)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (p.first == points[i].first&&p.second==points[i].second)
			return true;
	}
	return false;
}

bool have(pair<int, int> p,int flag)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (p.first == points[i].first && p.second == points[i].second&&flag)
		{
			pointflags[i] = true;
			return true;
		}
	}
	return false;
}

bool pointstrue()
{
	for (int i = 0; i < pointflags.size(); i++)
	{
		if (pointflags[i]==false)
			return false;
	}
	return true;
}

void pointsclear()
{
	for (int i = 0; i < pointflags.size(); i++)
	{
		pointflags[i] = false;
	}
}

bool neibor(int j,int i)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i] == pair<int, int>(j, i-1))
			return true;
		if (points[i] == pair<int, int>(j, i+1))
			return true;
		if (points[i] == pair<int, int>(j-1, i))
			return true;
		if (points[i] == pair<int, int>(j+1, i))
			return true;
		if (points[i] == pair<int, int>(j-1, i-1))
			return true;
		if (points[i] == pair<int, int>(j+1, i-1))
			return true;
		if (points[i] == pair<int, int>(j+1, i+1))
			return true;
		if (points[i] == pair<int, int>(j-1, i+1))
			return true;
	}
	return false;
}

void init()
{
	srand((unsigned int)time(NULL));
	vector<int>tmp(RE, 0);
	vector<vector<int>>tmp2(RE, tmp);
	board = tmp2;
	int num = RE*RE * 0.3;
	while (num>0)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (0 == rand()%(RE*RE)&&!have(pair<int, int>(j, i))&&!neibor(j,i))
				{
					points.push_back(pair<int, int>(j, i));
					pointflags.push_back(false);
					num--;
				}
			}
		}
	}
	board[RE-1][0] = 2;
	points.push_back(pair<int, int>(0, RE - 1));
	pointflags.push_back(false);

	board[(RE - 1)/2][0] = 2;
	points.push_back(pair<int, int>(0, (RE - 1)/2));
	pointflags.push_back(false);

	board[0][RE-1] = 2;
	points.push_back(pair<int, int>(RE-1,0));
	pointflags.push_back(false);

	board[0][(RE - 1)/2] = 2;
	points.push_back(pair<int, int>((RE - 1)/2, 0));
	pointflags.push_back(false);

	board[(RE - 1)/2][RE - 1] = 2;
	points.push_back(pair<int, int>(RE - 1, (RE - 1)/2));
	pointflags.push_back(bool(false));

	board[RE - 1][(RE - 1)/2] = 2;
	points.push_back(pair<int, int>((RE - 1)/2, RE - 1));
	pointflags.push_back(bool(false));


	board[0][0] = 2;
	board[RE - 1][RE - 1] = 2;
	points.push_back(pair<int, int>(RE-1, RE-1));
	pointflags.push_back(bool(false));
	initgraph(800,600);
	BeginBatchDraw();
	setbkcolor(DARKGRAY);
	setlinecolor(WHITE);
	cleardevice();
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

bool check(pair<int,int>a,pair<int,int>b)
{
	have(a,true);
	tmp2[a.second][a.first] = 1;
	setfillcolor(RED);
	fillrectangle(100 + a.first * (600/ RE), a.second * (600 / RE), 100+(600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
	FlushBatchDraw();
	vector<int>ret = { 0,1,2,3 };
	int i = 0;
	random_shuffle(ret.begin(), ret.end());
	if (b == pair<int, int>(a.first, a.second))
		return true;
	while (true)
	{
		if(i<4)
		switch (ret[i])
		{
		case 0:
			if (a.first != 0 && tmp2[a.second][a.first - 1] != 1 && board[a.second][a.first - 1] != 1)//Ì½Ñ°×ó±ß
			{
				setfillcolor(YELLOW);
				fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
				FlushBatchDraw();
				if (check(pair<int, int>(a.first - 1, a.second), b))
				{
					setfillcolor(WHITE);
					fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
					FlushBatchDraw();
					return true;
				}
					
			}
			break;
		case 1:
			if (a.first != RE - 1 && tmp2[a.second][a.first + 1] != 1 && board[a.second][a.first + 1] != 1)//Ì½Ñ°ÓÒ±ß
			{
				setfillcolor(YELLOW);
				fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
				FlushBatchDraw();
				if (check(pair<int, int>(a.first + 1, a.second), b))
				{
					setfillcolor(WHITE);
					fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
					FlushBatchDraw();
					return true;
				}
			}
			break;
		case 2:
			if (a.second != 0 && tmp2[a.second - 1][a.first] != 1 && board[a.second - 1][a.first] != 1)//Ì½Ñ°ÉÏ±ß
			{
				setfillcolor(YELLOW);
				fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
				FlushBatchDraw();
				if (check(pair<int, int>(a.first, a.second - 1), b))
				{
					setfillcolor(WHITE);
					fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
					FlushBatchDraw();
					return true;
				}
			}
			break;
		case 3:
			if (a.second != RE - 1 && tmp2[a.second + 1][a.first] != 1 && board[a.second + 1][a.first] != 1)//Ì½Ñ°ÏÂ±ß
			{
				setfillcolor(YELLOW);
				fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
				FlushBatchDraw();
				if (check(pair<int, int>(a.first, a.second + 1), b))
				{
					setfillcolor(WHITE);
					fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
					FlushBatchDraw();
					return true;
				}
			}
			break;
		default:
			break;
		}
		else
		{
			//tmp2[a.second][a.first] = 1;
			setfillcolor(WHITE);
			fillrectangle(100 + a.first * (600 / RE), a.second * (600 / RE), 100 + (600 / RE) + a.first * (600 / RE), (600 / RE) + a.second * (600 / RE));
			FlushBatchDraw();
			return false;
		}
		i++;
	}
}

void settwotozero()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == 2)
				board[i][j] = 0;
		}
	}
}

bool checkall()
{
	//settwotozero();
	for (int i = 0; i < points.size(); i++)
	{
		int ret = rand() % points.size();
		pair<int,int> tmp = points[ret];
		points[ret] = bpoint;
		bpoint = tmp;
		setzero();
		if (pointstrue())
			return true;
		if (!check(bpoint, points[i]))
			return false;
	}
	return true;
}

bool fourblock(int i,int j)
{
	if (i > 0 && j > 0)
	{
		if (board[i-1][j] == 1 && board[i][j-1] == 1 && board[i-1][j-1] == 1)
			return true;
	}
	if (i < RE-1 && j <RE-1)
	{
		if (board[i + 1][j] == 1 && board[i][j + 1] == 1 && board[i + 1][j + 1] == 1)
			return true;
	}
	if (i > 0 && j < RE - 1)
	{
		if (board[i - 1][j] == 1 && board[i][j + 1] == 1 && board[i - 1][j + 1] == 1)
			return true;
	}
	if (i < RE - 1 && j > 0)
	{
		if (board[i + 1][j] == 1 && board[i][j - 1] == 1 && board[i + 1][j - 1] == 1)
			return true;
	}
	return false;
}

bool streat(int i,int j)
{
	//if(have(pair<int,int>(j,i)))
	if (i == 0 || j == 0 || i == RE - 1 || j == RE - 1)
	{
		for (int i = 0; i < pointflags.size(); i++)
		{
			pointflags[i] = true;
		}
		return true;
	}
	if (board[i-1][j] == 1)
		return true;
	if (board[i+1][j] == 1)
		return true;
	if (board[i][j-1] == 1)
		return true;
	if (board[i][j+1] == 1)
		return true;
	return false;
}

void update()
{
	int num = iszero();
	if (num)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (0 == rand() % num&&board[i][j]==0&&!(i==0&&j==0)&&!have(pair<int, int>(j, i)))
				{
					/*if (fourblock(i,j))
					{
						board[i][j] = 2;
						continue;
					}*/
					pointsclear();
					/*if (!streat(i, j) || (i == 1 && j == 0) || (i == 0 && j == 1) || (i == RE - 2 && j == 0) || (i == 0 && j == RE - 2) || (i == RE - 1 && j == 1) || (j == RE - 1 && i == 1) || (i == RE - 2 && j == RE - 1) || (i == RE - 1 && j == RE - 2))
					{
						continue;
					}*/

					board[i][j] = 1;
					show();
					if (!checkall())
					{
						board[i][j] = 2;
					}
				}
			}
		}
	}
	else
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				int i = m.y / (600 / RE);
				int j = (m.x-100) / (600 / RE);
				if (i >= 0 && i < RE && j >= 0 && j < RE)
					board[i][j] = 2;
			}
			if (m.uMsg == WM_RBUTTONDOWN)
			{
				int i = m.y / (600 / RE);
				int j = (m.x - 100) / (600 / RE);
				if (i >= 0 && i < RE && j >= 0 && j < RE&&!have(pair<int,int>(j,i)))
				{
					board[i][j] = 2;
					points.push_back(pair<int, int>(j, i));
					pointflags.push_back(false);
				}
			}
		}
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a')
			{
				settwotozero();
				for (int i = 0; i < points.size(); i++)
				{
					board[points[i].second][points[i].first] = 2;
				}
				board[0][0] = 2;
			}
		}
	}
}


void show()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == 2||board[i][j]==0)//Â·
			{
				setfillcolor(WHITE);
				fillrectangle(100 + j * (600 / RE), i * (600 / RE), 100+(600 / RE) + j * (600 / RE), (600 / RE) + i * (600 / RE));
			}
		}
	}
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == 1)//Ç½
			{
				setfillcolor(GREEN);
				fillrectangle(100 + j * (600 / RE), i * (600 / RE), 100 + (600 / RE) + j * (600 / RE), (600 / RE) + i * (600 / RE));
			}
		}
	}
	//for (int i = 0; i < board.size(); i++)
	//{
	//	for (int j = 0; j < board[i].size(); j++)
	//	{
	//		if (board[i][j] == 2)//Â·
	//		{
	//			setfillcolor(BLUE);
	//			fillrectangle(100 + j * (600 / RE), i * (600 / RE), 100 + (600 / RE) + j * (600 / RE), (600 / RE) + i * (600 / RE));
	//		}
	//	}
	//}
	FlushBatchDraw();
}


int main()
{
	init();
	
	while (true)
	{
		show();
		update();
	}
	system("pause");
	return 0;
}