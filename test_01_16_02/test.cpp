#include <graphics.h>  

#include <conio.h>

#include <stdio.h>



// 盘子的个数，对应盘子的大小序号，从1到DISHNUM

# define DISHNUM 6
#define SLEEPTIME 1000



struct Pillar // 柱子结构体

{

	int dishesNum; // 当前柱子上的盘子个数

	// 先用数组存储当前柱子上，所有的盘子序号，从上到下依次存储

	int dishes[DISHNUM];

};



// 全局变量定义

const int windowWidth = 1000; // 屏幕宽度

const int windowHEIGHT = 600; // 屏幕高度

const int dishHeight = windowHEIGHT / DISHNUM / 4; // 盘子的高度，所有大小盘子都一样

const int dishUnitWidth = windowHEIGHT / DISHNUM / 6; // 盘子单位数值对应的宽度

struct Pillar pillars[3];  // 定义所有的柱子数组

int isWin = 0; // 游戏是否胜利，0为否，1为是

int moveTime = 0; // 玩家移动次数



void startup()  //  初始化函数

{

	initgraph(windowWidth, windowHEIGHT);		// 新开窗口

	setbkcolor(RGB(50, 50, 50));   // 设置背景颜色

	cleardevice();    // 以背景颜色清屏

	BeginBatchDraw(); // 开始批量绘制



	for (int i = 0; i < 3; i++) // 初始化所有的柱子数据

	{

		if (i == 0) // 初始所有盘子在柱子0上

		{

			pillars[i].dishesNum = DISHNUM; // 设定柱子上的盘子个数

			for (int j = 0; j < DISHNUM; j++)

				pillars[i].dishes[j] = j + 1; // 设定柱子上的盘子序号

		}

		else

			pillars[i].dishesNum = 0; // 初始另外两个柱子上面没有盘子

	}



	setbkmode(TRANSPARENT); // 文字字体透明    

	settextcolor(YELLOW);// 设定文字颜色

	settextstyle(35, 0, _T("宋体")); // 设置文字大小、字体

}



void show()  // 绘制函数

{

	cleardevice();    // 以背景颜色清屏



	// 首先绘制三根柱子	

	int pillarWidth = 5; // 柱子的宽度

	int pillarHeight = windowHEIGHT * 2 / 3; // 柱子的高度

	for (int i = 0; i < 3; i++)

	{

		int center_x = windowWidth * (i + 1) / 4; // 当前柱子x中心坐标

		int left_x = center_x - pillarWidth;

		int right_x = center_x + pillarWidth;

		int top_y = windowHEIGHT - pillarHeight;

		int bottom_y = windowHEIGHT;

		setfillcolor(WHITE);

		fillrectangle(left_x, top_y, right_x, bottom_y);  // 绘制当前柱子矩形

	}



	// 根据pillars数组记录的信息，绘制柱子上的盘子图形

	setfillcolor(GREEN);

	for (int i = 0; i < 3; i++)

	{

		for (int j = 0; j < pillars[i].dishesNum; j++)

		{

			// 绘制当前柱子上序号为dishID的盘子信息

			int dishID = pillars[i].dishes[j]; // 当前盘子的序号，序号越大，盘子越大

			int center_x = windowWidth * (i + 1) / 4; // 同当前柱子x中心坐标一样

			int width = dishID * dishUnitWidth;

			int left_x = center_x - width;

			int right_x = center_x + width;

			int bottom_y = windowHEIGHT - (pillars[i].dishesNum - j - 1) * dishHeight;

			int top_y = bottom_y - dishHeight;

			fillrectangle(left_x, top_y, right_x, bottom_y);  // 绘制当前盘子矩形

		}

	}



	outtextxy(40, 10, _T("借助中间的柱子，把最左边柱子上的盘子，移到最右边柱子上"));

	outtextxy(40, 50, _T("每次只能移动一个盘子，并且大盘子必须在小盘子下面"));

	TCHAR s[20]; // 定义字符串数组

	swprintf_s(s, _T("已经移动了：%d次盘子"), moveTime); // 转换为字符串

	outtextxy(40, 90, s);

	if (isWin)

		outtextxy(40, 140, _T("恭喜你，游戏胜利！"));



	FlushBatchDraw(); // 批量绘制

	Sleep(SLEEPTIME);

}



void move(int sourcePillarID, int selectPillarID) // 移动盘子和绘制动画函数

{

	show();

	moveTime++; // 玩家移动次数加1



	// 把selectPillarID柱子上面的一个盘子，移动到sourcePillarID上面

	// 目标柱子上盘子个数加1

	pillars[selectPillarID].dishesNum += 1;

	// 目标柱子上，已有盘子向下，并在最上面添加一个盘子

	for (int j = pillars[selectPillarID].dishesNum - 1; j > 0; j--)

		pillars[selectPillarID].dishes[j] = pillars[selectPillarID].dishes[j - 1];

	pillars[selectPillarID].dishes[0] = pillars[sourcePillarID].dishes[0];



	// 原始柱子，所有盘子向上，最上面的一个盘子去掉，盘子个数减1

	pillars[sourcePillarID].dishesNum -= 1;

	for (int j = 0; j < pillars[sourcePillarID].dishesNum; j++)

		pillars[sourcePillarID].dishes[j] = pillars[sourcePillarID].dishes[j + 1];



	// 最右边柱子上的盘子个数达到DISHNUM，游戏胜利

	if (pillars[2].dishesNum == DISHNUM)

		isWin = 1;



	show();

}



// 汉诺塔递归函数求解

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



int main() //  主函数

{

	startup();  // 初始化函数，仅执行一次

	// 把DISHNUM个盘子，从柱子0，借助柱子1，移动到柱子2上

	hanoi(DISHNUM, 0, 1, 2);

	_getch();

	return 0;

}