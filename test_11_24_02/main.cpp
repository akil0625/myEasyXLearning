#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <stdio.h>




int main()
{
	int width = 800;
	int height = 600;

	float x = width / 6;
	float y = height / 3;
	int radius = 0;
	printf("请输入小球半径\n");
	scanf("%d", &radius);

	//物理参数
	float g = 0.3;
	float vy = 0;
	float vx = 1;

	initgraph(width, height);


	while (1)
	{
		cleardevice();
		BeginBatchDraw();
		fillcircle(x, y, radius);
		EndBatchDraw();
		FlushBatchDraw();

		//加速
		vy += g;
		//位移
		y += vy;
		x += vx;

		//横轴撞墙
		if ((vx<0&& x <= radius) || (vx>0&& x >= width - radius))
		{
			vx = -vx;
		}
		
		//竖轴撞墙
		if ((vy<0&& y <= radius) || (vy>0&& y >= height - radius))
		{
			vy =  - vy;
		}


		Sleep(3);

	}

	system("pause");
	return 0;
}