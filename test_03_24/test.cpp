#include <iostream>
#include <conio.h>
using namespace std;
#include <graphics.h>
#include <vector>
#include <math.h>

class Point
{
public:
	double getR()
	{
		return 540000 / (1800 + m_Z);
	}
	double getR(double z)
	{
		return 300*(900-z)/900;
	}
	double m_X;
	double m_Y;
	double m_Z;
};

class Line
{
public:
	Line(double bx, double cx, double by, double cy, double bz, double ez)
	{
		m_Bx = bx;
		m_By = by;
		m_Cy = cy;
		m_Cx = cx;
		m_Bz = bz;
		m_Ez = ez;
	}
	double m_Bx;
	double m_Cx;

	double m_By;
	double m_Cy;
	
	double m_Bz;
	double m_Ez;
	void drawLine()
	{
		double d = (m_Ez - m_Bz) / 100;
		for (double i = m_Bz; i < m_Ez; i+=d)
		{
			fillcircle(m_Bx+(i-m_Bz)*m_Cx, m_By+(i-m_Bz)*m_Cy, Point().getR(i));
		}
	}
};


int main()
{
	initgraph(600,600);
	setbkcolor(BLACK);
	setlinecolor(GREEN);
	setfillcolor(YELLOW);
	BeginBatchDraw();
	cleardevice();
	Line l(200, 2, 200, 2, 950, 1000);
	vector<Line>lines;
	lines.push_back(l);
	int i = 0;
	while (true)
	{
		cleardevice();
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a')
			{
				lines[i].m_Bx -= 3;
			}
			if(ch=='d')
			{
				lines[i].m_Bx += 3;
			}
			if (ch == 'w')
			{
				lines[i].m_By -= 3;
			}
			if (ch == 's')
			{
				lines[i].m_By += 3;
			}


			if (ch == '4')
			{
				lines[i].m_Cx-=0.05;
			}
			if (ch == '6')
			{
				lines[i].m_Cx+= 0.05;
			}
			if (ch == '8')
			{
				lines[i].m_Cy-= 0.05;
			}
			if (ch == '2')
			{
				lines[i].m_Cy+= 0.05;
			}

			if (ch == '7')
			{
				lines[i].m_Bz--;
			}
			if (ch == '9')
			{
				lines[i].m_Bz++;
			}

			if (ch == '1')
			{
				lines[i].m_Ez--;
			}
			if (ch == '3')
			{
				lines[i].m_Ez++;
			}

			if (ch == 'i')
			{
				lines[i].m_Bz++;
				lines[i].m_Ez++;
			}

			if (ch == 'k')
			{
				lines[i].m_Bz--;
				lines[i].m_Ez--;
			}

			if (ch == '\b')
			{
				for (vector<Line>::iterator it = lines.begin(); it != lines.end(); i++)
				{
					if (it - lines.begin() == i)
					{
						lines.erase(it);
						i = 0;
						break;
					}
				}
			}
			if (ch == '.')
			{
				lines.push_back(l);
			}
			if (ch == '+')
			{
				i++;
				if (i == lines.size())
					i = 0;
			}
			if (ch == '-')
			{
				i--;
				if (i == -1)
					i = lines.size() - 1;
			}
		}
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].drawLine();
		}
		FlushBatchDraw();
	}



	system("pause");
	return 0;
}