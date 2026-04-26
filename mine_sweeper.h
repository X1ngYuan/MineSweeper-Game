/* XingYuan */
#pragma once
#include "cmd_console_tools.h"

#define MAX_ROW 30
#define MAX_COL 60

#define LEVEL_1_ROW 9
#define LEVEL_1_COL 9
#define LEVEL_1_MINE 10
#define LEVEL_2_ROW 16
#define LEVEL_2_COL 16
#define LEVEL_2_MINE 40
#define LEVEL_3_ROW 16
#define LEVEL_3_COL 30
#define LEVEL_3_MINE 99

#define CELL_MINE -1
#define CELL_EMPTY 0
#define MASK_COVERED 0
#define MASK_OPEN    1
#define MASK_FLAG    2

struct MineGame {
    int rows;
    int cols;
    int mineNum;
    int map[MAX_ROW][MAX_COL];
    int mask[MAX_ROW][MAX_COL];
};

void main_menu();
void to_be_continued(const char* prompt, const int X = 0, const int Y = 22);
int my_rand();
void InitGame(MineGame& game, int level);
void PrintInternalMap(const MineGame& game);
void PrintMaskedMap(const MineGame& game, bool highlightOpen);
void PlaceMines(MineGame& game);
void PlaceMinesSafe(MineGame& game, int safeR, int safeC);
void CalcNumbers(MineGame& game);
void ExpandArea(MineGame& game, int r, int c);
bool ParseInput(const char* input, int& r, int& c);
bool CheckWin(const MineGame& game);

void SubProblem_1();
void SubProblem_2();
void SubProblem_3();
void SubProblem_4();
void SubProblem_5();
void SubProblem_6();
void SubProblem_7();
void SubProblem_8();
void SubProblem_9();