#include <graphics.h>
#include <conio.h>
#include <stdio.h>


int main()
{
	int height = 600;
	int width = 800;
	int Oy = height/2;
	int Ox = width/2;
	int r = 20;
	int vy = 3;
	int vx = 3;

	initgraph(width  , height);
	while (1)
	{
		//�������½�
		if (Oy >= height-r || Oy <= r)
		{
			vy = -vy;
		}
		//�������ҽ�
		if (Ox >= width-r || Ox < r)
		{
			vx = -vx;
		}
		//�ƶ�
		Oy += vy;
		Ox += vx;
		//��ͼ
		fillcircle(Ox, Oy, r);
		Sleep(33);
		cleardevice();
	}


	return 0;
}