#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>




int main()
{
	srand((unsigned int)time(NULL));
	//���ڿ��
	float width, height;
	width = 800;
	height = 600;
	
	//��ʼ��
	initgraph(width, height);
	
	//С��뾶
	float radius = 30;

	//�ϰ������϶�������
	int b_left = width;
	int b_height =270+rand()%250;
	int b_v = 10 + rand() % 5;
	//�ϰ�����
	int b_width = 30;

	//�÷�
	int score = 0;

	TCHAR s[20]; // �����ַ�������

settextstyle(40, 0, _T("����")); // �������ִ�С������





	
	//С��Բ������
	float ball_x, ball_y;
	ball_x = width / 4;
	ball_y = height - radius;
	
	//�������
	float g = 0.9;
	float vy = 0;


	char l = '\0';
	int flag = 1;


	while (true)
	{

		//���̱��û�ʱ�Ķ���
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


		//Ĭ�ϵĶ���
		vy += g;
		ball_y += vy;
		b_left -= b_v;


		

		if (ball_y > height - radius)
		{
			ball_y = height - radius;

		}
		swprintf_s(s, _T("%d"), score); // ��scoreת��Ϊ�ַ���
		cleardevice();
		BeginBatchDraw();
		//����÷�����
		outtextxy(50, 30, s);
		//��Բ
		fillcircle(ball_x, ball_y, radius);
		fillrectangle(b_left - 1, b_height, b_left + b_width, height);
		FlushBatchDraw();
		EndBatchDraw();
		
	}

	return 0;
}