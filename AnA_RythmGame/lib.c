#include <stdio.h>
#include <Windows.h>

/// Ŀ���� ���ϴ� ��ġ�� �ű��.
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
