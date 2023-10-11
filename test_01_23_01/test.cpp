#include <graphics.h>

#include <conio.h>

#include <stdio.h>

#include <time.h>



#define NUM 300

#define MAXDISTANCE 8000



struct Ball  // С��ṹ��

{

	float x, y; // ����

	float vx, vy; // �ٶ�

	int radius; // �뾶

	int hue; // ɫ��

	COLORREF  color; // ��ɫ

};



// ����[min,max]֮������С��

float randBetween(float min, float max)

{

	float x = (double)rand() / RAND_MAX; // ����0��1�����С��

	float r = x * (max - min) + min; // ����min��max�����С��

	return r;

}



// �ж�����С���Ƿ�ȽϽӽ�

float isNear(Ball ball1, Ball ball2)

{

	float d2 = (ball1.x - ball2.x) * (ball1.x - ball2.x) + (ball1.y - ball2.y) * (ball1.y - ball2.y);

	if (d2 < MAXDISTANCE)

		return d2; // ����Ͻ����ͷ��ؾ���ƽ��

	else

		return -1;  // �����Զ������-1

}



// ȫ�ֱ�������

int width = 1200; // ������

int height = 800; // ����߶�

Ball balls[NUM]; // ����С��ṹ�����



void startup()  //  ��ʼ������

{

	srand(time(0));  // ������Ӻ���

	for (int i = 0; i < NUM; i++) // ������С�����

	{

		balls[i].radius = 2; // С��뾶

		balls[i].x = randBetween(balls[i].radius, width - balls[i].radius); // С��x����

		balls[i].y = randBetween(balls[i].radius, height - balls[i].radius); // С��y����

		balls[i].vx = randBetween(-1, 1); // С��x�����ٶ�

		balls[i].vy = randBetween(-1, 1); // С��y�����ٶ�		

		balls[i].hue = 360.0 * i / NUM; // С��ɫ��

		balls[i].color = HSVtoRGB(balls[i].hue, 0.7, 0.8); // С����ɫ

	}



	initgraph(width, height); // �¿�һ������

	setbkcolor(HSVtoRGB(0, 0, 0.1)); // ������ɫ

	BeginBatchDraw(); // ��ʼ��������

}



void show()  // ���ƺ���

{

	cleardevice(); // �Ա�����ɫ����



	for (int i = 0; i < NUM; i++) // �Ե�1�������

	{

		for (int j = i + 1; j < NUM; j++) // �Ե�2�������

		{

			float dis = isNear(balls[i], balls[j]);

			if (dis > 0) // �����������ȽϽ����ͻ�һ������

			{

				// ɫ��Ϊ����С��ľ�ֵ

				int hue = (balls[i].hue + balls[j].hue) / 2;

				// ����Խ������Խ���ޣ�����ԽԶԽ�ӽ������ı��Ͷ� 0

				float saturation = 1 - dis / MAXDISTANCE;

				// ����Խ������Խ����������ԽԶԽ�ӽ�����ɫ���� 0.1

				float value = 0.1 + saturation * 0.9;

				setlinecolor(HSVtoRGB(hue, saturation, value)); // ����������ɫ

				line(balls[i].x, balls[i].y, balls[j].x, balls[j].y); // ����

			}

		}

	}



	for (int i = 0; i < NUM; i++) // ������С�����

	{

		setfillcolor(balls[i].color); // ���������ɫ	

		setlinecolor(balls[i].color); // ����������ɫ

		fillcircle(balls[i].x, balls[i].y, balls[i].radius); // ��С��

	}



	FlushBatchDraw(); // ��������

	Sleep(10); // ��ͣ10����

}



void update() //���º���

{

	for (int i = 0; i < NUM; i++) // ������С�����

	{

		// �����ٶȣ�����С���λ��

		balls[i].x = balls[i].x + balls[i].vx;

		balls[i].y = balls[i].y + balls[i].vy;

		// С���������ұ߽磬x�ٶȷ���

		if (balls[i].x <= balls[i].radius || balls[i].x >= width - balls[i].radius)

			balls[i].vx = -balls[i].vx;

		// С���������±߽磬y�ٶȷ���

		if (balls[i].y <= balls[i].radius || balls[i].y >= height - balls[i].radius)

			balls[i].vy = -balls[i].vy;

	}

}



int main() //  ������

{

	startup();  // ��ʼ����������ִ��һ��	

	while (1)   // һֱѭ��

	{

		show();  // ���л���

		update(); //���и��� 

	}

	return 0;

}