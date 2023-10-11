#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#define PI 3.14159

void drowarc(int x,int y,int R,float b,float e)
{
	solidpie(x - R, y - R, x + R, y + R, b*2*PI, e*2*PI);
}

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(800, 800);
	int x = 400;
	int y = 400;
	int R = 300;
	for ( int i = 0; i < 360; i++)
	{
		setfillcolor(HSVtoRGB(i, 1, 1));
		setlinecolor(HSVtoRGB(i, 1, 1));
		drowarc(x,y,R,i*(1.0/360), (i+1)*(1.0/360));
	}
	system("pause");
	return 0;
}