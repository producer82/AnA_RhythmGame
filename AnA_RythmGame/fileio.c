#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/// 이 함수는 파일로부터 노트를 읽어 배열에 저장하는 함수다.

/// 노트를 읽어 배열에 저장하기 위해 다음과 같은 절차를 거친다.
/// 1) 노트가 저장될 배열을 초기화 한다.
/// 2) 노트의 시작이 SIZE_OF_NOTE - 1이므로 노트의 끝에서부터 노트를 저장한다.
void readNote(char **note, FILE *np, int SIZE_OF_NOTE) {
	int i, j; // 제어용 변수

	// 이 반복문은 배열을 초기화 한다.
	for (i = 0; i < SIZE_OF_NOTE; i++) {
		for (int j = 0; j < 4; j++) {
			note[i][j] = 0;
		}
	}

	// 이 반복문은 노트를 읽어서 배열에 저장한다/ 
	for (i = SIZE_OF_NOTE - 1; i >= 0; i--) {
		for (j = 0; j < 4; j++) {
			fscanf(np, "%d", &note[i][j]);
		}
	}
}		

/// 이 함수는 노트의 길이(=파일의 줄 수)를 계산하여 반환하는 함수다.
/// 반환된 길이는 동적할당 크기 계산 및 반복문에 사용된다.

/// 노트의 길이를 계산하기 위해 다음과 같은 절차를 거친다.
/// 1) fgets 함수를 통해 파일 포인터를 다음 줄로 넘긴다.
/// 2) cnt에 1을 누적한다.
/// 3) 파일의 끝이면 파일 포인터를 처음으로 돌리고 cnt를 반환한다.
/// 4) 1번으로 돌아간다.
int countLine(FILE* np) {
	int cnt = 0;
	char buf[20] = { 0, };

	while (!feof(np))
	{
		fgets(buf, 8, np);
		cnt++;
	}

	//파일 포인터의 위치를 처음오로 되돌림
	fseek(np, 0, SEEK_SET);

	return cnt;
}