#define _CRT_SECURE_NO_WARNINGS
#include "game.h"


void game()
{
	//�����������飬һ�����ס�һ����ʾ��
	char mine[ROWS][COLS];//�����
	char show[ROWS][COLS];//��ʾ
	//��ʼ���������飬��������
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//��ӡ��ʾ����
	//Display(mine,ROW,COL);
	Display(show,ROW,COL);
	//������
	LayMine(mine, ROW, COL);
	//Display(mine,ROW,COL);
	//�Ų���
	ScreenMine(mine, show, ROW, COL);
}

int main()
{
	int num1;
	srand((unsigned int)time(NULL));//srand����������ӣ�time�õ�����ÿ�����е�ʱ��
	do//ѡ������Ϸ�����˳�
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