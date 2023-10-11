#include <graphics.h>

#include <conio.h>

#include <stdio.h>



// 设置线条、填充颜色

void setLineFillColor(int r, int g, int b)

{

	setlinecolor(RGB(r, g, b));

	setfillcolor(RGB(r, g, b));

}



int main()

{

	int len = 40; // 小正方形的边长

	int rowNum = 15; // 行数

	int colNum = 19; // 列数



	int width = (colNum + 2) * len; // 画面宽度

	int height = (rowNum + 2) * len; // 画面高度

	initgraph(width, height); // 新开一个画面

	setbkcolor(WHITE); // 背景白色

	cleardevice(); // 以背景颜色清屏



	for (int i = 1; i <= rowNum; i = i + 1)

		for (int j = 1; j <= colNum; j = j + 1)

		{

			if ((i + j) % 2 == 0)

			{

				// 设为黄色

				setLineFillColor(170, 220, 0);

			}

			else

			{

				// 设为青色

				setLineFillColor(60, 190, 130);

			}

			fillrectangle(j * len, i * len, (j + 1) * len, (i + 1) * len);

		}





	for (int i = 2; i <= rowNum; i = i + 1)

		for (int j = 2; j <= colNum; j = j + 1)

		{

			if ((i - j) % 3 == 0)

			{

				// 设为白色

				setLineFillColor(230, 255, 240);

			}

			else

			{

				// 设为红色

				setLineFillColor(175, 50, 140);

			}

			fillcircle(j * len, i * len, 4);

		}



	_getch();

	return 0;

}