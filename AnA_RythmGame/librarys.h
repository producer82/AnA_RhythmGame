#pragma once

// 공용
void gotoxy(int x, int y);

// 아스키 아트
void mainTitle();
void pressAnyButton();
void menuText();
void dokiMekiExperience();

// 인게임 함수 정의
void makeFrame();
void printNote(int x, int y);
void printCombo();
void isHitted(void* arg);
void judge(int rain);
void inGame(int sel);
void processPerfect();
void processGood();
void processBad();

// 파일 입출력 관련
int countLine(FILE* np);
void readNote(char** note, FILE* np, int SIZE_OF_NOTE);

// UI 및 기타 게임 외 관련
void liveMenu();
void viewResult(int perfect, int good, int bad);

// 음악 리소스 정의
#define sans ".\\sans.wav"
#define taebo ".\\taebo.wav"
#define welcome ".\\welcome.wav"
#define waitingRoom ".\\wait_room.wav"
