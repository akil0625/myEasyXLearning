#include <iostream>
#include <conio.h>
using namespace std;
#include <graphics.h>
#include <vector>
#define Pi 3.1415926


class Point
{
public:
	Point(float x,float y,float color)
	{
		m_X = x;
		m_Y = y;
		m_Color = HSVtoRGB(color,1,1);
	}
	void show(pair<pair<float, float>, pair<float, float>> ij)
	{
		putpixel(m_X*ij.first.first+m_Y * ij.second.first, m_X*ij.first.second + m_Y*ij.second.second, m_Color);
	}
	float m_X;
	float m_Y;
	float m_Color;
};



int main()
{
	float width = 600;
	float height = 600;
	initgraph(width, height);
	//setbkcolor(WHITE);
	BeginBatchDraw();
	setorigin(300, 300);
	setaspectratio(1, -1);
	pair<pair<float, float>, pair<float, float>>ij;

	ij.first.first = 1;
	ij.first.second = 0;
	ij.second.first = 0;
	ij.second.second = 1;//设置基向量

	vector<Point>points;
	for (int i = 0; i < 180; i++)//画图
	{
		for(int j = 0; j < 180; j++)
		{
			points.push_back(Point( i-90, j-90, i+j));
		}
	}

	float a, b, c, d;
	float Redios = 0;
	while (true)//变换
	{
		ij.first.first = 0;//cos(Redios);
		ij.first.second = 1;//sin(Redios);
		ij.second.first = cos(Redios + Pi/2);
		ij.second.second = 0.5*sin(Redios + Pi/2);

		a = ij.first.first;
		b = ij.first.second;
		c = ij.second.first;
		d = ij.second.second;

		/*ij.first.first = (6 * a - 6 * b)/sqrt(37);
		ij.first.second = (a+b)/ sqrt(37);

		ij.second.first = (6 * c - 6 * d)/sqrt(37);
		ij.second.second = (c + d)/ sqrt(37);*/

		/*ij.first.first = a+b;
		ij.first.second = b;

		ij.second.first = c+d;
		ij.second.second = d;*/


		cleardevice();
		setorigin(300, 300);
		for (int i = 0; i < points.size(); i++)
		{
			points[i].show(ij);
		}
		//setorigin(300,200);
		//for (int i = 0; i < points.size(); i++)
		//{
		//	points[i].show(ij);
		//}
		FlushBatchDraw();
		Redios += 0.017;
	}


	system("pause");
	return 0;
}