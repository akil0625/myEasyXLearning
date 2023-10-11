#include<iostream>
using namespace std;
#include<conio.h>
#include<graphics.h>
#include<ctime>
#include<math.h>
#include<vector>

#define VMAX 1
#define RMAX 3
#define RMIN 3
#define BALLNUM 4
#define WAIT 10000000
#define K 20

static int width = 600;
static int height = 600;
static int A = 0;

int randbetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}
void setfilllinecolor(COLORREF color)
{
	setfillcolor(color);
	setlinecolor(color);
}
bool isSame(long double l, long double r)
{
	if (l > 0 && r > 0|| l < 0 && r < 0)
		return 1;
	return 0;
}

class Ball
{
public:
	long double m_X;
	long double m_Y;
	long double m_Vx;
	long double m_Vy;
	long double m_Ax;
	long double m_Ay;
	long double m_R;
	COLORREF m_Color;

	Ball()
	{
		m_R = randbetween(RMIN, RMAX);
		m_X = randbetween(0 + m_R, width - m_R);
		m_Y = randbetween(0 + m_R, height - m_R);
		m_Vx = randbetween(-VMAX, VMAX);
		m_Vy = randbetween(-VMAX, VMAX);
		m_Color = 2*(randbetween(1, 8) * 16 + randbetween(1, 8) * 16 * 256 + randbetween(1, 8) * 16 * 256 * 256);
		m_Ax = 0;
		m_Ay = 0;
	}
	int isOut()
	{
		if ((m_X + m_R < 0 && m_Vx < 0) || (m_X - m_R > width && m_Vx > 0))
			return 1;
		if ((m_Y + m_R < 0 && m_Vy < 0) || (m_Y - m_R > height && m_Vy > 0))
			return 2;
		return 0;
	}
	void rebound()
	{
		if ((m_X - m_R < 0 && m_Vx < 0) || (m_X + m_R > width && m_Vx > 0))
			m_Vx = -m_Vx;
		if ((m_Y - m_R < 0 && m_Vy < 0) || (m_Y + m_R > height && m_Vy > 0))
			m_Vy = -m_Vy;
	}
	long double getD(Ball bl)
	{
		return sqrt(pow(bl.m_X - m_X, 2) + pow(bl.m_Y - m_Y, 2));
	}
	long double getA(Ball bl)
	{
		return K / pow(getD(bl), 2);
	}
	void speedUp(Ball bl)
	{
		long double a = getA(bl);
		long double d = getD(bl);
		m_Ax += a * (bl.m_X - m_X) / d;
		m_Ay += a * (bl.m_Y - m_Y) / d;
	}
	void move()
	{
		m_Vx += m_Ax;
		m_Vy += m_Ay;
		m_X += m_Vx;
		m_Y += m_Vy;
	}
	void showUp()
	{
		setfilllinecolor(m_Color);
		fillcircle(m_X, m_Y, m_R);
	}
};

static vector<Ball> v1;

void startup()
{
	srand((unsigned int)time(NULL));
	initgraph(width, height);
	setbkcolor(BLACK);
	cleardevice();
	BeginBatchDraw();
	v1.reserve(BALLNUM);
	for (int i = 0; i < BALLNUM; i++)
		v1.push_back(Ball());
	//令第一个球静止与中心
	//v1.begin()->m_Vx = 0;
	//v1.begin()->m_Vy = 0;
	//v1.begin()->m_X = width / 2;
	//v1.begin()->m_Y = height / 2;
	//v1.begin()->m_Ax = 0;
	//v1.begin()->m_Ay = 0;
}

void update()
{
	for (vector<Ball>::iterator it = v1.begin(); it < v1.end(); it++)
	{
		it->m_Ax = 0;
		it->m_Ay = 0;
		for (vector<Ball>::iterator itelse = v1.begin(); itelse < v1.end(); itelse++)
		{
			if (it == itelse)
				continue;
			it->speedUp(*itelse);
			//令第一个球不碰撞
			/*if (itelse == v1.begin())
				continue;*/
			if (it->getD(*itelse) < 10+it->m_R + itelse->m_R &&
				((isSame(it->m_Vx - itelse->m_Vx, itelse->m_X - it->m_X)) ||
					(isSame(it->m_Vy - itelse->m_Vy, itelse->m_Y - it->m_Y))))
			{
				long double tmp = it->m_Vx;
				it->m_Vx = 1.07*itelse->m_Vx;
				itelse->m_Vx = 1.07*tmp;
				tmp = it->m_Vy;
				it->m_Vy = 1.07*itelse->m_Vy;
				itelse->m_Vy = 1.07*tmp;
			}			
		}
		//it->rebound();
		it->move();
		if (it->isOut() == 1)
			it->m_X = width - it->m_X;
		if (it->isOut() == 2)
			it->m_Y = height - it->m_Y;
	}
}

void show()
{
	cleardevice();
	for (vector<Ball>::iterator it = v1.begin(); it < v1.end(); it++)
	{
		(*it).showUp();
	}
	FlushBatchDraw();
}

void timeCtl()
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
		timeCtl();
	}
}