#include<iostream>
using namespace std;
#include<list>
#include<graphics.h>
#include<conio.h>
#include<algorithm>

double randbetween(int l,int r)
{
	return rand() % (r - l + 1) + l+rand()%100/100.0;
}

void setfilllinecolor(COLORREF cl)
{
	setfillcolor(cl);
	setlinecolor(cl);
}

class Ball
{
public:
	Ball(double x, double y, double r, COLORREF color)
	{
		m_X = x;
		m_Y = y;
		m_R = r;
		m_Color = color;
		m_Vx = randbetween(-1, 1)/10;
		m_Vy = randbetween(-1, 1)/10;
	}
	double getds(Ball b)
	{
		return sqrt(pow(m_X - b.m_X, 2) + pow(m_Y - b.m_Y, 2));
	}
	double m_X;
	double m_Y;
	double m_Vx;
	double m_Vy;
	double m_R;
	COLORREF m_Color;
};

#define BALLNUM 20
#define WAIT 1
#define BALLSIZE 15

double width = 600;
double height = 600;
int life = 1000;
MOUSEMSG m;
list<Ball>balls;
Ball ch(width/2,height/2,BALLSIZE,HSVtoRGB(rand()%360, 1, 1));


void startup()
{
	m.x = width / 2;
	m.y = height / 2;
	ch.m_Color = BLACK;
	srand((unsigned int)time(NULL));
	initgraph(width, height);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	for (int i = 0; i < BALLNUM; i++)
	{
		balls.push_front(Ball(randbetween(0,600),randbetween(0,600),randbetween(5,20),HSVtoRGB(rand()%360, 1, 1)));
	}
}

void updatewithinput()
{
	if (MouseHit())
	{
		m = GetMouseMsg();
		double dx = m.x - ch.m_X;
		double dy = m.y - ch.m_Y;
		double ds = sqrt(pow(dx, 2) + pow(dy, 2));
		ch.m_Vx = dx / ds/7.0;
		ch.m_Vy = dy / ds/7.0;
	}
	else
	{
		double dx = m.x - ch.m_X;
		double dy = m.y - ch.m_Y;
		double ds = sqrt(pow(dx, 2) + pow(dy, 2));
		if (ds < 1)
		{
			ch.m_Vx = 0;
			ch.m_Vy = 0;
		}
	}
}

void updatewithoutinput()
{
	for (list<Ball>::iterator it = balls.begin(); it != balls.end(); it++)
	{
		if (ch.getds(*it) < ch.m_R)
		{
			if (it->m_R < ch.m_R)//³Ô
			{
				balls.erase(it);
				ch.m_R += 0.2;
				break;
			}
			else//±»³Ô
			{
				life--;
			}
		}
		it->m_X += it->m_Vx;
		it->m_Y += it->m_Vy;
		if ((it->m_X - it->m_R < 0 && it->m_Vx < 0) || (it->m_X + it->m_R > width && it->m_Vx > 0))
			it->m_Vx = -it->m_Vx;
		if ((it->m_Y - it->m_R < 0 && it->m_Vy < 0) || (it->m_Y + it->m_R > width && it->m_Vy > 0))
			it->m_Vy = -it->m_Vy;
	}
	ch.m_X += ch.m_Vx;
	ch.m_Y += ch.m_Vy;
	if (ch.m_X - ch.m_R < 0)
		ch.m_X = 0 + ch.m_R;
	if (ch.m_X + ch.m_R > width)
		ch.m_X = width - ch.m_R;
	if (ch.m_Y - ch.m_R < 0)
		ch.m_Y = 0 + ch.m_R;
	if (ch.m_Y + ch.m_R > height)
		ch.m_Y = height - ch.m_R;
	if (!life)
	{
		while (1);
	}
	while (balls.size() < BALLNUM)
	{
		balls.push_front(Ball(randbetween(0, 600), randbetween(0, 600), ch.m_R + randbetween(0, 20) - BALLSIZE, HSVtoRGB(rand() % 360, 1, 1)));
	}
}

void update()
{
	updatewithinput();
	updatewithoutinput();
}

void show()
{
	cleardevice();
	for (list<Ball>::iterator it = balls.begin(); it != balls.end(); it++)
	{
		setfilllinecolor(it->m_Color);
		fillcircle(it->m_X, it->m_Y, it->m_R);
	}
	setfilllinecolor(ch.m_Color);
	fillcircle(ch.m_X, ch.m_Y, ch.m_R);
	FlushBatchDraw();
}

void timeclt()
{
	int i = WAIT;
	while (i--);
}


int main()
{
	startup();
	while (1)
	{
		update();
		show();
		timeclt();
	}

}