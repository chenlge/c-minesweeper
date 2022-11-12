#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

//��ӡ�˵�����ʵ��
void menu()
{
	puts("************************************");
	puts("************************************");
	puts("*******         1.play       *******");
	puts("*******         0.exit       *******");
	puts("************************************");
	puts("************************************");
}

//��ʼ�����飬�������ݺ���ʵ��
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

//��ӡ��ʾ����ĺ���ʵ��
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

//�����׵ĺ���ʵ�֣��ú���rand������α��������Դ���ʵ���׵�����������
void LayMine(char(*board)[COLS], int row, int col)
{
	int i=0, j=0, count=0;
	while (count != easy)//ѭ������easy���׽���
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

//�˵ݹ麯��ʵ������Ϊ����ʱshow����ѡ������Ĵ�ӡ����ӡֵΪ3*3��Χ���׸�����������ӱ��ȡ�����ܡ�
void MineNumbers(char(*boardMine)[COLS], char(*boardShow)[COLS], int i, int j,int row,int col)
{
	int m = 0, n = 0, count = 0;
	for (m = i - 1; m <= i + 1; m++)//��Χ�׸���
	{
		for (n = j - 1; n <= j + 1; n++)
		{
			if (boardMine[m][n] == '1')
				count++;
		}
	}
	if (boardShow[i][j] == '*')//�ж������Ƿ񱻱�ǣ�����������ȡ������֮��ӡ����
	{
		boardShow[i][j] = count + '0';
		if (count == 0)//3*3��Χ�����׸���Ϊ0ʱ��ӡ��ΧһƬ
		{
			boardMine[i][j] = '#';//��ֹ�ݹ���ѭ��������Ҫȫ����ӡ3*3��Χ������������������ַ�
			for (m = i - 1; m <= i + 1; m++)//3*3��Χѭ��
			{
				for (n = j - 1; n <= j + 1; n++)
				{
					if (m >= 1 && m <= row && n >= 1 && n <= col && boardMine[m][n] == '0'&&boardShow[m][n]=='*')//���õݹ�����
						MineNumbers(boardMine, boardShow, m, n, row, col);//�ݹ�ʵ������ķ�Χ����3*3�׵���ĿΪ0���ܱߴ�ӡ
				}
			}
		}
	}
	else
	{
		boardShow[i][j] = '*';
	}
}

//�Ų��׵ĺ���ʵ��
void ScreenMine(char(*boardMine)[COLS], char(*boardShow)[COLS], int row, int col)
{
	while (1)//ѭ��ʵ���Ų�
	{
		int i = 0, j = 0, count = 0, num = 0, sum = 0;
		puts("please select 1. Minesweeping 2. Mark->");
		scanf("%d", &num);
		if (num == 1)//ѡ���Ų���������߱������
		{
			puts("please enter the coordinates to be checked->");
			scanf("%d %d", &i, &j);
			if (i >= 1 && i <= row && j >= 1 && j <= col)//���귶Χ
			{
				if (boardMine[i][j] == '1')//��������Ϸʧ��
				{
					if (boardShow[i][j] == '?')//�������ȡ��
					{
						boardShow[i][j] = '*';
						Display(boardShow, row, col);
					}
					else//��Ϸʧ��
					{
						puts("Sorry, you were killed by explosion");
						Display(boardMine, row, col);//ʧ�ܴ�ӡmine����
						break;
					}
				}
				else//�Ų���
				{
					MineNumbers(boardMine, boardShow, i, j, row, col);
					Display(boardShow, row, col);
					/*Display(boardMine, row, col);*/
					for (i = 1; i <= 9; i++)//ͳ��ʣ��δ�Ų����Ŀ
					{
						for (j = 1; j <= 9; j++)
						{
							if (boardShow[i][j] == '*')
							{
								count++;
							}
						}
					}
					if (count == easy)//����δ�Ų���Ŀ���׵���Ŀ��ȣ�Ӯ����Ϸ
					{
						puts("Congratulations, cleared all mines!");
						break;
					}
				}
			}
			else//����������Ѳ�����ѭ��
			{
				puts("Corrdinate error,please re-enter->");
			}
		}
		else
			if (num == 2)//��ǻ������׵�����
			{
				for (i = 1; i <= 9; i++)//ͳ���ѱ����Ŀ
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
				if (i >= 1 && i <= row && j >= 1 && j <= col)//��Ƿ�Χ�涨
				{
					if (boardShow[i][j] == '*')//����δ���������
					{
						if (sum == 10)//�������,��ʾ����ӡshow����
						{
							puts("Mark is full!");
							Display(boardShow, row, col);
						}
						else//���δ�����������
						{
							boardShow[i][j] = '?';
							Display(boardShow, row, col);
						}
					}
					else//�ѱ������ԭ
						if (boardShow[i][j] == '?')
						{
							boardShow[i][j] = '*';
							Display(boardShow, row, col);
						}
				}
				else//���������ʾ
				{
					puts("Corrdinate error,please re-enter->");
				}
			}
			else//���������ʾ
			{
				puts("Wrong selection, please re-enter!");
			}
	}
}









