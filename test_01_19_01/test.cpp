#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <ctime>

#define PI 3.14159

#define k 1
#define matom 1800
#define melc 1
#define Ratom 20
#define Relc 7

#define atomnum 20
#define elcnum 20


typedef struct Atom
{
	double x;
	double y;
	double v;
	double vd;
	double a;
	double ad;
	double q;
	double m;
	double R;
}Atom;

typedef struct Elc
{
	double x;
	double y;
	double v;
	double vd;
	double a;
	double ad;
	double q;
	double m;
	double R;
}Elc;

Atom atoms[atomnum];
Elc elcs[elcnum];
int width = 800;
int height = 800;

double randbetween(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

void setfilllinecolor(int cl)
{
	setlinecolor(cl);
	setfillcolor(cl);
}

double arcsum(double size1,double arc1,double size2,double arc2)
{
	double x1 = size1 * cos(arc1);
	double x2 = size2 * cos(arc2);
	double y1 = size1 * sin(arc1);
	double y2 = size2 * sin(arc2);
	if (x1 + x2 == 0 && y1 + y2 > 0)
		return PI / 2;
	else if (x1 + x2 == 0 && y1 + y2 < 0)
		return -PI / 2;
	else if (x1 + x2 == 0)
		return 0;
	return atan((y1 + y2) / (x1 + x2));
}

void startup()
{
	initgraph(width, height);
	setbkcolor(YELLOW);
	cleardevice();
	for (int i = 0; i < atomnum; i++)
	{
		atoms[i].a = 0;
		atoms[i].ad = PI/4;
		atoms[i].m = matom;
		atoms[i].q = 1;
		atoms[i].R = Ratom;
		atoms[i].v = randbetween(5, 20);
		atoms[i].vd = randbetween(0, 6);
		atoms[i].x = randbetween(0 + Ratom, 800 - Ratom);
		atoms[i].y = randbetween(0 + Ratom, 800 - Ratom);
	}
	for (int i = 0; i < elcnum; i++)
	{
		elcs[i].a = 0;
		elcs[i].ad = PI/2;
		elcs[i].m = melc;
		elcs[i].q = 1;
		elcs[i].R = Relc;
		elcs[i].v = randbetween(5, 20);
		elcs[i].vd = randbetween(0, 6);
		elcs[i].x = randbetween(0 + Ratom, 800 - Ratom);
		elcs[i].y = randbetween(0 + Ratom, 800 - Ratom);
	}
}

void update()
{
	int tmpv = 0;
	//加速和位移更行
	for (int i = 0; i < atomnum; i++)
	{
		atoms[i].x += (atoms[i].v * cos(atoms[i].vd));
		atoms[i].y += (atoms[i].v * sin(atoms[i].vd));
		if (atoms[i].a == 0)
			continue;
		tmpv = sqrt(pow(atoms[i].v, 2) + pow(atoms[i].a, 2) + 2 * atoms[i].v * atoms[i].a * cos(atoms[i].vd - atoms[i].ad));
		if (((atoms[i].v * cos(atoms[i].vd) + atoms[i].a * cos(atoms[i].ad)) != 0))
			atoms[i].vd = atan((atoms[i].v * sin(atoms[i].vd) + atoms[i].a * sin(atoms[i].ad))
				/ ((atoms[i].v * cos(atoms[i].vd) + atoms[i].a * cos(atoms[i].ad))));
		else if ((atoms[i].v * sin(atoms[i].vd) + atoms[i].a * sin(atoms[i].ad)) > 0)
			atoms[i].vd = PI / 2;
		else
			atoms[i].vd = -PI / 2;
		atoms[i].v = tmpv;
	}
	for (int i = 0; i < elcnum; i++)
	{
		elcs[i].x += (elcs[i].v * cos(elcs[i].vd));
		elcs[i].y += (elcs[i].v * sin(elcs[i].vd));
		if (elcs[i].a == 0)
			continue;
		tmpv = sqrt(pow(elcs[i].v, 2) + pow(elcs[i].a, 2) + 2 * elcs[i].v * elcs[i].a * cos(elcs[i].vd - elcs[i].ad));
		if (((elcs[i].v * cos(elcs[i].vd) + elcs[i].a * cos(elcs[i].ad)) != 0))
			elcs[i].vd = atan((elcs[i].v * sin(elcs[i].vd) + elcs[i].a * sin(elcs[i].ad))
				/ ((elcs[i].v * cos(elcs[i].vd) + elcs[i].a * cos(elcs[i].ad))));
		else if ((elcs[i].v * sin(elcs[i].vd) + elcs[i].a * sin(elcs[i].ad)) > 0)
			elcs[i].vd = PI / 2;
		else
			elcs[i].vd = -PI / 2;
		elcs[i].v = tmpv;
	}
	//碰撞检测
	for (int i = 0; i < atomnum; i++)
	{
		if ((atoms[i].x - atoms[i].R <= 0 && cos(atoms[i].vd) < 0)
			|| (atoms[i].x + atoms[i].R >= 800 && cos(atoms[i].vd) > 0))
			atoms[i].vd = PI - atoms[i].vd;
		if ((atoms[i].y - atoms[i].R <= 0 && sin(atoms[i].vd) < 0)
			|| (atoms[i].y + atoms[i].R >= 800 && sin(atoms[i].vd) > 0))
			atoms[i].vd = - atoms[i].vd;
	}
	for (int i = 0; i < elcnum; i++)
	{
		if ((elcs[i].x - elcs[i].R <= 0 && cos(elcs[i].vd) < 0)
			|| (elcs[i].x + elcs[i].R >= 800 && cos(elcs[i].vd) > 0))
			elcs[i].vd = PI - elcs[i].vd;
		if ((elcs[i].y - elcs[i].R <= 0 && sin(elcs[i].vd) < 0)
			|| (elcs[i].y + elcs[i].R >= 800 && sin(elcs[i].vd) > 0))
			elcs[i].vd = -elcs[i].vd;
	}
	//库仑力更新
	/*double d = 0;
	double dx = 0;
	double dy = 0;
	double tmpa = 0;
	double arct = 0;
	for (int i = 0; i < atomnum; i++)
	{
		atoms[i].a = 0;
		atoms[i].ad = 0;
		for (int j = 0; j < atomnum; j++)
		{
 			d = sqrt(pow(atoms[j].x - atoms[i].x, 2)+pow(atoms[j].y - atoms[i].y, 2));
			dx = atoms[j].x - atoms[i].x;
			dy = atoms[j].y - atoms[i].y;
			if (d == 0)
				continue;
			tmpa = sqrt(pow(atoms[i].a, 2) + 
				2 * atoms[i].a * k / (pow(d, 2) * matom )* cos(atoms[j].ad - atoms[i].ad) +
				pow(k / ((pow(d, 2) * matom)),2));
			if (dx == 0 && dy > 0)
				arct = PI/2;
			if (dx == 0 && dy < 0)
				arct = -PI / 2;
			arct = atan(dy / dx);
			atoms[i].ad = arcsum(atoms[i].a, atoms[i].ad, k / (pow(d, 2) * matom), arct);
			atoms[i].a = tmpa;
		}
	}*/

}

void show()
{
	BeginBatchDraw();
	cleardevice();
	setfilllinecolor(RED);
	for (int i = 0; i < atomnum; i++)
	{
		fillcircle(atoms[i].x, atoms[i].y, atoms[i].R);
	}
	setfilllinecolor(BLUE);
	for (int i = 0; i < elcnum; i++)
	{
		fillcircle(elcs[i].x, elcs[i].y, elcs[i].R);
	}
	FlushBatchDraw();
}

int main()
{
	srand((unsigned int)time(NULL));
	startup();
	show();
	while (1)
	{
		update();
		show();
		Sleep(30);
	}
	return 0;
}