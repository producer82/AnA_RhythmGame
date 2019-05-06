#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <mmsystem.h>
#include "librarys.h"

/************************ �������� ************************/
char** note;						//��Ʈ�� ���� 2���� �迭
int SIZE_OF_NOTE;					//��Ʈ�� ���̸� ���� �� ����
int combo = 0;						//�޺��� ���� �� ����
int perfect = 0, good = 0, bad = 0;	//������ ��� �� ����
/*********************************************************/

/// ������ �����ϸ�, �÷��̾�� ���� �����ϰ� �� �Լ��� �Ѿ���� �� ���̴�.
/// �� �Լ��� �� ������ ���� �Լ��̴�.

/// �� �Լ��� ������ ���۽�Ű�� ���� ������ ���� ������ ��ģ��.
/// 1) ���ӿ� �ʿ��� ���� �� �迭���� �ʱ�ȭ�Ѵ�.
/// 2) ���Ϸκ��� ��Ʈ�� �ҷ��´�.
/// 3) �ݺ����� �������� �Լ� �� ����� ����� ������ ���۽�Ų��.
/// 4) ������ ��� ������ ��� â �Լ��� �����Ѵ�.
void inGame(int sel) {
	// �� ������ ����� �ʱ�ȭ
	perfect = 0;
	good = 0;
	bad = 0;
	combo = 0;

	int line = 50;	//��� �� �� ���� ����ϱ� ���� ����
	int i, j, k;	// ����� ����
	int sync = 103;	// �뷡���� ��ũ

	//��Ȱ�� ����� ������ ��ŭ �ܼ� â�� �о�����.
	system("mode con cols=120 lines=60");

	FILE* np = fopen("note.txt", "r");
	
	//������ �����Ҵ� �� �ݺ��� ����� ���� ��Ʈ�� �� ���� ���Ѵ�.
	SIZE_OF_NOTE = countLine(np); // fileio.c

	note = (char **)malloc(sizeof(char*) * SIZE_OF_NOTE);

	for (int i = 0; i < SIZE_OF_NOTE; i++){
		note[i] = (char *)malloc(sizeof(char) * 4);
	}

	//��Ʈ�� �����Ѵ�.
	readNote(note, np, SIZE_OF_NOTE);	// fileio.c

	PlaySound(TEXT(taebo), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//���� �ݺ����� ��Ʈ�� ���̸�ŭ ������ ���۽�Ų��.
	for (i = 0; i < SIZE_OF_NOTE; i++) {
		makeFrame();
		gotoxy(0, 0);	

		line = 34;		// Ʋ�� �� = 48�� ° ��
		
		//���� �ݺ����� ��Ʈ�� ȭ�鿡 ��½�Ų��.
		for (j = SIZE_OF_NOTE - 1; j > SIZE_OF_NOTE - 34; j--) {
			for (k = 0; k < 4; k++) {
				if (note[j][k] == 1) {
					printNote(k, line);
				}
			}
			//���ٷ� �� �� �ö󰣴�.
			line--;
		}
		
		//�÷��̾ Ű�� ������ ���⼭ ó���Ѵ�.
		isHitted(0);
		Sleep(sync);	//��ũ��ŭ ������

		//���õ� ��Ʈ�� �����ϳ�� �����Ѵ�.
		for (j = 0; j < 4; j++) {
			if (note[SIZE_OF_NOTE - 1][j] ==  1) {
				note[SIZE_OF_NOTE - 1][j] = 0;
				processBad();
			}
		}

		//���� �ݺ����� ��Ʈ�� �� ĭ�� �Ʒ��� �̵���Ų��.
		for (j = SIZE_OF_NOTE - 1; j >= 0 ; j--) {
			for (k = 0; k < 4; k++) {
				// SIZE_OF_NOTE - 1�� ��Ʈ�� ������ ��´�.
				if (j == SIZE_OF_NOTE - 1) {
					break;
				}
				else {
					note[j + 1][k] = note[j][k];
					note[j][k] = 0;
				}
			}
		}

		//����) system("cls")�� gotoxy(0,0)���� �� ������ ī����.
		gotoxy(0, 0);	
	}

	PlaySound(NULL, NULL, NULL);

	fclose(np);		
	system("mode con cols=800 lines=600");
	viewResult(perfect, good, bad);	
}


// TODO
// ��Ʈ�� ���� ���� ���� ���� �����ÿ� �Է��ߴٸ�...
// ���� ������ �ִ� ��Ʈ�� ����� �����ϳ븦 ����Ѵ�.

// kbhit�� ����Ͽ� �ԷµǾ������� �Լ��� �����ϴ� ��ɿ� ���� ����

/// �� �Լ��� �÷��̾ Ű�� ��������, �� � Ű�� �������� Ȯ���ϴ� �Լ��̴�.
/// �� �Լ��� inGame()���� �ֱ������� ȣ�� �� ���̴�.

/// �� �Լ��� Ű�� ������ �Ǹ� ������ ���� ���� �Ѵ�.
/// 1) f, g, h, j �� �ϳ��� Ű�� �Է¹޴´�
/// 2) �Է¹��� ���ڿ� ���� �ش��ϴ� ���� ��ȣ�� ���ڷ� �Ͽ��� ���� �Լ��� ȣ���Ѵ�.
/// 3) ���� ������ ���� �Լ��� �� ���̴�.
void isHitted(void *arg) {
	//�˸��� ���� ��ȣ�� ���ڷ� �Ͽ� ȣ���Ѵ�.
	if (GetAsyncKeyState(0x46)) {
		judge(0);
	}
	else if (GetAsyncKeyState(0x47)) {
		judge(1);
	}
	else if (GetAsyncKeyState(0x48)) {
		judge(2);
	}
	else if (GetAsyncKeyState(0x4A)) {
		judge(3);
	}
	else {
		;
	}
}

/// �� �Լ��� �ش��ϴ� ���ο� ���ؼ� ��Ʈ�� ������ Ÿ�ֿ̹� ���ȴ��� �����ϴ� �Լ��̴�.
/// �� �Լ��� isHitted()�� ����ġ ���̽����� ���ؼ� ���ڸ� ������ ȣ��ȴ�.

/// �� �Լ��� ��Ʈ�� �����ϱ� ���� ������ ���� ������ ��ģ��.
/// 1) SIZE_OF_NOTE - 3�� ��ġ�� PERFECT�� �Ͽ� �� ��ġ�� +-1 ��ŭ�� GOOD���� �����Ѵ�.
/// 2) �迭�� ������ ��ġ���� Ȯ���Ͽ� ��Ʈ�� �����ϴ��� Ȯ���Ѵ�.
/// 3) ��Ʈ�� ���� ���ο����� �ش� ������ �˸´� �ڵ带 �����ϰ� ����Ѵ�.
void judge(int rain) {
	// PERFECT
	if (note[SIZE_OF_NOTE - 3][rain] == 1) {
		//������ ��Ʈ ����
		note[SIZE_OF_NOTE - 3][rain] = 0;
		processPerfect();
		return;
	}
	// GOOD LOW
	else if (note[SIZE_OF_NOTE - 2][rain] == 1) {
		//������ ��Ʈ ����
		note[SIZE_OF_NOTE - 2][rain] = 0;
		processGood();
		return;
	}
	// GOOD HIGH
	else if (note[SIZE_OF_NOTE - 4][rain] == 1) {
		//������ ��Ʈ ����
		note[SIZE_OF_NOTE - 4][rain] = 0;
		processGood();
		return;
	}
	// �����ϳ� ��
	else {
		processBad();
		return;
	}
}

void processPerfect() {
	//���� ���
	gotoxy(100, 30);
	printf("PERFECT!   														");
	//�޺� ���
	printCombo();
	//����Ʈ�� ���
	perfect++;
	combo++;
	return;
}

void processGood() {
	//���� ���
	gotoxy(100, 30);
	printf("GOOD!                                                          ");
	//�޺� ���
	printCombo();
	//�¿� ���
	good++;
	combo++;
	return;
}

void processBad() {
	//���� ���
	gotoxy(100, 30);
	printf("�����ϳ뤹       												");
	//�޺� �ʱ�ȭ �� ���
	combo = 0;
	printCombo();
	//�����ϳ뿡 ���
	bad++;
	return;
}

/// �� �Լ��� �޺��� ����Ѵ�.
void printCombo() {
	gotoxy(100, 31);
	printf("COMBO : %d															", combo);
}

/// �� �Լ��� �����ϰ� �̸� ���� ��ġ�� ��Ʈ�� ����Ѵ�.
void printNote(int x, int y) {
	gotoxy(x * 11 + 1, y);
	printf(" �ڡڡڡڡ�");
}

/// �� �Լ��� ������ �⺻ Ʋ�� ����Ѵ�.
void makeFrame() {
	int i;
	printf("������������������������������������������������������������������������������������������  \n");
	for (i = 0; i <= 30; i++) {
		printf("��          ��          ��          ��          ��           \n");
	}
	printf("����������������������������������������������������������������������������������������������< PERFECT!	\n");
	printf("��          ��          ��          ��          ��  				\n");
	printf("��          ��          ��          ��          ��				\n");
	printf("������������������������������������������������������������������������������������������  			    \n");
	printf("     F          G          H          J     \n                ");
	printf("                                                              ");
}