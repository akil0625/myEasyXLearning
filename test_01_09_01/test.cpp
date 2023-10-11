#include <stdio.h>
#include <graphics.h>
#include <conio.h>

//ÊÓ¾õÐ§¹û


int main()
{
	int col = 8;
	int row = 8;
	int len = 70;
	initgraph(row*len,col*len);
	setbkcolor(WHITE);
	cleardevice();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2)
			{
				setlinecolor(RGB(60, 90, 130));
				setfillcolor(RGB(60, 90, 130));
			}
			else
			{
				setlinecolor(RGB(170, 220, 0));
				setfillcolor(RGB(170, 220, 0));
			}
			fillrectangle(i * len, j * len, (i + 1) * len, (j + 1) * len);
		}

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
		{
			if ((i - j) % 3==0)
			{
				setlinecolor(RGB(230, 255, 240));
				setfillcolor(RGB(230, 255, 240));
			}
			else
			{
				setlinecolor(RGB(175, 50, 140));
				setfillcolor(RGB(175, 50, 140));
			}
			fillcircle((i + 1) * len, (j + 1) * len, 8);
		}

	system("pause");
	return 0;
}