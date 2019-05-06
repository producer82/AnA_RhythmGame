#include <stdio.h>
#include <Windows.h>

/// 커서를 원하는 위치로 옮긴다.
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
