#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include "librarys.h"

#pragma comment(lib, "winmm.lib")

/// ���α׷��� ���۰� ���ÿ� ���� ���� ȭ���� ����Ѵ�.
int main() {
	system("mode con cols=800 lines=600");

	// ���� �׸� ���
	PlaySound(TEXT(sans), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//����ȭ�� ���
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	mainTitle();
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO START\n\n\n\n");
	system("pause");

	// ������� ���
	PlaySound(TEXT(welcome), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1500);

	liveMenu();
}

/// ���̺� �޴��� ����Ѵ�.
void liveMenu() {
	int sel = 0;

	system("cls");

	// ���� ���� ���
	PlaySound(TEXT(waitingRoom), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	mainTitle();

	//�� �� ���
	printf("�� ����\n\n");
	printf("1. �� �� �� �� ��\n\n");

	printf("���� >> ");
	scanf_s("%d", &sel);

	switch (sel) {
	case(1):
		//�� �������� �̵�
		inGame(sel);
	default:
		printf("�ȹٷ� ���ʽÿ� �޸�\n");
	}
}

/// ����� ����� �� �޴��� ���ư���.
void viewResult(int perfect, int good, int bad) {
	Sleep(200);
	system("cls");
	printf("������ ������...\n");
	printf("PERFECT : %d\n", perfect);
	printf("GOOD : %d\n", good);
	printf("�����ϳ� : %d\n", bad);
	system("pause");
	liveMenu();
}