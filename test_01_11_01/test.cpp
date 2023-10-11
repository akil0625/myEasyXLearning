#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
// 盘子的个数，对应盘子的大小序号，从1到DISHNUM
# define DISHNUM 6
struct Pillar // 柱子结构体
{
	int dishesNum; // 当前柱子上的盘子个数
	// 先用数组存储当前柱子上，所有的盘子序号，从上到下依次存储
	int dishes[DISHNUM];
	int isSelected; // 选中状态 0 没有选中，1 选中
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
		pillars[i].isSelected = 0; // 开始柱子都没有选中
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
		if (pillars[i].isSelected == 0) // 柱子未选中状态，绘制为白色
			setfillcolor(WHITE);
		if (pillars[i].isSelected == 1) // 柱子选中状态，绘制为红色
			setfillcolor(RED);
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
	outtextxy(40, 10, _T("通过鼠标点击，把最左边柱子上的盘子，移到最右边柱子上"));
	outtextxy(40, 50, _T("每次只能移动一个盘子，并且大盘子必须在小盘子下面"));
	TCHAR s[20]; // 定义字符串数组
	swprintf_s(s, _T("你已经移动了：%d次盘子"), moveTime); // 转换为字符串
	outtextxy(40, 90, s);
	if (isWin)
		outtextxy(40, 140, _T("恭喜你，游戏胜利！"));
	FlushBatchDraw(); // 批量绘制
}
void update()  // 更新
{
	MOUSEMSG m;		 // 定义鼠标消息
	int selectPillarID; // 被鼠标点击区域的柱子序号
	if (MouseHit())   // 如果有鼠标消息
	{
		m = GetMouseMsg();  // 获得鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN) // 如果按下鼠标左键
		{
			if (m.x < windowWidth / 3) // 点击的是最左边的0号柱子
				selectPillarID = 0;
			else if (m.x > windowWidth * 2 / 3) // 点击的是最右边的2号柱子
				selectPillarID = 2;
			else // 点击的是中间的1号柱子
				selectPillarID = 1;
			// 下面要开始分情况讨论
			// 如果当前柱子是已选中状态，又点击了一次当前柱子，表示取消当前柱子的选中状态，并返回
			if (pillars[selectPillarID].isSelected == 1)
			{
				pillars[selectPillarID].isSelected = 0;
				return;
			}
			else if (pillars[0].isSelected + pillars[1].isSelected + pillars[2].isSelected == 0)
			{
				// 如果当前柱子是未选中状态，并且没有其他柱子被选中，则将当前柱子设为已选中
				if (pillars[selectPillarID].dishesNum > 0) // 并且当前柱子上有盘子
					pillars[selectPillarID].isSelected = 1;
				return;
			}
			else
			{
				// 如果当前柱子是未选中状态，并且之前有其他一个柱子已被选中，首先获得原始柱子序号
				int sourcePillarID;
				for (sourcePillarID = 0; sourcePillarID < 3; sourcePillarID++)
				{
					if (pillars[sourcePillarID].isSelected == 1)
						break;
				}
				// 判断能否移动：目标盘子上为空，或者
				// 原始柱子最上面一个盘子，比目标盘子最上面一个盘子小
				if (pillars[selectPillarID].dishesNum == 0 ||
					pillars[sourcePillarID].dishes[0] < pillars[selectPillarID].dishes[0])
				{
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
				}
				// 无论是否可以移动，之后都把两个柱子的状态设为未选中状态
				pillars[sourcePillarID].isSelected = 0;
				pillars[selectPillarID].isSelected = 0;
			}
		}
	}
}

int main() //  主函数
{
	startup();  // 初始化函数，仅执行一次	
	while (1)   // 一直循环
	{
		show();  // 进行绘制
		update(); // 更新 
	}
	return 0;
}