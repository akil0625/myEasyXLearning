#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctime>

#define PI 3.14159
#define q2 1.0621*pow(10,-16)
#define k 8.9880*pow(10,9)
#define mproton 1.6726*pow(10,-27)

#define protonnum 100

class Proton
{
public:
	long double m_X;
	long double m_Y;
	long double m_V;
	long double m_Vd;
	long double m_Vx;
	long double m_Vy;
	long double m_A;
	long double m_Ad;
	long double m_Ax;
	long double m_Ay;
	long double m_F;
	long double m_Fd;
	long double m_Fx;
	long double m_Fy;
	Proton()
	{
		m_X = rand() % 6 / pow(10, -11);
		m_Y = rand() % 6 / pow(10, -11);
		m_V = rand()%340000+340000;
		m_Vd = rand()%22;
		m_Vx = m_V * cos(m_Vd);
		m_Vy = m_V * sin(m_Vd);
		m_A = rand();
		m_Ad = rand()%22;
		m_Ax = rand();
		m_Ay = rand();
		m_F = rand();
		m_Fd = rand()%22;
		m_Fx = rand();
		m_Fy = rand();
	}
	void addv()
	{
		this->m_X += this->m_Vx;
		this->m_Y += this->m_Vy;
	}
	void adda()
	{
		this->m_Vx += this->m_Ax;
		this->m_Vy += this->m_Ay;
		this->m_V = sqrt(pow(this->m_Vx, 2) + pow(this->m_Vy, 2));
	}
	void clearf()
	{
		this->m_Fx = 0;
		this->m_Fy = 0;
	}
	void updatef(const Proton& p)
	{
		long double d = sqrt(pow(this->m_X - p.m_X, 2) + pow(this->m_Y - p.m_Y, 2));
		long double F = k * q2 / d / d;
		long double fd = atan2(this->m_Y - p.m_Y,this->m_X - p.m_X);//可以用来决定是斥力还是引力,指向减数
		this->m_Fx += F * cos(fd);
		this->m_Fy += F * sin(fd);
		this->m_F = sqrt(pow(this->m_Fx, 2) + pow(this->m_Fy, 2));
		this->m_Fd = atan2(this->m_Fy, this->m_Fx);
	}
	void updatea()
	{
		this->m_A = this->m_F / mproton;
		this->m_Ad = this->m_Fd;
		this->m_Ax = this->m_A * cos(this->m_Fd);
		this->m_Ay = this->m_A * sin(this->m_Fd);
	}
};


int main()
{
	srand((unsigned int)time(NULL));

	Proton proton[protonnum];
	int i = 100;
	while (i)
	{
		for (int i = 0; i < protonnum; i++)
		{
			proton[i].clearf();
			for (int j = 0; j < protonnum; j++)
			{
				if (i == j)
					continue;
				proton[i].updatef(proton[j]);
			}
			proton[i].updatea();
			proton[i].adda();
			proton[i].addv();
			printf("X = %lf Y = %lf\n", proton[i].m_Ax, proton[i].m_Ay);
		}
		printf("\n");
		i--;
	}
	system("pause");
	return 0;
}