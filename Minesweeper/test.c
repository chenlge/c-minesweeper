#define _CRT_SECURE_NO_WARNINGS
#include "game.h"


void game()
{
	//创建两个数组，一个放雷、一个显示。
	char mine[ROWS][COLS];//存放雷
	char show[ROWS][COLS];//显示
	//初始化两个数组，存入数据
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//打印显示界面
	//Display(mine,ROW,COL);
	Display(show,ROW,COL);
	//布置雷
	LayMine(mine, ROW, COL);
	//Display(mine,ROW,COL);
	//排查雷
	ScreenMine(mine, show, ROW, COL);
}

int main()
{
	int num1;
	srand((unsigned int)time(NULL));//srand设置随机种子，time得到程序每次运行的时间
	do//选择玩游戏或者退出
	{
		menu();
		puts("Please select->");
		scanf("%d", &num1);
		switch (num1)
		{
		case 1:
			game();
			break;
		case 0:
			puts("Game exited!");
			break;
		default:
			puts("Error,please re-enter!");
			break;
		}
	}while (num1);
	return 0;
}