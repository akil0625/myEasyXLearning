#include <graphics.h>

#include <conio.h>

#include <stdio.h>



// ���������������ɫ

void setLineFillColor(int r, int g, int b)

{

	setlinecolor(RGB(r, g, b));

	setfillcolor(RGB(r, g, b));

}



int main()

{

	int len = 40; // С�����εı߳�

	int rowNum = 15; // ����

	int colNum = 19; // ����



	int width = (colNum + 2) * len; // ������

	int height = (rowNum + 2) * len; // ����߶�

	initgraph(width, height); // �¿�һ������

	setbkcolor(WHITE); // ������ɫ

	cleardevice(); // �Ա�����ɫ����



	for (int i = 1; i <= rowNum; i = i + 1)

		for (int j = 1; j <= colNum; j = j + 1)

		{

			if ((i + j) % 2 == 0)

			{

				// ��Ϊ��ɫ

				setLineFillColor(170, 220, 0);

			}

			else

			{

				// ��Ϊ��ɫ

				setLineFillColor(60, 190, 130);

			}

			fillrectangle(j * len, i * len, (j + 1) * len, (i + 1) * len);

		}





	for (int i = 2; i <= rowNum; i = i + 1)

		for (int j = 2; j <= colNum; j = j + 1)

		{

			if ((i - j) % 3 == 0)

			{

				// ��Ϊ��ɫ

				setLineFillColor(230, 255, 240);

			}

			else

			{

				// ��Ϊ��ɫ

				setLineFillColor(175, 50, 140);

			}

			fillcircle(j * len, i * len, 4);

		}



	_getch();

	return 0;

}