#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "ConsoleFunctions.h"

using namespace std;

#pragma comment(lib, "winmm.lib")
#define FPS 60
#define GAME_WIDTH 40
#define GAME_HEIGHT 20
#define SOUND_FILE_NAME "bgm.wav"

enum State {
	TITLE,
	GAME,
	OVER,
};

// 게임 설정 초기화
State state;
int score;
int playerX, playerY, _playerX, _playerY;
int enemyX, enemyY, _enemyX, _enemyY;
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
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	reset();
}

void reset() {
	score = 0;
	playerX = GAME_WIDTH / 2;
	playerY = GAME_HEIGHT / 2;
	_playerX = playerX;
	_playerY = playerY;
	enemyX = rand() % (GAME_WIDTH - 3) + 1;
	enemyY = rand() % (GAME_HEIGHT - 2) + 1;
	_enemyX = enemyX;
	_enemyY = enemyY;
	starX = rand() % (GAME_WIDTH - 3) + 1;
	starY = rand() % (GAME_HEIGHT - 2) + 1;
	system("cls");
}

void update() {
	if (state == TITLE || state == OVER) {
		if (_kbhit() && _getch() == ' ') {
			state = GAME;
			reset();
		}
	}
	else if (state == GAME) {
		// 플레이어 이동
		_playerX = playerX;
		_playerY = playerY;

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
		_enemyX = enemyX;
		_enemyY = enemyY;
		int movePos = rand() % 15;

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
			gotoxy(starX, starY);
			cout << " ";
			starX = rand() % (GAME_WIDTH - 3) + 1;
			starY = rand() % (GAME_HEIGHT - 2) + 1;
		}
	}
}

void render() {
	if (state == TITLE) {
		gotoxy(4, 5);
		cout << "별따먹자♥        <START: SPACE>";
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
		// 플레이어 그리기
		gotoxy(_playerX, _playerY);
		cout << " ";
		gotoxy(playerX, playerY);
		cout << "＠";

		// 나쁜놈 그리기
		gotoxy(_enemyX, _enemyY);
		cout << " ";
		gotoxy(enemyX, enemyY);
		cout << "*";

		// 별 그리기
		gotoxy(starX, starY);
		cout << "★";

		// UI 그리기
		gotoxy(16, 0);
		cout << "SCORE: " << score;
	}
	else if (state == OVER) {
		gotoxy(16, 8);
		cout << "GAME OVER";
		gotoxy(15, 10);
		cout << "<RE: SPACE>";
	}
}