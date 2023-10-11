#include<graphics.h>
#include<conio.h>
#include<cmath>


#define WIDTH 1440
#define HEIGHT 900


class point
{
public:
	double x, y, z;
	point(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	/*point(point& p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}*/
};


class transmat
{
public:
	double theta;
	double phi;
	double r;
private:
	double a;
	double b;
	double c;
	double Tx;
	double Ty;
	double Tz;
	double sintheta;
	double costheta;
	double sinphi;
	double cosphi;
	double mat[3][3];
public:
	void setvalue()
	{
		a = r * sin(theta) * cos(phi);
		b = r * sin(theta) * sin(phi);
		c = r * cos(theta);
		Tx = 0;
		Ty = 0;
		Tz = r;
		sintheta = sin(theta);
		costheta = cos(theta);
		sinphi = sin(phi);
		cosphi = cos(phi);
		mat[0][0] = -sinphi;
		mat[0][1] = cosphi;
		mat[0][2] = 0;
		mat[1][0] = cosphi * costheta;
		mat[1][1] = sinphi * costheta;
		mat[1][2] = -sintheta;
		mat[2][0] = -sintheta * cosphi;
		mat[2][1] = -sintheta * sinphi;
		mat[2][2] = -sintheta;
	}
	transmat()
	{
		theta = 0;
		phi = 0;
		r = 2;
		setvalue();
	}
	transmat(double theta, double phi, double r)
	{
		this->theta = theta;
		this->phi = phi;
		this->r = r;
		setvalue();
	}
	point trans(point p)
	{
		double xs, ys, zs;
		point pout(0, 0, 0);
		xs = Tx + mat[0][0] * p.x + mat[0][1] * p.y;
		ys = Ty + mat[1][0] * p.x + mat[1][1] * p.y + mat[1][2] * p.z;
		zs = Tz + mat[2][0] * p.x + mat[2][1] * p.y + mat[2][2] * p.z;
		pout.x = 200 * xs + WIDTH / 2;
		pout.y = 200 * ys + HEIGHT / 2;
		return pout;
	}
};


class cubic
{
public:
	point p1, p2, p3, p4, p5, p6, p7, p8;
	cubic() :p1(0, 0, 0), p2(1, 0, 0), p3(0, 1, 0), p4(0, 0, 1), p5(1, 0, 1), p6(0, 1, 1), p7(1, 1, 0), p8(1, 1, 1) {}
	void draw(transmat tm)
	{
		point pout1(tm.trans(p1));
		point pout2(tm.trans(p2));
		point pout3(tm.trans(p3));
		point pout4(tm.trans(p4));
		point pout5(tm.trans(p5));
		point pout6(tm.trans(p6));
		point pout7(tm.trans(p7));
		point pout8(tm.trans(p8));
		setlinecolor(RED);
		drawline(pout1, pout2);
		setlinecolor(GREEN);
		drawline(pout1, pout3);
		setlinecolor(BLUE);
		drawline(pout1, pout4);
		setlinecolor(YELLOW);
		drawline(pout2, pout5);
		drawline(pout4, pout5);
		drawline(pout4, pout6);
		drawline(pout3, pout6);
		drawline(pout2, pout7);
		drawline(pout3, pout7);
		drawline(pout5, pout8);
		drawline(pout6, pout8);
		drawline(pout7, pout8);
	}
private:
	void drawline(point p1, point p2)
	{
		line(p1.x, p1.y, p2.x, p2.y);
	}
};


int main()
{
	transmat tm;
	cubic c;
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	setcolor(RED);
	MOUSEMSG m;
	tm.setvalue();
	cleardevice();
	c.draw(tm);
	FlushBatchDraw();
	int mousex, mousey;
	bool leftclick = false;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			leftclick = true;
			mousex = m.x;
			mousey = m.y;
		}
		else if (m.uMsg == WM_LBUTTONUP)
		{
			leftclick = false;
		}
		else if (m.uMsg == WM_RBUTTONUP)
		{
			closegraph();
			return 0;
		}
		else if (leftclick && m.uMsg == WM_MOUSEMOVE)
		{
			short dx = m.x - mousex;
			short dy = m.y - mousey;
			tm.phi -= dx / 10000.0;
			if (tm.theta - dy / 10000.0 < 0)
				tm.theta = 0;
			else if (tm.theta - dy / 10000.0 > 3.14)
				tm.theta = 3.14;
			else
				tm.theta -= dy / 10000.0;
			tm.setvalue();
			cleardevice();
			c.draw(tm);
			FlushBatchDraw();
		}
		//Sleep(10);
	}
	closegraph();
	return 0;
}