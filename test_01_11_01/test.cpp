#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
// ���ӵĸ�������Ӧ���ӵĴ�С��ţ���1��DISHNUM
# define DISHNUM 6
struct Pillar // ���ӽṹ��
{
	int dishesNum; // ��ǰ�����ϵ����Ӹ���
	// ��������洢��ǰ�����ϣ����е�������ţ����ϵ������δ洢
	int dishes[DISHNUM];
	int isSelected; // ѡ��״̬ 0 û��ѡ�У�1 ѡ��
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
		pillars[i].isSelected = 0; // ��ʼ���Ӷ�û��ѡ��
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
		if (pillars[i].isSelected == 0) // ����δѡ��״̬������Ϊ��ɫ
			setfillcolor(WHITE);
		if (pillars[i].isSelected == 1) // ����ѡ��״̬������Ϊ��ɫ
			setfillcolor(RED);
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
	outtextxy(40, 10, _T("ͨ���������������������ϵ����ӣ��Ƶ����ұ�������"));
	outtextxy(40, 50, _T("ÿ��ֻ���ƶ�һ�����ӣ����Ҵ����ӱ�����С��������"));
	TCHAR s[20]; // �����ַ�������
	swprintf_s(s, _T("���Ѿ��ƶ��ˣ�%d������"), moveTime); // ת��Ϊ�ַ���
	outtextxy(40, 90, s);
	if (isWin)
		outtextxy(40, 140, _T("��ϲ�㣬��Ϸʤ����"));
	FlushBatchDraw(); // ��������
}
void update()  // ����
{
	MOUSEMSG m;		 // ���������Ϣ
	int selectPillarID; // �������������������
	if (MouseHit())   // ����������Ϣ
	{
		m = GetMouseMsg();  // ��������Ϣ
		if (m.uMsg == WM_LBUTTONDOWN) // �������������
		{
			if (m.x < windowWidth / 3) // �����������ߵ�0������
				selectPillarID = 0;
			else if (m.x > windowWidth * 2 / 3) // ����������ұߵ�2������
				selectPillarID = 2;
			else // ��������м��1������
				selectPillarID = 1;
			// ����Ҫ��ʼ���������
			// �����ǰ��������ѡ��״̬���ֵ����һ�ε�ǰ���ӣ���ʾȡ����ǰ���ӵ�ѡ��״̬��������
			if (pillars[selectPillarID].isSelected == 1)
			{
				pillars[selectPillarID].isSelected = 0;
				return;
			}
			else if (pillars[0].isSelected + pillars[1].isSelected + pillars[2].isSelected == 0)
			{
				// �����ǰ������δѡ��״̬������û���������ӱ�ѡ�У��򽫵�ǰ������Ϊ��ѡ��
				if (pillars[selectPillarID].dishesNum > 0) // ���ҵ�ǰ������������
					pillars[selectPillarID].isSelected = 1;
				return;
			}
			else
			{
				// �����ǰ������δѡ��״̬������֮ǰ������һ�������ѱ�ѡ�У����Ȼ��ԭʼ�������
				int sourcePillarID;
				for (sourcePillarID = 0; sourcePillarID < 3; sourcePillarID++)
				{
					if (pillars[sourcePillarID].isSelected == 1)
						break;
				}
				// �ж��ܷ��ƶ���Ŀ��������Ϊ�գ�����
				// ԭʼ����������һ�����ӣ���Ŀ������������һ������С
				if (pillars[selectPillarID].dishesNum == 0 ||
					pillars[sourcePillarID].dishes[0] < pillars[selectPillarID].dishes[0])
				{
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
				}
				// �����Ƿ�����ƶ���֮�󶼰��������ӵ�״̬��Ϊδѡ��״̬
				pillars[sourcePillarID].isSelected = 0;
				pillars[selectPillarID].isSelected = 0;
			}
		}
	}
}

int main() //  ������
{
	startup();  // ��ʼ����������ִ��һ��	
	while (1)   // һֱѭ��
	{
		show();  // ���л���
		update(); // ���� 
	}
	return 0;
}