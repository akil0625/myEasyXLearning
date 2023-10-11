#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


int main()
{
	srand((unsigned int)time(NULL));
	//窗口大小
	int width = 800;
	int height = 600;
	//物理参数
	float g = 0.3;
	float vy = 0;
	float x = width / 6;
	float y = height / 3;
	int radius = 20;
	char input = '0';

	//上方障碍物左下角坐标
	int b_xLeft = 0;
	int b_yBottom = 0;
	//障碍物宽度
	int b_width = 30;
	//障碍物空隙
	int b_gap = 300;

	b_xLeft = - b_gap;
	int grade = -1;
	TCHAR s[20]; // 定义字符串数组

	//初始化窗口
	initgraph(width, height);
	while (true)
	{
		BeginBatchDraw();
		
		//输出得分文字
		outtextxy(50, 30, s);

		//绘制障碍物
		rectangle(b_xLeft, 0, b_xLeft + b_width, b_yBottom);
		rectangle(b_xLeft, b_yBottom + b_gap-grade*10, b_xLeft + b_width, width);
		//绘制圆
		circle(x, y, radius+2*grade);
		
		EndBatchDraw();
		FlushBatchDraw();
		
		

		if (_kbhit())
		{
			input = _getch();
			if (input == ' ')
				vy = -10;
		}
		settextstyle(40, 0, _T("宋体")); // 设置文字大小、字体
		swprintf_s(s, _T("%d"), grade); // 将score转换为字符串
		if (b_xLeft <= -b_width)
		{
			b_xLeft = width;
			b_yBottom = rand() % (height - b_gap + 1 - grade * 10);
			grade++;
		}

		//碰壁
		if ((y - radius - 2 * grade<b_yBottom || y + radius + 2 * grade>b_yBottom + b_gap) && x + radius + 2 * grade > b_xLeft && x - radius - 2 * grade < b_xLeft + b_width)
		{
			Sleep(20);
			grade = 0;
		}

	
		//加速
		vy += g;
		//位移
		y += vy;
		b_xLeft -= (3+grade/3);


		//碰界反弹
		if ((y < radius && vy < 0) || (y > height - radius && vy > 0))
		{
			vy = -vy;
		}
		
		Sleep(6);
		cleardevice();
	}



	return 0;
}


//TCHAR s[20]; // 定义字符串数组
//		//输出得分文字
//outtextxy(50, 30, s);
//settextstyle(40, 0, _T("宋体")); // 设置文字大小、字体
//swprintf_s(s, _T("%d"), grade); // 将score转换为字符串
//