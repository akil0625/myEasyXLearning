#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>




int main()
{
	srand((unsigned int)time(NULL));
	//窗口宽高
	float width, height;
	width = 800;
	height = 600;
	
	//初始化
	initgraph(width, height);
	
	//小球半径
	float radius = 30;

	//障碍物左上顶点坐标
	int b_left = width;
	int b_height =270+rand()%250;
	int b_v = 10 + rand() % 5;
	//障碍物宽度
	int b_width = 30;

	//得分
	int score = 0;

	TCHAR s[20]; // 定义字符串数组

settextstyle(40, 0, _T("宋体")); // 设置文字大小、字体





	
	//小球圆心坐标
	float ball_x, ball_y;
	ball_x = width / 4;
	ball_y = height - radius;
	
	//物理参数
	float g = 0.9;
	float vy = 0;


	char l = '\0';
	int flag = 1;


	while (true)
	{

		//键盘被敲击时的动作
		if (_kbhit())
		{
			l = _getch();
			if (' ' == l&&ball_y==height-radius)
			{
				vy = -27;
			}
		}//h = 166
		Sleep(3);

		if (b_left < 0)
		{
			b_height = 270 + rand() % 250;
			b_left = width;
			b_v = 10+rand() % 5;
			score++;
		}


		if (ball_y + radius > b_height && ball_x + radius > b_left && ball_x - radius < b_left + b_width)
		{
			Sleep(30);
			score = 0;
		}


		//默认的动作
		vy += g;
		ball_y += vy;
		b_left -= b_v;


		

		if (ball_y > height - radius)
		{
			ball_y = height - radius;

		}
		swprintf_s(s, _T("%d"), score); // 将score转换为字符串
		cleardevice();
		BeginBatchDraw();
		//输出得分文字
		outtextxy(50, 30, s);
		//画圆
		fillcircle(ball_x, ball_y, radius);
		fillrectangle(b_left - 1, b_height, b_left + b_width, height);
		FlushBatchDraw();
		EndBatchDraw();
		
	}

	return 0;
}