#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


int main()
{
	srand((unsigned int)time(NULL));
	//���ڴ�С
	int width = 800;
	int height = 600;
	//�������
	float g = 0.3;
	float vy = 0;
	float x = width / 6;
	float y = height / 3;
	int radius = 20;
	char input = '0';

	//�Ϸ��ϰ������½�����
	int b_xLeft = 0;
	int b_yBottom = 0;
	//�ϰ�����
	int b_width = 30;
	//�ϰ����϶
	int b_gap = 300;

	b_xLeft = - b_gap;
	int grade = -1;
	TCHAR s[20]; // �����ַ�������

	//��ʼ������
	initgraph(width, height);
	while (true)
	{
		BeginBatchDraw();
		
		//����÷�����
		outtextxy(50, 30, s);

		//�����ϰ���
		rectangle(b_xLeft, 0, b_xLeft + b_width, b_yBottom);
		rectangle(b_xLeft, b_yBottom + b_gap-grade*10, b_xLeft + b_width, width);
		//����Բ
		circle(x, y, radius+2*grade);
		
		EndBatchDraw();
		FlushBatchDraw();
		
		

		if (_kbhit())
		{
			input = _getch();
			if (input == ' ')
				vy = -10;
		}
		settextstyle(40, 0, _T("����")); // �������ִ�С������
		swprintf_s(s, _T("%d"), grade); // ��scoreת��Ϊ�ַ���
		if (b_xLeft <= -b_width)
		{
			b_xLeft = width;
			b_yBottom = rand() % (height - b_gap + 1 - grade * 10);
			grade++;
		}

		//����
		if ((y - radius - 2 * grade<b_yBottom || y + radius + 2 * grade>b_yBottom + b_gap) && x + radius + 2 * grade > b_xLeft && x - radius - 2 * grade < b_xLeft + b_width)
		{
			Sleep(20);
			grade = 0;
		}

	
		//����
		vy += g;
		//λ��
		y += vy;
		b_xLeft -= (3+grade/3);


		//���練��
		if ((y < radius && vy < 0) || (y > height - radius && vy > 0))
		{
			vy = -vy;
		}
		
		Sleep(6);
		cleardevice();
	}



	return 0;
}


//TCHAR s[20]; // �����ַ�������
//		//����÷�����
//outtextxy(50, 30, s);
//settextstyle(40, 0, _T("����")); // �������ִ�С������
//swprintf_s(s, _T("%d"), grade); // ��scoreת��Ϊ�ַ���
//