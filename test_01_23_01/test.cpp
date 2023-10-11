#include <graphics.h>

#include <conio.h>

#include <stdio.h>

#include <time.h>



#define NUM 300

#define MAXDISTANCE 8000



struct Ball  // 小球结构体

{

	float x, y; // 坐标

	float vx, vy; // 速度

	int radius; // 半径

	int hue; // 色调

	COLORREF  color; // 颜色

};



// 生成[min,max]之间的随机小数

float randBetween(float min, float max)

{

	float x = (double)rand() / RAND_MAX; // 生成0到1的随机小数

	float r = x * (max - min) + min; // 生成min到max的随机小数

	return r;

}



// 判断两个小球是否比较接近

float isNear(Ball ball1, Ball ball2)

{

	float d2 = (ball1.x - ball2.x) * (ball1.x - ball2.x) + (ball1.y - ball2.y) * (ball1.y - ball2.y);

	if (d2 < MAXDISTANCE)

		return d2; // 距离较近，就返回距离平方

	else

		return -1;  // 距离较远，返回-1

}



// 全局变量定义

int width = 1200; // 画面宽度

int height = 800; // 画面高度

Ball balls[NUM]; // 定义小球结构体变量



void startup()  //  初始化函数

{

	srand(time(0));  // 随机种子函数

	for (int i = 0; i < NUM; i++) // 对所有小球遍历

	{

		balls[i].radius = 2; // 小球半径

		balls[i].x = randBetween(balls[i].radius, width - balls[i].radius); // 小球x坐标

		balls[i].y = randBetween(balls[i].radius, height - balls[i].radius); // 小球y坐标

		balls[i].vx = randBetween(-1, 1); // 小球x方向速度

		balls[i].vy = randBetween(-1, 1); // 小球y方向速度		

		balls[i].hue = 360.0 * i / NUM; // 小球色调

		balls[i].color = HSVtoRGB(balls[i].hue, 0.7, 0.8); // 小球颜色

	}



	initgraph(width, height); // 新开一个画面

	setbkcolor(HSVtoRGB(0, 0, 0.1)); // 背景颜色

	BeginBatchDraw(); // 开始批量绘制

}



void show()  // 绘制函数

{

	cleardevice(); // 以背景颜色清屏



	for (int i = 0; i < NUM; i++) // 对第1个球遍历

	{

		for (int j = i + 1; j < NUM; j++) // 对第2个球遍历

		{

			float dis = isNear(balls[i], balls[j]);

			if (dis > 0) // 这两个球距离比较近，就画一条连线

			{

				// 色调为两个小球的均值

				int hue = (balls[i].hue + balls[j].hue) / 2;

				// 距离越近连线越鲜艳，距离越远越接近背景的饱和度 0

				float saturation = 1 - dis / MAXDISTANCE;

				// 距离越近连线越明亮，距离越远越接近背景色亮度 0.1

				float value = 0.1 + saturation * 0.9;

				setlinecolor(HSVtoRGB(hue, saturation, value)); // 设置线条颜色

				line(balls[i].x, balls[i].y, balls[j].x, balls[j].y); // 连线

			}

		}

	}



	for (int i = 0; i < NUM; i++) // 对所有小球遍历

	{

		setfillcolor(balls[i].color); // 设置填充颜色	

		setlinecolor(balls[i].color); // 设置线条颜色

		fillcircle(balls[i].x, balls[i].y, balls[i].radius); // 画小球

	}



	FlushBatchDraw(); // 批量绘制

	Sleep(10); // 暂停10毫秒

}



void update() //更新函数

{

	for (int i = 0; i < NUM; i++) // 对所有小球遍历

	{

		// 根据速度，更新小球的位置

		balls[i].x = balls[i].x + balls[i].vx;

		balls[i].y = balls[i].y + balls[i].vy;

		// 小球碰到左右边界，x速度反向

		if (balls[i].x <= balls[i].radius || balls[i].x >= width - balls[i].radius)

			balls[i].vx = -balls[i].vx;

		// 小球碰到上下边界，y速度反向

		if (balls[i].y <= balls[i].radius || balls[i].y >= height - balls[i].radius)

			balls[i].vy = -balls[i].vy;

	}

}



int main() //  主函数

{

	startup();  // 初始化函数，仅执行一次	

	while (1)   // 一直循环

	{

		show();  // 进行绘制

		update(); //进行更新 

	}

	return 0;

}