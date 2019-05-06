#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include "librarys.h"

#pragma comment(lib, "winmm.lib")

/// 프로그램의 시작과 동시에 게임 시작 화면을 출력한다.
int main() {
	system("mode con cols=800 lines=600");

	// 메인 테마 재생
	PlaySound(TEXT(sans), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//시작화면 출력
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	mainTitle();
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO START\n\n\n\n");
	system("pause");

	// 어서오세요 재생
	PlaySound(TEXT(welcome), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1500);

	liveMenu();
}

/// 라이브 메뉴를 출력한다.
void liveMenu() {
	int sel = 0;

	system("cls");

	// 대기실 음악 재생
	PlaySound(TEXT(waitingRoom), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	mainTitle();

	//곡 명 출력
	printf("곡 선택\n\n");
	printf("1. 절 대 태 보 해\n\n");

	printf("선택 >> ");
	scanf_s("%d", &sel);

	switch (sel) {
	case(1):
		//본 게임으로 이동
		inGame(sel);
	default:
		printf("똑바로 고르십시오 휴먼\n");
	}
}

/// 결과를 출력한 후 메뉴로 돌아간다.
void viewResult(int perfect, int good, int bad) {
	Sleep(200);
	system("cls");
	printf("귀하의 성적은...\n");
	printf("PERFECT : %d\n", perfect);
	printf("GOOD : %d\n", good);
	printf("개못하노 : %d\n", bad);
	system("pause");
	liveMenu();
}