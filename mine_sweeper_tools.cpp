/* XingYuan */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <cctype>
#include <ctime>
#include "mine_sweeper.h"

using namespace std;

static unsigned long long next_seed = 1;

int my_rand() {
    next_seed = next_seed * 1103515245 + 12345;
    return (unsigned int)(next_seed / 65536) % 32768;
}

void to_be_continued(const char* prompt, const int X, const int Y) {
    cct_setcolor();
    cct_gotoxy(X, Y);
    if (prompt)
        cout << prompt << "，按回车键继续...";
    else 
        cout << "按回车键继续...";
    while (_getch() != '\r')
        ;
    cout << endl;
}

void InitGame(MineGame& game, int level) {
    if (next_seed == 1)
        next_seed = (unsigned long long)time(0);
    switch (level) {
        case 1:
            game.rows = LEVEL_1_ROW;
            game.cols = LEVEL_1_COL;
            game.mineNum = LEVEL_1_MINE;
            break;
        case 2: 
            game.rows = LEVEL_2_ROW;
            game.cols = LEVEL_2_COL;
            game.mineNum = LEVEL_2_MINE; 
            break;
        case 3:
            game.rows = LEVEL_3_ROW;
            game.cols = LEVEL_3_COL; 
            game.mineNum = LEVEL_3_MINE;
            break;
        default: 
            game.rows = LEVEL_1_ROW;
            game.cols = LEVEL_1_COL;
            game.mineNum = LEVEL_1_MINE; 
            break;
    }
    for (int i = 0; i < game.rows; i++) {
        for (int j = 0; j < game.cols; j++) {
            game.map[i][j] = CELL_EMPTY;
            game.mask[i][j] = MASK_COVERED;
        }
    }
}

void PlaceMines(MineGame& game) {
    for (int i = 0; i < game.rows; i++)
        for (int j = 0; j < game.cols; j++)
            game.map[i][j] = CELL_EMPTY;
    int count = 0;
    while (count < game.mineNum) {
        int r = my_rand() % game.rows;
        int c = my_rand() % game.cols;
        if (game.map[r][c] != CELL_MINE) {
            game.map[r][c] = CELL_MINE;
            count++;
        }
    }
}

void CalcNumbers(MineGame& game) {
    for (int i = 0; i < game.rows; i++) {
        for (int j = 0; j < game.cols; j++) {
            if (game.map[i][j] == CELL_MINE)
                continue;
            int n = 0;
            for (int r = i - 1; r <= i + 1; r++) {
                for (int c = j - 1; c <= j + 1; c++) {
                    if (r >= 0 && r < game.rows && c >= 0 && c < game.cols)
                        if (game.map[r][c] == CELL_MINE)
                            n++;
                }
            }
            game.map[i][j] = n;
        }
    }
}

void PlaceMinesSafe(MineGame& game, int safeR, int safeC) {
    while (true) {
        PlaceMines(game);
        CalcNumbers(game);
        if (game.map[safeR][safeC] == 0) 
            break;
    }
}

void ExpandArea(MineGame& game, int r, int c) {
    if (r < 0 || r >= game.rows || c < 0 || c >= game.cols)
        return;
    if (game.mask[r][c] == MASK_OPEN)
        return;
    game.mask[r][c] = MASK_OPEN;
    if (game.map[r][c] == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx != 0 || dy != 0)
                    ExpandArea(game, r + dx, c + dy);
            }
        }
    }
}

void PrintInternalMap(const MineGame& game) {
    cout << "内部数组：" << endl;
    cout << "  |";
    for (int j = 0; j < game.cols; j++) {
        if (j < 9)
            cout << (j + 1) << " ";
        else 
            cout << (char)('a' + (j - 9)) << " ";
    }
    cout << endl << "--+";
    for (int j = 0; j < game.cols; j++)
        cout << "--";
    cout << endl;
    for (int i = 0; i < game.rows; i++) {
        cout << (char)('A' + i) << " |";
        for (int j = 0; j < game.cols; j++) {
            if (game.map[i][j] == CELL_MINE)
                cout << "* ";
            else 
                cout << game.map[i][j] << " ";
        }
        cout << endl;
    }
}

void PrintMaskedMap(const MineGame& game, bool highlightOpen) {
    cout << "  |";
    for (int j = 0; j < game.cols; j++) {
        if (j < 9) 
            cout << (j + 1) << " ";
        else
            cout << (char)('a' + (j - 9)) << " ";
    }
    cout << endl << "--+";
    for (int j = 0; j < game.cols; j++)
        cout << "--";
    cout << endl;
    for (int i = 0; i < game.rows; i++) {
        cout << (char)('A' + i) << " |";
        for (int j = 0; j < game.cols; j++) {
            if (game.mask[i][j] == MASK_COVERED) {
                cct_setcolor(); 
                cout << "X ";
            }
            else if (game.mask[i][j] == MASK_FLAG) {
                cct_setcolor(COLOR_RED, COLOR_YELLOW);
                cout << "F "; 
                cct_setcolor();
            }
            else {
                int val = game.map[i][j];
                if (highlightOpen) {
                    int color = COLOR_BLACK;
                    switch (val) {
                        case 1:
                            color = COLOR_BLUE; 
                            break;
                        case 2:
                            color = COLOR_GREEN; 
                            break;
                        case 3:
                            color = COLOR_RED;
                            break;
                        case 4:
                            color = COLOR_CYAN;
                            break;
                        case 5: 
                            color = COLOR_PINK;
                            break;
                        case 6:
                            color = COLOR_YELLOW;
                            break;
                        case 7:
                            color = COLOR_HBLACK;
                            break;
                        case 8:
                            color = COLOR_HWHITE;
                            break;
                        case -1: 
                            color = COLOR_HRED;
                            break;
                        default: 
                            color = COLOR_BLACK; 
                            break;
                    }
                    cct_setcolor(COLOR_WHITE, color);
                    if (val == -1) 
                        cout << "* ";
                    else if (val == 0) 
                        cout << "  ";
                    else 
                        cout << val << " ";
                    cct_setcolor();
                }
                else {
                    if (val == -1) 
                        cout << "* ";
                    else if (val == 0)
                        cout << "  ";
                    else 
                        cout << val << " ";
                }
            }
        }
        cout << endl;
    }
}

bool ParseInput(const char* input, int& r, int& c) {
    if (!input || strlen(input) < 2)
        return false;
    if (input[0] < 'A' || input[0] > 'Z')
        return false;
    r = input[0] - 'A';
    if (isdigit(input[1]))
        c = input[1] - '1';
    else if (islower(input[1]))
        c = input[1] - 'a' + 9;
    else 
        return false;
    return true;
}

bool CheckWin(const MineGame& game) {
    for (int i = 0; i < game.rows; i++)
        for (int j = 0; j < game.cols; j++)
            if (game.map[i][j] != CELL_MINE && game.mask[i][j] != MASK_OPEN) 
                return false;
    return true;
}