#include <stdio.h>
#include <graphics.h>
#include <conio.h>


void setfilllinecolor(int cl)
{
	setlinecolor(cl);
	setfillcolor(cl);
}

void startup()
{
	initgraph(800, 600);
	//setbkcolor(RGB(0,255,255));
	cleardevice();
}


void show()
{
	BeginBatchDraw();
	for (int i = 0; i < 600; i++)
	{
		setfilllinecolor(RGB(0, 255 - i / 2.3529, 255 - i / 2.3529));
		fillrectangle(0, i, 800, i + 1);
	}
	setfilllinecolor(GREEN);
	fillcircle(200, 1400, 1000);
	setlinecolor(BLACK);
	fillcircle(800, 1450, 1000);
	setfilllinecolor(RED);
	fillcircle(0, 0, 100);
	FlushBatchDraw();
}

int main()
{
	startup();

	while (1)
	{
		//update();
		show();
	}
	return 0;
}