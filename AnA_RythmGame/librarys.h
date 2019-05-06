#pragma once

// ����
void gotoxy(int x, int y);

// �ƽ�Ű ��Ʈ
void mainTitle();
void pressAnyButton();
void menuText();
void dokiMekiExperience();

// �ΰ��� �Լ� ����
void makeFrame();
void printNote(int x, int y);
void printCombo();
void isHitted(void* arg);
void judge(int rain);
void inGame(int sel);
void processPerfect();
void processGood();
void processBad();

// ���� ����� ����
int countLine(FILE* np);
void readNote(char** note, FILE* np, int SIZE_OF_NOTE);

// UI �� ��Ÿ ���� �� ����
void liveMenu();
void viewResult(int perfect, int good, int bad);

// ���� ���ҽ� ����
#define sans ".\\sans.wav"
#define taebo ".\\taebo.wav"
#define welcome ".\\welcome.wav"
#define waitingRoom ".\\wait_room.wav"
