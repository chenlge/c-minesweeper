#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define easy 10

//打印菜单栏
void menu();

//初始化棋盘，存入数据；
void InitBoard(char(*board)[COLS], int rows, int cols, char word);

//打印显示界面
void Display(char(*board)[COLS], int row, int col);

//布置雷
void LayMine(char(*board)[COLS], int row, int col);

//排查雷
void ScreenMine(char(*boardMine)[COLS],char(*boardShow)[COLS], int row, int col);