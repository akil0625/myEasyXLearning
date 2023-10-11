#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

//斐波那契图形

int fibonacci(int n)
{
	n++;
	if (n <= 2)
		return 1;
	int f1 = 1;
	int f2 = 1;
	int tmp = 0;
	for (int i = 2; i < n; i++)
	{
		tmp = f2;
		f2 += f1;
		f1 = tmp;
	}
	return f2;
}


int main()
{
	int flag = 1;//1、左2、上3、右4、下
	int l, t, r, b;
	l = 500;
	t = 500;
	r = 500;
	b = 500;
	int R = 0;
	int Rpre = 0;
	initgraph(800, 800);
	for (int i = 0; i < 12; i++)
	{
		R = 5*fibonacci(i);
		Rpre = (r - l) / 2;
		switch (flag)
		{
		case 1:
			b = b - Rpre + R;
			t = b - 2 * R;
			l = r - 2 * R;
			arc(l, t, r, b, 0, 3.141592 / 2);
			break;
		case 2 :
			r = r - Rpre + R;
			l = r - 2 * R;
			b = t + 2 * R;
			arc(l, t, r, b, 1.57, 3.141592);
			break;
		case 3:
			t = t + Rpre - R;
			b = t + 2 * R;
			r = l + 2 * R;
			arc(l, t, r, b, 3.14, 3.141592 * 3 / 2);
			break;
		case 4:
			l = l + Rpre - R;
			r = l + 2 * R;
			t = b - 2 * R;
			arc(l, t, r, b, 4.71, 3.141592 * 2);
			break;
		case 5:
			flag = 0;
		}
		flag++;
	}



	system("pause");
	return 0;
}