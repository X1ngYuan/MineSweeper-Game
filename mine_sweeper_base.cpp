/* XingYuan */
#include <iostream>
#include <cstring>
#include <ctime>
#include "mine_sweeper.h"

using namespace std;

void SubProblem_1() {
    int level;
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）：";
    cin >> level;
    cct_cls();
    MineGame game;
    InitGame(game, level);
    PlaceMines(game);
    CalcNumbers(game);
    PrintInternalMap(game);
    to_be_continued(NULL);
}

void SubProblem_2() {
    int level;
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）：";
    cin >> level;
    cct_cls();
    MineGame game;
    InitGame(game, level);
    cout << "内部数组：" << endl;
    PrintMaskedMap(game, false);
    char input[32];
    int r, c;
    while (true) {
        cout << endl << "输入纵横坐标（如Gf、A1，按q退出）：";
        cin >> input;
        if (input[0] == 'q' || input[0] == 'Q')
            return;
        if (ParseInput(input, r, c)) {
            if (r >= 0 && r < game.rows && c >= 0 && c < game.cols) 
                break;
        }
        cout << "坐标无效，请重新输入！" << endl;
    }
    PlaceMinesSafe(game, r, c);
    ExpandArea(game, r, c);
    cct_cls();
    cout << "点开后的数组：" << endl;
    PrintMaskedMap(game, true);
    to_be_continued(NULL);
}

void SubProblem_3() {
    int level;
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）：";
    cin >> level;
    cct_cls();
    MineGame game;
    InitGame(game, level);
    bool firstClick = true;
    while (true) {
        cct_cls();
        cout << "--- 模式3：内部数组基础版 ---" << endl;
        PrintMaskedMap(game, true);
        char input[32];
        int r, c;
        cout << endl << "输入纵横坐标（如Gf、A1，按q退出）：";
        cin >> input;
        if (input[0] == 'q' || input[0] == 'Q')
            break;
        if (!ParseInput(input, r, c) || r < 0 || r >= game.rows || c < 0 || c >= game.cols) {
            cout << "坐标无效！" << endl;
            to_be_continued("按回车重试");
            continue;
        }
        if (game.mask[r][c] == MASK_OPEN) {
            cout << "该位置已打开！" << endl;
            to_be_continued("按回车重试");
            continue;
        }
        if (firstClick) {
            PlaceMinesSafe(game, r, c);
            ExpandArea(game, r, c);
            firstClick = false;
        }
        else {
            if (game.map[r][c] == CELL_MINE) {
                game.mask[r][c] = MASK_OPEN;
                cct_cls();
                PrintMaskedMap(game, true);
                cout << endl << "你踩到雷了，游戏结束！" << endl;
                to_be_continued(NULL);
                break;
            }
            else
                ExpandArea(game, r, c);
        }
        if (CheckWin(game)) {
            cct_cls();
            PrintMaskedMap(game, true);
            cout << endl << "恭喜你赢了！" << endl;
            to_be_continued(NULL);
            break;
        }
    }
}

void SubProblem_4() {
    int level;
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）：";
    cin >> level;
    cct_cls();
    MineGame game;
    InitGame(game, level);
    bool firstClick = true;
    time_t startTime = 0;
    while (true) {
        cct_cls();
        cout << "内部数组：" << endl;
        PrintMaskedMap(game, true);
        char input[32];
        int r, c;
        cout << endl << "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3标记，#A3取消）：";
        cin >> input;
        if (input[0] == 'q' || input[0] == 'Q')
            break;
        if (input[0] == '&') {
            if (firstClick)
                cout << "游戏尚未开始计秒。" << endl;
            else { 
                time_t now = time(0);
                cout << "已运行时间：" << (int)(now - startTime) << " 秒" << endl; }
            to_be_continued("按回车继续");
            continue;
        }
        if (input[0] == '@' || input[0] == '#') {
            if (ParseInput(input + 1, r, c)) {
                if (r >= 0 && r < game.rows && c >= 0 && c < game.cols) {
                    if (input[0] == '@') { 
                        if (game.mask[r][c] == MASK_COVERED) game.mask[r][c] = MASK_FLAG
                            ; 
                    }
                    else { 
                        if (game.mask[r][c] == MASK_FLAG) game.mask[r][c] = MASK_COVERED
                            ; 
                    }
                    continue;
                }
            }
            cout << "标记坐标无效！" << endl; 
            to_be_continued(NULL);
            continue;
        }
        if (!ParseInput(input, r, c) || r < 0 || r >= game.rows || c < 0 || c >= game.cols) {
            cout << "坐标无效！" << endl;
            to_be_continued(NULL);
            continue;
        }
        if (game.mask[r][c] != MASK_COVERED) {
            cout << "该位置无法点击（已打开或已标记）！" << endl; 
            to_be_continued(NULL); 
            continue;
        }
        if (firstClick) {
            startTime = time(0);
            PlaceMinesSafe(game, r, c);
            ExpandArea(game, r, c);
            firstClick = false;
        }
        else {
            if (game.map[r][c] == CELL_MINE) {
                game.mask[r][c] = MASK_OPEN;
                cct_cls();
                PrintMaskedMap(game, true);
                cout << endl << "【炸了！】游戏结束！" << endl;
                to_be_continued(NULL);
                break;
            }
            else ExpandArea(game, r, c);
        }
        if (CheckWin(game)) {
            cct_cls();
            PrintMaskedMap(game, true);
            time_t now = time(0);
            cout << endl << "【赢了！】总耗时：" << (int)(now - startTime) << " 秒。" << endl;
            to_be_continued(NULL);
            break;
        }
    }
}