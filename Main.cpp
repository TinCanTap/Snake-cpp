#include <Windows.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>

void refresh(int fruitx, int fruity, std::vector<int> snake);

int level = 1;

inline int random(int mini, int maxi) {
	int result = ((rand() % (maxi - (mini) + 1)) + mini);
	return result;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	SetConsoleTitleW(L"malware.exe");
	ShowConsoleCursor(false);
	srand(time(NULL));
	bool mustbreak = 0;
	int dir = 2;
	std::vector<int> snack = { 14, 7, 13, 7, 12, 7 };
	int footx = 22;
	int footy = 7;
	int tempdir = 0;
	while (1 == 1) {
		for (int j = 1; j <= 6; j++) { //KEY INPUTS
			SHORT keyState = GetKeyState(VK_UP);
			if (bool(keyState & 0x8000) == 1) {
				tempdir = 1;
			}
			else {
				keyState = GetKeyState(VK_RIGHT);
				if (bool(keyState & 0x8000) == 1) {
					tempdir = 2;
				}
				else {
					keyState = GetKeyState(VK_DOWN);
					if (bool(keyState & 0x8000) == 1) {
						tempdir = 3;
					}
					else {
						keyState = GetKeyState(VK_LEFT);
						if (bool(keyState & 0x8000) == 1) {
							tempdir = 4;
						}
						else {
							tempdir = 0;
						}
					}
				}
			}
			Sleep(18);
		}
		if (tempdir != 0) {
			if (dir == 1 && tempdir != 3 || dir == 2 && tempdir != 4 || dir == 3 && tempdir != 1 || dir == 4 && tempdir != 2) { //if snake is not turning backwards, it can turn
				dir = tempdir;
			}
		}
		if (dir == 1 && snack[1] + 1 == 14 || dir == 2 && snack[0] + 1 == 31 || //check if running into border
			dir == 3 && snack[1] - 1 == 0 || dir == 4 && snack[0] - 1 == 2) {
			break;
		}
		else {
			if (dir == 1 && footx == snack[0] && footy == snack[1] + 1 ||
				dir == 2 && footx == snack[0] + 1 && footy == snack[1] ||
				dir == 3 && footx == snack[0] && footy == snack[1] - 1 ||
				dir == 4 && footx == snack[0] - 1 && footy == snack[1]) {
				level++;
				int sips = snack.size();
				std::vector<int> tempclone = {};
				for (int cloner = 0; cloner <= sips - 1; cloner++) {
					tempclone.push_back(snack[cloner]);
				}
				snack.push_back(snack[sips - 2]); //adds to snake body when eating fruit
				snack.push_back(snack[sips - 1]);
				snack.push_back(snack[sips + 1]);
				snack.push_back(snack[sips]);
				for (int q = 2; q <= sips + 1; q++) { //moves snake forwards
					snack[q] = tempclone[q - 2];
				}
				if (dir == 1) { //changes position of head based on direction
					snack[1] += 1;
				}
				else if (dir == 2) {
					snack[0] += 1;
				}
				else if (dir == 3) {
					snack[1] -= 1;
				}
				else if (dir == 4) {
					snack[0] -= 1;
				}
				footx = random(3, 25);
				footy = random(4, 12);
				bool cango = 0;
				while (cango == 0) {
					for (int y = 0; y <= snack.size() - 1; y++) {
						if (y % 2 == 0 && footx == snack[y]) {
							footx = random(3, 26);
						}
						else if (y % 2 == 1 && footy == snack[y]) {
							footy = random(3, 12);
						}
						else {
							cango = 1;
						}
					}
				}
			}
			else {
				int sips = snack.size();
				std::vector<int> tempclone = {};
				for (int cloner = 0; cloner <= sips - 1; cloner++) {
					tempclone.push_back(snack[cloner]);
				}
				for (int q = 2; q <= sips - 1; q++) {
					snack[q] = tempclone[q - 2];
				}
				if (dir == 1) {
					snack[1] += 1;
				}
				else if (dir == 2) {
					snack[0] += 1;
				}
				else if (dir == 3) {
					snack[1] -= 1;
				}
				else if (dir == 4) {
					snack[0] -= 1;
				}
			}
			/*if (snack.size() >= 6) {
				for (int i = 2; i <= snack.size() - 1; i += 2) { //check if snake runs into itself
					if (dir == 1 && snack[0] == snack[i] && snack[1] == snack[i+1] - 1) { //going up
						mustbreak = 1;
					}
					else if (dir == 2 && snack[0] == snack[i] - 1 && snack[1] == snack[i + 1]) { //going right
						mustbreak = 1;
					}
					else if (dir == 3 && snack[0] == snack[i] && snack[1] == snack[i + 1]+1) { //going down
						mustbreak = 1;
					}
					else if (dir == 4 && snack[0] == snack[i] + 1 && snack[1] == snack[i + 1]) { //going left
						mustbreak = 1;
					}
				}
			}
			*/
			refresh(footx, footy, snack);
		}

		if (mustbreak == 1) {
			break;
		}
	}
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cord; cord.X = 0; cord.Y = 15;
	SetConsoleCursorPosition(hand, cord);
	system("pause");
	return 0;
}
