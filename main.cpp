#include <stdio.h>
#include <easyx.h>
#include <math.h>
#include <time.h>
#include <conio.h> //getch
#define GRID_WIDTH 100
#define INTERVAL 15
#define GRID_NUM 4

enum Color//枚举格子颜色
{
	zero = RGB(205, 193, 180),//0的颜色
	twoTo1 = RGB(238, 228, 218),//2的颜色
	twoTo2 = RGB(237, 224, 200),//4的颜色
	twoTo3 = RGB(242, 177, 121),//8的颜色
	twoTo4 = RGB(245, 149, 99),//16的颜色
	twoTo5 = RGB(246, 94, 59),//32的颜色
	twoTo6 = RGB(242, 177, 121),//64的颜色
	twoTo7 = RGB(237, 204, 97),//128的颜色
	twoTo8 = RGB(255, 0, 128),//256的颜色
	twoTo9 = RGB(145, 0, 72),//512的颜色
	twoTo10 = RGB(242, 17, 158),//1024的颜色
	twoTo11 = RGB(187, 173, 160),//2048的颜色
	back = RGB(187, 173, 160)//背景颜色
};

Color colors[13] = { zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11 };
int num[12] = { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int map[GRID_NUM][GRID_NUM];
//= { 1024, 512, 8, 4, 2 };//全局变量自动初始化为0
POINT pos[GRID_NUM][GRID_NUM];//为了方便先保存每个格子的左上角坐标
bool flag = false;
int rand2Or4()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
//suijishufangrushuzuzhongjian
void createNumber(){
	while (true){
		//baozhengchenggong,panduanyuanlaiyoumeiyoushuzu
		int r = rand() % GRID_NUM;
		int c = rand() % GRID_NUM;
		if (map[r][c] == 0){
			map[r][c] = rand2Or4();
			break;
		}
	}
}
void moveUp()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < GRID_NUM; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					temp++;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}
					temp++;
				}
			}
		}
	}
}


void moveDown()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = GRID_NUM-1;
		for (int begin = GRID_NUM-2; begin>=0; begin--)//zuoweilie
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] *=2;
					map[begin][i] = 0;
					temp--;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
					temp--;
				}
			}
		}
	}
}

void moveleft()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < GRID_NUM; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
					temp++;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp++;
				}
			}
		}
	}
}


void moveright()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = GRID_NUM - 1;
		for (int begin = GRID_NUM - 2; begin >= 0; begin--)//zuoweilie
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] *= 2;
					map[i][begin] = 0;
					temp--;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp--;
				}
			}
		}
	}
}
/*
void moveleft()
{
	for (int i = 0; i<GRID_NUM; i++)
	{
		int temp = 0;
		for (int begin = 1; begin<GRID_NUM; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp + 1] += map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("left\n");
}
//右移
void moveright()
{
	for (int i = 0; i<GRID_NUM; i++)
	{
		int temp = GRID_NUM - 1;
		for (int begin = GRID_NUM - 1; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp - 1] += map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("right\n");
}
*/
void KeyEvent(){//72up80down75left77right
	int key = _getch();
	switch (key)
	{
	case 72:
		moveUp();
		createNumber();
		break;
	case 80:
		moveDown();
		createNumber();
		break;
	case 75:
		moveleft();
		createNumber();
		break;
	case 77:
		moveright();
		createNumber();
		break;
	}
}

void GameJude()
{
	if (flag)
	{
		createNumber();
		flag = false;
	}
}
void init(){
	createNumber();
	createNumber();
	createNumber();
	createNumber();
	createNumber();
	createNumber();
	createNumber();
	createNumber();
}
void draw()
{
//绘制格子
	for (int r = 0; r < GRID_NUM; r++)
	{
		for (int c = 0; c < GRID_NUM; c++)
		{
			int x = c*GRID_WIDTH + (c + 1)*INTERVAL;
			int y = r*GRID_WIDTH + (r + 1)*INTERVAL;
			int index=log2(float(map[r][c])); //colorsyansexiabiao
			setfillcolor(colors[index]);
			//转化成两面，显示出来
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH,10,10);
			if (map[r][c] != 0){
				settextstyle(50, 0, "楷体");
				char str[5] = { 0 };
				sprintf(str, "%d", map[r][c]);
				int horspace = (GRID_WIDTH - textwidth(str)) / 2;
				int vercspace = (GRID_WIDTH - textheight(str)) / 2;
				outtextxy(x + horspace, y + vercspace, str);
			}
		}
	}

}

int main(){
//draw();
	initgraph(GRID_NUM*GRID_WIDTH + (GRID_NUM + 1)*INTERVAL, GRID_NUM*GRID_WIDTH + (GRID_NUM + 1)*INTERVAL, EW_SHOWCONSOLE);
	setbkcolor(RGB(187,173,160));
	cleardevice();
	//设置背景模式
	setbkmode(TRANSPARENT);
	//suijishuzhongzi
	srand(time(NULL));
	init();
	while (true)
	{

		draw();
		KeyEvent();
		GameJude();
	}
	getchar();
	return 0;
}