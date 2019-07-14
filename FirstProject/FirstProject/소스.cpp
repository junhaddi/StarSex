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

// 게임 설정 초기화
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
	setTitle("별따먹자♥");
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
		// 플레이어 이동
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

		// 나쁜놈 이동
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
				// 게임 오버
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
				// 게임 오버
				state = OVER;
			}
		}

		// 별 충돌
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
		cout << "별따먹자♥";
		gotoxy(4, 10);
		cout << "<-^->방향키로 이동";
		gotoxy(4, 12);
		cout << "@	<-당신";
		gotoxy(4, 13);
		cout << "*	<-나쁜 놈";
		gotoxy(4, 14);
		cout << "■	<-나쁜 놈";
		gotoxy(4, 15);
		cout << "★	<-별";
	}
	else if (state == GAME) {
		// 벽 그리기
		/*for (int y = 0; y < GAME_HEIGHT; y++) {
			for (int x = 0; x < GAME_WIDTH; x++) {
				gotoxy(x, y);
				cout << "■";
			}
		}*/

		/*for (int y = 1; y < GAME_HEIGHT - 1; y++) {
			for (int x = 1; x < GAME_WIDTH - 1; x++) {
				gotoxy(x, y);
				cout << " ";
			}
		}*/

		// 플레이어 그리기
		gotoxy(playerX, playerY);

		cout << "＠";

		// 나쁜놈 그리기
		gotoxy(enemyX, enemyY);
		cout << "*";

		// 별 그리기
		gotoxy(starX, starY);
		cout << "★";

		// UI 그리기
		gotoxy(16, 0);
		cout << "SCORE: " << score;

		// 백 버퍼 지우기
		system("cls");
	}
	else if (state == OVER) {
		gotoxy(16, 8);
		cout << "GAME OVER";
		gotoxy(16, 10);
		cout << "SCORE: " << score;
	}
}

// TODO 더블버퍼링 구현