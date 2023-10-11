#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <ctime>
#include <math.h>

#define VMAX 10
#define R 10


DWORD* g_pBuf;



void fast_putpixel(int x, int y, COLORREF c)
{
	g_pBuf[y * 600 + x] = BGR(c);
}

COLORREF fast_getpixel(int x, int y)
{
	COLORREF c = g_pBuf[y * 640 + x];
	return BGR(c);
}



float width = 600;
float height = 600;

bool board[600][600];

float x = 0;
float y = 0;
float r = 0;
float vx = 0;
float vy = 0;
float ax = 0;
float ay = 0;

float k = 200;

int randbetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

void startup()
{
	srand((unsigned int)time(NULL));
	initgraph(width, height);
	// дк main КЏЪ§жа
	g_pBuf = GetImageBuffer();
	cleardevice();
	setfillcolor(YELLOW);
	setlinecolor(YELLOW);
	BeginBatchDraw();
	x = randbetween(0, width);
	y = randbetween(0, height);
	r = R;
	vx = randbetween(-VMAX, VMAX)/10.0;
	vy = randbetween(-VMAX, VMAX)/10.0;
}

void update()
{
	float d = sqrt(pow(x - width / 2, 2) + pow(y - height / 2,2));
	float a = k / pow(d, 2);
	ax = -a * ((x - width / 2) / d);
	ay = -a * ((y - height / 2) / d);
	vx += ax;
	vy += ay;
	x += vx;
	y += vy;
	if ((int)x >= 0 && (int)x < 600 && (int)y >= 0 && (int)y < 600)
		board[(int)x][(int)y] = true;
}


void show()
{
	cleardevice();
	setfillcolor(0xAA7A00);
	setlinecolor(0x00AA00);
	fillcircle(x,y,r);
	for (int i = 0; i < 600; i++)
		for (int j = 0; j < 600; j++)
		{
			if(board[i][j])
				fast_putpixel(i, j,WHITE);
		}
	setfillcolor(0x0057ff);
	setlinecolor(0x0057ff);
	fillcircle(width / 2, height / 2, 5);
	FlushBatchDraw();
}

int main()
{
	int i = 5000000;
	startup();
	while (1)
	{
		update();
		show();
		i = 4000000;
		//i = 3000;
		while (i--);
	}
}