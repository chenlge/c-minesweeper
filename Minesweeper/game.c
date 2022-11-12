#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

//打印菜单函数实现
void menu()
{
	puts("************************************");
	puts("************************************");
	puts("*******         1.play       *******");
	puts("*******         0.exit       *******");
	puts("************************************");
	puts("************************************");
}

//初始化数组，存入数据函数实现
void InitBoard(char(*board)[COLS], int rows, int cols, char word)
{
	int i=0, j=0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = word;
		}
	}
}

//打印显示界面的函数实现
void Display(char(*board)[COLS], int row, int col)
{
	int i=0, j=0;
	puts("---------------Minesweeper game----------------");
	printf("%d", i);
	for (i = 1; i <= row; i++)
	{
		printf("  %d  ", i);
	}
	printf("\n\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d", i);
		for (j = 1; j <= col; j++)
		{
			printf("  %c  ", board[i][j]);
		}
		puts("\n");
	}
	puts("---------------Minesweeper game----------------");
}

//布置雷的函数实现，用函数rand来生成伪随机数，以此来实现雷的随机存放坐标
void LayMine(char(*board)[COLS], int row, int col)
{
	int i=0, j=0, count=0;
	while (count != easy)//循环生成easy个雷结束
	{
		i = 1 + rand() % 9;
		j = 1 + rand() * 9 / (RAND_MAX + 1);
		if (board[i][j] == '0')
		{
			board[i][j] = '1';
			count++;
		}
	}
}

//此递归函数实现坐标为非雷时show数组选择坐标的打印，打印值为3*3范围的雷个数，并且添加标记取消功能。
void MineNumbers(char(*boardMine)[COLS], char(*boardShow)[COLS], int i, int j,int row,int col)
{
	int m = 0, n = 0, count = 0;
	for (m = i - 1; m <= i + 1; m++)//范围雷个数
	{
		for (n = j - 1; n <= j + 1; n++)
		{
			if (boardMine[m][n] == '1')
				count++;
		}
	}
	if (boardShow[i][j] == '*')//判断坐标是否被标记，如果被标记则取消，反之打印坐标
	{
		boardShow[i][j] = count + '0';
		if (count == 0)//3*3范围坐标雷个数为0时打印周围一片
		{
			boardMine[i][j] = '#';//防止递归死循环，将需要全部打印3*3范围坐标的坐标设置其他字符
			for (m = i - 1; m <= i + 1; m++)//3*3范围循环
			{
				for (n = j - 1; n <= j + 1; n++)
				{
					if (m >= 1 && m <= row && n >= 1 && n <= col && boardMine[m][n] == '0'&&boardShow[m][n]=='*')//设置递归条件
						MineNumbers(boardMine, boardShow, m, n, row, col);//递归实现坐标的范围坐标3*3雷的数目为0的周边打印
				}
			}
		}
	}
	else
	{
		boardShow[i][j] = '*';
	}
}

//排查雷的函数实现
void ScreenMine(char(*boardMine)[COLS], char(*boardShow)[COLS], int row, int col)
{
	while (1)//循环实现排查
	{
		int i = 0, j = 0, count = 0, num = 0, sum = 0;
		puts("please select 1. Minesweeping 2. Mark->");
		scanf("%d", &num);
		if (num == 1)//选择排查雷坐标或者标记坐标
		{
			puts("please enter the coordinates to be checked->");
			scanf("%d %d", &i, &j);
			if (i >= 1 && i <= row && j >= 1 && j <= col)//坐标范围
			{
				if (boardMine[i][j] == '1')//遇到雷游戏失败
				{
					if (boardShow[i][j] == '?')//遇到标记取消
					{
						boardShow[i][j] = '*';
						Display(boardShow, row, col);
					}
					else//游戏失败
					{
						puts("Sorry, you were killed by explosion");
						Display(boardMine, row, col);//失败打印mine界面
						break;
					}
				}
				else//排查雷
				{
					MineNumbers(boardMine, boardShow, i, j, row, col);
					Display(boardShow, row, col);
					/*Display(boardMine, row, col);*/
					for (i = 1; i <= 9; i++)//统计剩余未排查的数目
					{
						for (j = 1; j <= 9; j++)
						{
							if (boardShow[i][j] == '*')
							{
								count++;
							}
						}
					}
					if (count == easy)//界面未排查数目与雷的数目相等，赢得游戏
					{
						puts("Congratulations, cleared all mines!");
						break;
					}
				}
			}
			else//坐标错误，提醒并重新循环
			{
				puts("Corrdinate error,please re-enter->");
			}
		}
		else
			if (num == 2)//标记怀疑是雷的坐标
			{
				for (i = 1; i <= 9; i++)//统计已标记数目
				{
					for (j = 1; j <= 9; j++)
					{
						if (boardShow[i][j] == '?')
						{
							sum++;
						}
					}
				}
				puts("please enter the coordinates to be marked->");
				scanf("%d %d", &i, &j);
				if (i >= 1 && i <= row && j >= 1 && j <= col)//标记范围规定
				{
					if (boardShow[i][j] == '*')//坐标未被标记则标记
					{
						if (sum == 10)//标记满了,提示并打印show界面
						{
							puts("Mark is full!");
							Display(boardShow, row, col);
						}
						else//标记未满，继续标记
						{
							boardShow[i][j] = '?';
							Display(boardShow, row, col);
						}
					}
					else//已被标记则还原
						if (boardShow[i][j] == '?')
						{
							boardShow[i][j] = '*';
							Display(boardShow, row, col);
						}
				}
				else//坐标错误提示
				{
					puts("Corrdinate error,please re-enter->");
				}
			}
			else//坐标错误提示
			{
				puts("Wrong selection, please re-enter!");
			}
	}
}









