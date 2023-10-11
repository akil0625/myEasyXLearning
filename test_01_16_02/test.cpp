#include <graphics.h>  

#include <conio.h>

#include <stdio.h>



// ���ӵĸ�������Ӧ���ӵĴ�С��ţ���1��DISHNUM

# define DISHNUM 6
#define SLEEPTIME 1000



struct Pillar // ���ӽṹ��

{

	int dishesNum; // ��ǰ�����ϵ����Ӹ���

	// ��������洢��ǰ�����ϣ����е�������ţ����ϵ������δ洢

	int dishes[DISHNUM];

};



// ȫ�ֱ�������

const int windowWidth = 1000; // ��Ļ���

const int windowHEIGHT = 600; // ��Ļ�߶�

const int dishHeight = windowHEIGHT / DISHNUM / 4; // ���ӵĸ߶ȣ����д�С���Ӷ�һ��

const int dishUnitWidth = windowHEIGHT / DISHNUM / 6; // ���ӵ�λ��ֵ��Ӧ�Ŀ��

struct Pillar pillars[3];  // �������е���������

int isWin = 0; // ��Ϸ�Ƿ�ʤ����0Ϊ��1Ϊ��

int moveTime = 0; // ����ƶ�����



void startup()  //  ��ʼ������

{

	initgraph(windowWidth, windowHEIGHT);		// �¿�����

	setbkcolor(RGB(50, 50, 50));   // ���ñ�����ɫ

	cleardevice();    // �Ա�����ɫ����

	BeginBatchDraw(); // ��ʼ��������



	for (int i = 0; i < 3; i++) // ��ʼ�����е���������

	{

		if (i == 0) // ��ʼ��������������0��

		{

			pillars[i].dishesNum = DISHNUM; // �趨�����ϵ����Ӹ���

			for (int j = 0; j < DISHNUM; j++)

				pillars[i].dishes[j] = j + 1; // �趨�����ϵ��������

		}

		else

			pillars[i].dishesNum = 0; // ��ʼ����������������û������

	}



	setbkmode(TRANSPARENT); // ��������͸��    

	settextcolor(YELLOW);// �趨������ɫ

	settextstyle(35, 0, _T("����")); // �������ִ�С������

}



void show()  // ���ƺ���

{

	cleardevice();    // �Ա�����ɫ����



	// ���Ȼ�����������	

	int pillarWidth = 5; // ���ӵĿ��

	int pillarHeight = windowHEIGHT * 2 / 3; // ���ӵĸ߶�

	for (int i = 0; i < 3; i++)

	{

		int center_x = windowWidth * (i + 1) / 4; // ��ǰ����x��������

		int left_x = center_x - pillarWidth;

		int right_x = center_x + pillarWidth;

		int top_y = windowHEIGHT - pillarHeight;

		int bottom_y = windowHEIGHT;

		setfillcolor(WHITE);

		fillrectangle(left_x, top_y, right_x, bottom_y);  // ���Ƶ�ǰ���Ӿ���

	}



	// ����pillars�����¼����Ϣ�����������ϵ�����ͼ��

	setfillcolor(GREEN);

	for (int i = 0; i < 3; i++)

	{

		for (int j = 0; j < pillars[i].dishesNum; j++)

		{

			// ���Ƶ�ǰ���������ΪdishID��������Ϣ

			int dishID = pillars[i].dishes[j]; // ��ǰ���ӵ���ţ����Խ������Խ��

			int center_x = windowWidth * (i + 1) / 4; // ͬ��ǰ����x��������һ��

			int width = dishID * dishUnitWidth;

			int left_x = center_x - width;

			int right_x = center_x + width;

			int bottom_y = windowHEIGHT - (pillars[i].dishesNum - j - 1) * dishHeight;

			int top_y = bottom_y - dishHeight;

			fillrectangle(left_x, top_y, right_x, bottom_y);  // ���Ƶ�ǰ���Ӿ���

		}

	}



	outtextxy(40, 10, _T("�����м�����ӣ�������������ϵ����ӣ��Ƶ����ұ�������"));

	outtextxy(40, 50, _T("ÿ��ֻ���ƶ�һ�����ӣ����Ҵ����ӱ�����С��������"));

	TCHAR s[20]; // �����ַ�������

	swprintf_s(s, _T("�Ѿ��ƶ��ˣ�%d������"), moveTime); // ת��Ϊ�ַ���

	outtextxy(40, 90, s);

	if (isWin)

		outtextxy(40, 140, _T("��ϲ�㣬��Ϸʤ����"));



	FlushBatchDraw(); // ��������

	Sleep(SLEEPTIME);

}



void move(int sourcePillarID, int selectPillarID) // �ƶ����Ӻͻ��ƶ�������

{

	show();

	moveTime++; // ����ƶ�������1



	// ��selectPillarID���������һ�����ӣ��ƶ���sourcePillarID����

	// Ŀ�����������Ӹ�����1

	pillars[selectPillarID].dishesNum += 1;

	// Ŀ�������ϣ������������£��������������һ������

	for (int j = pillars[selectPillarID].dishesNum - 1; j > 0; j--)

		pillars[selectPillarID].dishes[j] = pillars[selectPillarID].dishes[j - 1];

	pillars[selectPillarID].dishes[0] = pillars[sourcePillarID].dishes[0];



	// ԭʼ���ӣ������������ϣ��������һ������ȥ�������Ӹ�����1

	pillars[sourcePillarID].dishesNum -= 1;

	for (int j = 0; j < pillars[sourcePillarID].dishesNum; j++)

		pillars[sourcePillarID].dishes[j] = pillars[sourcePillarID].dishes[j + 1];



	// ���ұ������ϵ����Ӹ����ﵽDISHNUM����Ϸʤ��

	if (pillars[2].dishesNum == DISHNUM)

		isWin = 1;



	show();

}



// ��ŵ���ݹ麯�����

void hanoi(int n, int A, int B, int C)
{
	if (n == 1)
		move(A, C);
	else
	{
		hanoi(n - 1, A, C, B);
		move(A, C);
		hanoi(n - 1, B, A, C);
	}
}



int main() //  ������

{

	startup();  // ��ʼ����������ִ��һ��

	// ��DISHNUM�����ӣ�������0����������1���ƶ�������2��

	hanoi(DISHNUM, 0, 1, 2);

	_getch();

	return 0;

}