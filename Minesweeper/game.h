#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define easy 10

//��ӡ�˵���
void menu();

//��ʼ�����̣��������ݣ�
void InitBoard(char(*board)[COLS], int rows, int cols, char word);

//��ӡ��ʾ����
void Display(char(*board)[COLS], int row, int col);

//������
void LayMine(char(*board)[COLS], int row, int col);

//�Ų���
void ScreenMine(char(*boardMine)[COLS],char(*boardShow)[COLS], int row, int col);