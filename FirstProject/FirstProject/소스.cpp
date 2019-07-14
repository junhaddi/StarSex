#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "ConsoleFunctions.h"
#define FPS 60
#define GAME_WIDTH 40
#define GAME_HEIGHT 20
using namespace std;

enum State {
	TITLE,
	GAME,
	OVER,
};

// ���� ���� �ʱ�ȭ
State state;
int score;
int playerX, playerY;
int enemyX, enemyY;
int starX, starY;

void init();
void reset();
void update();
void render();

int main() {
	init();
	
	while (true) {
		update();
		render();
		Sleep(1000 / FPS);
	}
	return 0;
}

void init() {
	setTitle("�������ڢ�");
	setSize(GAME_WIDTH, GAME_HEIGHT);
	setCursorType(CursorInvisible);
	srand((unsigned int)time(NULL));
	State state = TITLE;
	reset();
}

void reset() {
	score = 0;
	playerX = GAME_WIDTH / 2;
	playerY = GAME_HEIGHT / 2;
	enemyX = rand() % (GAME_WIDTH - 3) + 1;
	enemyY = rand() % (GAME_HEIGHT - 2) + 1;
	starX = rand() % (GAME_WIDTH - 3) + 1;
	starY = rand() % (GAME_HEIGHT - 2) + 1;
}

void update() {
	if (state == TITLE || state == OVER) {
		if (_kbhit()) {
			state = GAME;
			reset();
		}
	}
	else if (state == GAME) {
		// �÷��̾� �̵�
		if (_kbhit()) {
			switch (_getch()) {
			case 65:
			case 97:
			case 75:
				if (playerX > 1) {
					playerX--;
				}
				break;
			case 68:
			case 100:
			case 77:
				if (playerX < GAME_WIDTH - 3) {
					playerX++;
				}
				break;
			case 87:
			case 119:
			case 72:
				if (playerY > 1) {
					playerY--;
				}
				break;
			case 83:
			case 115:
			case 80:
				if (playerY < GAME_HEIGHT - 2) {
					playerY++;
				}
				break;
			}
		}

		// ���۳� �̵�
		int movePos = rand() % 10;

		if (movePos == 0) {
			if (playerX > enemyX) {
				enemyX++;
			}
			else if (playerX < enemyX) {
				enemyX--;
			}
			else if (playerY > enemyY) {
				enemyY++;
			}
			else if (playerY < enemyY) {
				enemyY--;
			}
			else {
				// ���� ����
				state = OVER;
			}
		}
		else if (movePos == 1) {
			if (playerY > enemyY) {
				enemyY++;
			}
			else if (playerY < enemyY) {
				enemyY--;
			}
			else if (playerX > enemyX) {
				enemyX++;
			}
			else if (playerX < enemyX) {
				enemyX--;
			}
			else {
				// ���� ����
				state = OVER;
			}
		}

		// �� �浹
		if (starX == playerX && starY == playerY) {
			score++;
			starX = rand() % (GAME_WIDTH - 3) + 1;
			starY = rand() % (GAME_HEIGHT - 2) + 1;
		}
	}
}

void render() {
	if (state == TITLE) {
		gotoxy(4, 5);
		cout << "�������ڢ�";
		gotoxy(4, 10);
		cout << "<-^->����Ű�� �̵�";
		gotoxy(4, 12);
		cout << "@	<-���";
		gotoxy(4, 13);
		cout << "*	<-���� ��";
		gotoxy(4, 14);
		cout << "��	<-���� ��";
		gotoxy(4, 15);
		cout << "��	<-��";
	}
	else if (state == GAME) {
		// �� �׸���
		/*for (int y = 0; y < GAME_HEIGHT; y++) {
			for (int x = 0; x < GAME_WIDTH; x++) {
				gotoxy(x, y);
				cout << "��";
			}
		}*/

		/*for (int y = 1; y < GAME_HEIGHT - 1; y++) {
			for (int x = 1; x < GAME_WIDTH - 1; x++) {
				gotoxy(x, y);
				cout << " ";
			}
		}*/

		// �÷��̾� �׸���
		gotoxy(playerX, playerY);

		cout << "��";

		// ���۳� �׸���
		gotoxy(enemyX, enemyY);
		cout << "*";

		// �� �׸���
		gotoxy(starX, starY);
		cout << "��";

		// UI �׸���
		gotoxy(16, 0);
		cout << "SCORE: " << score;

		// �� ���� �����
		system("cls");
	}
	else if (state == OVER) {
		gotoxy(16, 8);
		cout << "GAME OVER";
		gotoxy(16, 10);
		cout << "SCORE: " << score;
	}
}

// TODO ������۸� ����