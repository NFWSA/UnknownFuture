#include <Windows.h>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>

using namespace std;

void cprintf(char *str, WORD color, ...);

int main() {
        for (int i = 0; i < 16 * 16; i += 16) {
                cprintf("0", i + 0);
                cprintf("1", i + 1);
                cprintf("2", i + 2);
                cprintf("3", i + 3);
                cprintf("4", i + 4);
                cprintf("5", i + 5);
                cprintf("6", i + 6);
                cprintf("7", i + 7);
                cprintf("8", i + 8);
                cprintf("9", i + 9);
                cprintf("A", i + 10);
                cprintf("B", i + 11);
                cprintf("C", i + 12);
                cprintf("D", i + 13);
                cprintf("E", i + 14);
                cprintf("F", i + 15);
                cout << endl;
    }
    return 0;
}

void cprintf(char *str, WORD color, ...) {
    WORD colorOld;
    HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    colorOld = csbi.wAttributes;
    SetConsoleTextAttribute(handle, color);
    cout << str;
    SetConsoleTextAttribute(handle, colorOld);
}
