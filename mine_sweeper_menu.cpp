/* XingYuan */
#include <iostream>
#include <conio.h>
#include "mine_sweeper.h"

using namespace std;

void main_menu() {
    char choice;
    while (true) {
        cct_cls();
        cct_setcolor();

        cout << "--------------------------------------------" << endl;
        cout << "1.选择模式，显示内部数组" << endl;
        cout << "2.输入一个位置，显示打开区域" << endl;
        cout << "3.内部数组基础版" << endl;
        cout << "4.内部数组完整版（标记、运行时间）" << endl;
        cout << "5.画出框架，显示内部数据" << endl;
        cout << "6.检测鼠标位置和合法性，以及左键点击" << endl;
        cout << "7.鼠标点击一次，显示打开区域" << endl;
        cout << "8.允许连续游戏，支持右键标记，判断游戏结束" << endl;
        cout << "9.完整游戏，标明雷数，空格、结束显示时间" << endl;
        cout << "0.退出游戏" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "[请选择] ";

        choice = _getch();
        cout << choice << endl;

        cct_cls();

        switch (choice) {
            case '1':
                SubProblem_1();
                break;
            case '2': 
                SubProblem_2(); 
                break;
            case '3': 
                SubProblem_3();
                break;
            case '4':
                SubProblem_4();
                break;
            case '5': 
                SubProblem_5(); 
                break;
            case '6': 
                SubProblem_6(); 
                break;
            case '7':
                SubProblem_7(); 
                break;
            case '8':
                SubProblem_8();
                break;
            case '9': 
                SubProblem_9(); 
                break;
            case '0':
                return;
            default:
                break;
        }
    }
}