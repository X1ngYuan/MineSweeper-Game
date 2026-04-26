/* XingYuan */
#include <iostream>
#include <iomanip>
#include "mine_sweeper.h"

using namespace std;

void PrintGraphInternal(const MineGame& game) {
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "     ";
    for (int j = 0; j < game.cols; j++) {
        char colLabel = (j < 9) ? (j + '1') : (j - 9 + 'a');
        cout << "  " << colLabel << "   ";
    }
    cout << endl;

    for (int i = 0; i < game.rows; i++) {
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << "   ";
        if (i == 0) 
            cout << "╔"; 
        else 
            cout << "╠";
        for (int j = 0; j < game.cols; j++) {
            cout << " ═ ═ ";
            if (j == game.cols - 1) {
                if (i == 0) cout << "╗"; else cout << "╣";
            }
            else {
                if (i == 0) cout << "╦"; else cout << "╬"; 
            }
        }
        cout << endl;

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << "   ║ ";
        for (int j = 0; j < game.cols; j++) {
            cct_setcolor(COLOR_WHITE, COLOR_WHITE);
            cout << "    ";
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cout << "║ ";
        }
        cout << endl;

        // 内容行
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << (char)('A' + i) << "  ║ ";
        for (int j = 0; j < game.cols; j++) {
            int val = game.map[i][j];
            if (val == CELL_MINE) {
                cct_setcolor(COLOR_WHITE, COLOR_HRED);
                cout << " *  ";
            }
            else if (val == 0) {
                cct_setcolor(COLOR_WHITE, COLOR_WHITE);
                cout << "    ";
            }
            else {
                int foreColor;
                switch (val) {
                    case 1: 
                        foreColor = COLOR_HBLUE;
                        break;
                    case 2: 
                        foreColor = COLOR_HGREEN; 
                        break;
                    case 3:
                        foreColor = COLOR_HRED; 
                        break;
                    case 4: 
                        foreColor = COLOR_HCYAN;
                        break;
                    default:
                        foreColor = COLOR_HYELLOW;
                        break;
                }
                cct_setcolor(COLOR_WHITE, foreColor);
                cout << " " << val << "  ";
            }
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cout << "║ ";
        }
        cout << endl;
    }

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "   ╚";
    for (int j = 0; j < game.cols; j++) {
        cout << " ═ ═ ";
        if (j == game.cols - 1) 
            cout << "╝"; 
        else
            cout << "╩";
    }
    cout << endl;
}

void SubProblem_5() {
    int level;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）："; 
    cin >> level;
    if (level == 1) 
        cct_setconsoleborder(75, 45);
    else if (level == 2)
        cct_setconsoleborder(120, 70);
    else 
        cct_setconsoleborder(210, 70);
    cct_cls();
    MineGame game;
    InitGame(game, level);
    PlaceMines(game);   
    CalcNumbers(game);  
    PrintGraphInternal(game);
    int finalY = (game.rows * 3) + 5;
    to_be_continued(NULL, 0, finalY);
    cct_setconsoleborder(80, 25);
}

void SubProblem_6() {
    int level;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）：";
    cin >> level;

    if (level == 1)
        cct_setconsoleborder(75, 45);
    else if (level == 2)
        cct_setconsoleborder(120, 70);
    else 
        cct_setconsoleborder(210, 70);

    cct_cls();
    MineGame game;
    InitGame(game, level);
    PlaceMines(game);
    CalcNumbers(game);
    PrintGraphInternal(game);

    int finalY = (game.rows * 3) + 5;
    cct_showstr(0, finalY, "当前模式：[模式6] 监控鼠标位置。按ESC退出监控并恢复窗口。", COLOR_BLACK, COLOR_WHITE);

    cct_enable_mouse();

    int MX, MY, MAction, k1, k2;
    int r, c;
    int eventType;

    while (true) {
        eventType = cct_read_keyboard_and_mouse(MX, MY, MAction, k1, k2);

        if (eventType == CCT_KEYBOARD_EVENT && k1 == 27) {
            break;
        }

        if (eventType == CCT_MOUSE_EVENT) {
            r = (MY - 2) / 3;
            c = (MX - 5) / 6;

            if (r >= 0 && r < game.rows && c >= 0 && c < game.cols && MY >= 2) {
                cct_showstr(0, finalY + 2, "[当前光标]  ", COLOR_BLACK, COLOR_WHITE);
                cct_showch(12, finalY + 2, (char)('A' + r), COLOR_BLACK, COLOR_WHITE);
                cct_showstr(13, finalY + 2, "行", COLOR_BLACK, COLOR_WHITE);

                if (c < 9) {
                    cct_showint(15, finalY + 2, c + 1, COLOR_BLACK, COLOR_WHITE);
                    cct_showstr(16, finalY + 2, "列          ", COLOR_BLACK, COLOR_WHITE);
                }
                else {
                    cct_showch(15, finalY + 2, (char)('a' + (c - 9)), COLOR_BLACK, COLOR_WHITE);
                    cct_showstr(16, finalY + 2, "列          ", COLOR_BLACK, COLOR_WHITE);
                }

                if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
                    cct_showstr(0, finalY + 4, "检测到左键点击坐标！", COLOR_BLACK, COLOR_HRED);
                }
                else if (MAction == MOUSE_ONLY_MOVED) {
                    cct_showstr(0, finalY + 4, "                    ", COLOR_BLACK, COLOR_WHITE);
                }
            }
            else {
                cct_showstr(0, finalY + 2, "[当前光标]  位置非法            ", COLOR_BLACK, COLOR_WHITE);
                cct_showstr(0, finalY + 4, "                    ", COLOR_BLACK, COLOR_WHITE);
            }
        }
    }

    cct_disable_mouse();           
    cct_setconsoleborder(80, 25);  
    cct_cls();                     
}

void PrintGame(const MineGame& game) {
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "     ";
    for (int j = 0; j < game.cols; j++) {
        char colLabel = (j < 9) ? (j + '1') : (j - 9 + 'a');
        cout << "  " << colLabel << "   "; 
    }
    cout << endl;

    for (int i = 0; i < game.rows; i++) {
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << "   ";
        if (i == 0) 
            cout << "╔"; 
        else 
            cout << "╠";
        for (int j = 0; j < game.cols; j++) {
            cout << " ═ ═ ";
            if (j == game.cols - 1) {
                if (i == 0) 
                    cout << "╗";
                else 
                    cout << "╣";
            }
            else {
                if (i == 0) 
                    cout << "╦"; 
                else 
                    cout << "╬";
            }
        }
        cout << endl;

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << "   ║ ";
        for (int j = 0; j < game.cols; j++) {
            if (game.mask[i][j] == MASK_COVERED || game.mask[i][j] == MASK_FLAG) {
                cct_setcolor(COLOR_HYELLOW, COLOR_HYELLOW);
            }
            else {
                cct_setcolor(COLOR_WHITE, COLOR_WHITE);
            }
            cout << "    "; 
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cout << "║ ";
        }
        cout << endl;

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << (char)('A' + i) << "  ║ "; 
        for (int j = 0; j < game.cols; j++) {
            if (game.mask[i][j] == MASK_COVERED) {
                cct_setcolor(COLOR_HYELLOW, COLOR_HYELLOW);
                cout << "    ";
            }
            else if (game.mask[i][j] == MASK_FLAG) {
                cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
                cout << " F  "; 
            }
            else {
                int val = game.map[i][j];
                if (val == CELL_MINE) {
                    cct_setcolor(COLOR_WHITE, COLOR_HRED);
                    cout << " *  "; 
                }
                else if (val == 0) {
                    cct_setcolor(COLOR_WHITE, COLOR_WHITE);
                    cout << "    ";
                }
                else {
                    int foreColor;
                    switch (val) {
                        case 1: 
                            foreColor = COLOR_HBLUE;
                            break;
                        case 2:
                            foreColor = COLOR_HGREEN;
                            break;
                        case 3: 
                            foreColor = COLOR_HRED; 
                            break;
                        case 4: 
                            foreColor = COLOR_HCYAN;
                            break;
                        default: 
                            foreColor = COLOR_HYELLOW;
                            break;
                    }
                    cct_setcolor(COLOR_WHITE, foreColor);
                    cout << " " << val << "  "; 
                }
            }
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cout << "║ ";
        }
        cout << endl;
    }

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "   ╚";
    for (int j = 0; j < game.cols; j++) {
        cout << " ═ ═ ";
        if (j == game.cols - 1)
            cout << "╝";
        else 
            cout << "╩";
    }
    cout << endl;
}

void SubProblem_7() {
    int level;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）："; cin >> level;

    if (level == 1) 
        cct_setconsoleborder(75, 45);
    else if (level == 2)
        cct_setconsoleborder(120, 70);
    else
        cct_setconsoleborder(210, 70);

    cct_cls();
    MineGame game;
    InitGame(game, level);
    cct_gotoxy(0, 0);
    PrintGame(game); 

    int finalY = (game.rows * 3) + 5;

    cct_enable_mouse();

    int MX, MY, MAction, k1, k2;
    bool firstClickDone = false;

    while (!firstClickDone) {
        int eventType = cct_read_keyboard_and_mouse(MX, MY, MAction, k1, k2);
        if (eventType == CCT_KEYBOARD_EVENT && k1 == 27)
            break;

        if (eventType == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
            int r = (MY - 2) / 3;
            int c = (MX - 5) / 6;

            if (r >= 0 && r < game.rows && c >= 0 && c < game.cols && MY >= 2) {
                PlaceMinesSafe(game, r, c);
                CalcNumbers(game);
                ExpandArea(game, r, c);

                firstClickDone = true;
            }
        }
    }

    cct_gotoxy(0, 0);
    PrintGame(game);

    cct_disable_mouse();

    to_be_continued(NULL, 0, finalY + 3);

    cct_setconsoleborder(80, 25);
    cct_cls();
}

void SubProblem_8() {
    int level;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）："; cin >> level;

    if (level == 1) 
        cct_setconsoleborder(75, 45);
    else if (level == 2)
        cct_setconsoleborder(120, 70);
    else 
        cct_setconsoleborder(210, 70);

    cct_cls();
    MineGame game;
    InitGame(game, level);

    int finalY = (game.rows * 3) + 5;

    cct_setcursor(0);
    cct_enable_mouse();

    int MX, MY, MAction, k1, k2;
    int lastMX = -1, lastMY = -1, lastMAction = -1; 
    bool firstClick = true, gameOver = false, gameWin = false;

    cct_gotoxy(0, 0);
    PrintGame(game);

    while (true) {
        int eventType = cct_read_keyboard_and_mouse(MX, MY, MAction, k1, k2);

        bool needRedraw = false; 

        if (eventType == CCT_KEYBOARD_EVENT && k1 == 27) 
            break;

        if (eventType == CCT_MOUSE_EVENT) {
            if (MX != lastMX || MY != lastMY || MAction != lastMAction) {
                lastMX = MX; lastMY = MY; lastMAction = MAction;

                int r = (MY - 2) / 3;
                int c = (MX - 5) / 6;

                if (r >= 0 && r < game.rows && c >= 0 && c < game.cols && MY >= 2) {
                    
                    if (MAction == MOUSE_LEFT_BUTTON_CLICK && game.mask[r][c] == MASK_COVERED) {
                        if (firstClick) {
                            PlaceMinesSafe(game, r, c);
                            CalcNumbers(game);
                            firstClick = false;
                        }
                        if (game.map[r][c] == CELL_MINE) {
                            for (int i = 0; i < game.rows; i++) {
                                for (int j = 0; j < game.cols; j++) {
                                    if (game.map[i][j] == CELL_MINE) 
                                        game.mask[i][j] = MASK_OPEN;
                                }
                            }
                            gameOver = true;
                        }
                        else {
                            ExpandArea(game, r, c);
                        }
                        needRedraw = true; 
                    }
                    
                    else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
                        if (game.mask[r][c] == MASK_COVERED) 
                            game.mask[r][c] = MASK_FLAG;
                        else if (game.mask[r][c] == MASK_FLAG) 
                            game.mask[r][c] = MASK_COVERED;
                        needRedraw = true;
                    }
                }
            }
        }

        // 胜负状态检查
        if (!gameOver && !firstClick && !gameWin) {
            bool currentWin = true;
            for (int i = 0; i < game.rows; i++) {
                for (int j = 0; j < game.cols; j++) {
                    if (game.map[i][j] != CELL_MINE && game.mask[i][j] != MASK_OPEN) {
                        currentWin = false;
                        break;
                    }
                }
                if (!currentWin) 
                    break;
            }
            if (currentWin) { 
                gameWin = true;
                needRedraw = true;
            }
        }

        if (needRedraw || gameOver || gameWin) {
            cct_gotoxy(0, 0);
            PrintGame(game);

            if (gameOver || gameWin) {
                cct_gotoxy(0, finalY);
                cct_setcolor(COLOR_BLACK, gameWin ? COLOR_HGREEN : COLOR_HRED);
                cout << (gameWin ? "恭喜你，扫雷成功！" : "很遗憾，你踩到了地雷！");
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                break;
            }
        }
    }

    cct_setcursor(1); 
    cct_disable_mouse();
    to_be_continued(NULL, 0, finalY + 2);
    cct_setconsoleborder(80, 25);
    cct_cls();
}

void SubProblem_9() {
    int level;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）："; cin >> level;

    if (level == 1)
        cct_setconsoleborder(75, 45);
    else if (level == 2)
        cct_setconsoleborder(120, 70);
    else 
        cct_setconsoleborder(210, 70);

    cct_cls();
    MineGame game;
    InitGame(game, level);

    int finalY = (game.rows * 3) + 5;
    cct_setcursor(0); 
    cct_enable_mouse();

    int MX, MY, MAction, k1, k2;
    int lastMX = -1, lastMY = -1;
    bool firstClick = true, gameOver = false, gameWin = false, showTime = false;
    long long startTime = 0;

    cct_gotoxy(0, 0);
    PrintGame(game);

    while (true) {
        int eventType = cct_read_keyboard_and_mouse(MX, MY, MAction, k1, k2);
        bool needRedraw = false;

        if (eventType == CCT_KEYBOARD_EVENT) {
            if (k1 == 27) 
                break;
            if (k1 == ' ') { 
                showTime = true;
                needRedraw = true;
            }
        }

        if (eventType == CCT_MOUSE_EVENT) {
            if (MX != lastMX || MY != lastMY || MAction != 0) {
                lastMX = MX; lastMY = MY;
                int r = (MY - 2) / 3, c = (MX - 5) / 6;
                if (r >= 0 && r < game.rows && c >= 0 && c < game.cols && MY >= 2) {
                    if (MAction == MOUSE_LEFT_BUTTON_CLICK && game.mask[r][c] == MASK_COVERED) {
                        if (firstClick) {
                            PlaceMinesSafe(game, r, c);
                            CalcNumbers(game);
                            startTime = time(NULL); firstClick = false;
                        }
                        if (game.map[r][c] == CELL_MINE) {
                            for (int i = 0; i < game.rows; i++)
                                for (int j = 0; j < game.cols; j++)
                                    if (game.map[i][j] == CELL_MINE) 
                                        game.mask[i][j] = MASK_OPEN;
                            gameOver = true;
                        }
                        else ExpandArea(game, r, c);
                        needRedraw = true;
                    }
                    else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
                        if (game.mask[r][c] == MASK_COVERED)
                            game.mask[r][c] = MASK_FLAG;
                        else if (game.mask[r][c] == MASK_FLAG) 
                            game.mask[r][c] = MASK_COVERED;
                        needRedraw = true;
                    }
                }
            }
        }

        // 胜负状态检查逻辑
        if (!gameOver && !firstClick && !gameWin) {
            bool currentWin = true;
            for (int i = 0; i < game.rows; i++) {
                for (int j = 0; j < game.cols; j++) {
                    if (game.map[i][j] != CELL_MINE && game.mask[i][j] != MASK_OPEN) {
                        currentWin = false;
                        break;
                    }
                }
                if (!currentWin)
                    break;
            }
            if (currentWin) {
                gameWin = true; needRedraw = true; 
            }
        }

        if (needRedraw || gameOver || gameWin) {
            cct_gotoxy(0, 0);
            PrintGame(game);

            int flagCount = 0;
            for (int i = 0; i < game.rows; i++)
                for (int j = 0; j < game.cols; j++)
                    if (game.mask[i][j] == MASK_FLAG) 
                        flagCount++;

            cct_gotoxy(0, finalY);
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cout << "剩余雷数：" << (game.mineNum - flagCount) << "    " << "按空格显示耗时" <<endl;

            if (showTime || gameOver || gameWin) {
                int duration = firstClick ? 0 : (int)(time(NULL) - startTime);
                cout << "耗时统计：" << duration << " 秒          ";
                showTime = false;
            }
            else {
                cout << "                    ";
            }

            if (gameOver || gameWin) {
                cct_gotoxy(0, finalY + 2);
                cct_setcolor(COLOR_BLACK, gameWin ? COLOR_HGREEN : COLOR_HRED);
                cout << (gameWin ? "【胜利】恭喜你排除所有险情！" : "【失败】遗憾踩雷，下次努力！");
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                break;
            }
        }
    }
    cct_setcursor(1); 
    cct_disable_mouse();
    to_be_continued(NULL, 0, finalY + 4);
    cct_setconsoleborder(80, 25);
    cct_cls();
}