#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <ctime>
#include <math.h>

#define BALLNUM 10
#define MAXREDIS 30
#define MINREDIS 20
#define MAXV 10
#define wait 50000000


int width = 600;
int height = 600;

void setfilllinecolor(COLORREF color)
{
	setfillcolor(color);
	setlinecolor(color);
}

int randbetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

class Ball
{
public:
	int m_X;
	int m_Y;
	int m_R;
	int m_Vx;
	int m_Vy;
	COLORREF m_Color;
	void update()
	{
		if ((m_Y + m_R > height && m_Vy > 0) || (m_Y - m_R < 0 && m_Vy < 0))
			m_Vy = -m_Vy;
		if ((m_X + m_R > width && m_Vx > 0) || (m_X - m_R < 0 && m_Vx < 0))
			m_Vx = -m_Vx;
	}
	void move()
	{
		m_X += m_Vx;
		m_Y += m_Vy;
	}
	void showup()
	{
		setfilllinecolor(m_Color);
		fillcircle(m_X, m_Y, m_R);
	}
};

Ball ball[BALLNUM];

void startup()
{
	srand((unsigned int)time(NULL));
	initgraph(width, height);
	setbkcolor(YELLOW);
	cleardevice();
	BeginBatchDraw();
	for (int i = 0; i < BALLNUM; i++)
	{
		ball[i].m_Color = randbetween(1, 16) * 16 * 256 * 256 + randbetween(1, 16) * 16 * 256 + randbetween(1, 16) * 16;
		ball[i].m_R = randbetween(MINREDIS, MAXREDIS);
		ball[i].m_X = randbetween(0, width);
		ball[i].m_Y = randbetween(0, height);
		ball[i].m_Vx = randbetween(-MAXV, MAXV);
		ball[i].m_Vy = randbetween(-MAXV, MAXV);
	}
}

void update()
{
	if (_kbhit())
	{
		_getch();
		while (!_kbhit());
		_getch();
	}
	for (int i = 0; i < BALLNUM; i++)
	{
		ball[i].update();
		ball[i].move();
	}
}


void show()
{
	cleardevice();
	for (int i = 0; i < BALLNUM; i++)
	{
		ball[i].showup();
	}
	FlushBatchDraw();
}

void timectl()
{
	int i = wait;
	while (i)
	{
		i--;
	}
}

int main()
{
	startup();
	while (1)
	{
		update();
		show();
		timectl();
	}


}