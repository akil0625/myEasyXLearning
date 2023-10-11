#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

#define height 800
#define width 800
#define PI 3.14159

void drawcircle(int x, int y, int R, int n)
{
	if (R < 1)
		return;
	float arc = -PI/2;
	for (int i = 0; i < n; arc += (2 * PI / n),i++)
	{
		circle(x, y, R);
		drawcircle(x + 4 * R * cos(arc), y + 4 * R * sin(arc), R / 2, n);
	}
	
}




int main()
{
	initgraph(width, height);
	int i = 1;
	while (1)
	{
		drawcircle(400, 400, 50, i);
		_getch();
		cleardevice();
		i++;
	}
	drawcircle(400, 400, 100, 6);
	while (1);
	return 0;
}