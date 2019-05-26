#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include "librarys.h"

/************************ 전역변수 ************************/
char** note;						//노트를 위한 2차원 배열
int SIZE_OF_NOTE;					//노트의 길이를 저장 할 변수
int combo = 0;						//콤보를 저장 할 변수
int perfect = 0, good = 0, bad = 0;	//판정을 기록 할 변수
/*********************************************************/

/// 게임을 시작하면, 플레이어는 곡을 선택하고 이 함수로 넘어오게 될 것이다.
/// 이 함수는 본 게임의 메인 함수이다.

/// 이 함수는 게임을 동작시키기 위해 다음과 같은 절차를 거친다.
/// 1) 게임에 필요한 변수 및 배열들을 초기화한다.
/// 2) 파일로부터 노트를 불러온다.
/// 3) 반복문과 여러가지 함수 및 기능을 사용해 게임을 동작시킨다.
/// 4) 게임이 모두 끝나면 결과 창 함수로 점프한다.
void inGame(int sel) {
	int line = 50;	//출력 시 줄 수를 계산하기 위한 변수
	int i, j, k;	// 제어용 변수
	int sync = 103;	// 노래와의 싱크
	// 전 게임의 기록을 초기화
	perfect = 0;
	good = 0;
	bad = 0;
	combo = 0;

	//원활한 출력이 가능할 만큼 콘솔 창이 넓어진다.
	system("mode con cols=120 lines=60");

	FILE* np = fopen("note.txt", "r");
	
	//유연한 동적할당 및 반복문 사용을 위해 노트의 줄 수를 구한다.
	SIZE_OF_NOTE = countLine(np); // fileio.c

	note = (char **)malloc(sizeof(char*) * SIZE_OF_NOTE);

	for (int i = 0; i < SIZE_OF_NOTE; i++){
		note[i] = (char *)malloc(sizeof(char) * 4);
	}

	//노트를 생성한다.
	readNote(note, np, SIZE_OF_NOTE);	// fileio.c

	PlaySound(TEXT(taebo), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//다음 반복문은 노트의 길이만큼 게임을 동작시킨다.
	for (i = 0; i < SIZE_OF_NOTE; i++) {
		makeFrame();
		gotoxy(0, 0);	

		line = 34;		// 틀의 끝 = 48번 째 줄
		
		//다음 반복문은 노트를 화면에 출력시킨다.
		for (j = SIZE_OF_NOTE - 1; j > SIZE_OF_NOTE - 34; j--) {
			for (k = 0; k < 4; k++) {
				if (note[j][k] == 1) {
					printNote(k, line);
				}
			}
			//윗줄로 한 줄 올라간다.
			line--;
		}
		
		//플레이어가 키를 누르면 여기서 처리한다.
		isHitted(0);
		Sleep(sync);	//싱크만큼 딜레이

		//무시된 노트는 개못하노로 간주한다.
		for (j = 0; j < 4; j++) {
			if (note[SIZE_OF_NOTE - 1][j] ==  1) {
				note[SIZE_OF_NOTE - 1][j] = 0;
				processBad();
			}
		}

		//다음 반복문은 노트를 한 칸씩 아래로 이동시킨다.
		for (j = SIZE_OF_NOTE - 1; j >= 0 ; j--) {
			for (k = 0; k < 4; k++) {
				// SIZE_OF_NOTE - 1를 노트의 끝으로 삼는다.
				if (j == SIZE_OF_NOTE - 1) {
					break;
				}
				else {
					note[j + 1][k] = note[j][k];
					note[j][k] = 0;
				}
			}
		}

		//정보) system("cls")는 gotoxy(0,0)보다 더 느리다 카더라.
		gotoxy(0, 0);	
	}

	PlaySound(NULL, NULL, NULL);

	fclose(np);		
	system("mode con cols=800 lines=600");
	viewResult(perfect, good, bad);	
}


// TODO
// 노트가 판정 범위 내에 있지 않을시에 입력했다면...
// 가장 가까이 있는 노트를 지우고 개못하노를 출력한다.

// kbhit을 사용하여 입력되었을때만 함수를 실행하는 기능에 대해 고찰

/// 이 함수는 플레이어가 키를 눌렀는지, 또 어떤 키를 눌렀는지 확인하는 함수이다.
/// 이 함수는 inGame()에서 주기적으로 호출 될 것이다.

/// 이 함수는 키가 눌리게 되면 다음과 같은 일을 한다.
/// 1) f, g, h, j 중 하나의 키를 입력받는다
/// 2) 입력받은 문자에 따라서 해당하는 레인 번호를 인자로 하여금 판정 함수를 호출한다.
/// 3) 이후 판정은 판정 함수가 할 것이다.
void isHitted(void *arg) {
	//알맞은 레인 번호를 인자로 하여 호출한다.
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

/// 이 함수는 해당하는 레인에 대해서 노트가 적절한 타이밍에 눌렸는지 판정하는 함수이다.
/// 이 함수는 isHitted()의 스위치 케이스문에 의해서 인자를 받으며 호출된다.

/// 이 함수는 노트를 판정하기 위해 다음과 같은 절차를 거친다.
/// 1) SIZE_OF_NOTE - 3의 위치를 PERFECT로 하여 그 위치의 +-1 만큼을 GOOD으로 판정한다.
/// 2) 배열의 적절한 위치들을 확인하여 노트가 존재하는지 확인한다.
/// 3) 노트의 존재 여부에따라 해당 판정에 알맞는 코드를 실행하고 기록한다.
void judge(int rain) {
	// PERFECT
	if (note[SIZE_OF_NOTE - 3][rain] == 1) {
		//판정된 노트 삭제
		note[SIZE_OF_NOTE - 3][rain] = 0;
		processPerfect();
		return;
	}
	// GOOD LOW
	else if (note[SIZE_OF_NOTE - 2][rain] == 1) {
		//판정된 노트 삭제
		note[SIZE_OF_NOTE - 2][rain] = 0;
		processGood();
		return;
	}
	// GOOD HIGH
	else if (note[SIZE_OF_NOTE - 4][rain] == 1) {
		//판정된 노트 삭제
		note[SIZE_OF_NOTE - 4][rain] = 0;
		processGood();
		return;
	}
	// 개못하노 ㅉ
	else {
		processBad();
		return;
	}
}

void processPerfect() {
	//판정 출력
	gotoxy(100, 30);
	printf("PERFECT!   														");
	//콤보 출력
	printCombo();
	//퍼펙트에 기록
	perfect++;
	combo++;
	return;
}

void processGood() {
	//판정 출력
	gotoxy(100, 30);
	printf("GOOD!                                                          ");
	//콤보 출력
	printCombo();
	//굿에 기록
	good++;
	combo++;
	return;
}

void processBad() {
	//판정 출력
	gotoxy(100, 30);
	printf("개못하노ㅉ       												");
	//콤보 초기화 및 출력
	combo = 0;
	printCombo();
	//개못하노에 기록
	bad++;
	return;
}

/// 이 함수는 콤보를 출력한다.
void printCombo() {
	gotoxy(100, 31);
	printf("COMBO : %d															", combo);
}

/// 이 함수는 적절하게 미리 계산된 위치에 노트를 출력한다.
void printNote(int x, int y) {
	gotoxy(x * 11 + 1, y);
	printf(" ★★★★★");
}

/// 본 함수는 게임의 기본 틀을 출력한다.
void makeFrame() {
	int i;
	printf("┌──────────┬──────────┬──────────┬──────────┐  \n");
	for (i = 0; i <= 30; i++) {
		printf("│          │          │          │          │           \n");
	}
	printf("├──────────┼──────────┼──────────┼──────────┼──< PERFECT!	\n");
	printf("│          │          │          │          │  				\n");
	printf("│          │          │          │          │				\n");
	printf("└──────────┴──────────┴──────────┴──────────┘  			    \n");
	printf("     F          G          H          J     \n                ");
	printf("                                                              ");
}
