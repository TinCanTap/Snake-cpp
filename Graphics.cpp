#include <stdlib.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
//COLORS LIST
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white
//Numbers after 15 include background colors
static std::string lastframe[15] = 
{"                              ",
"                              ",
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", 
"                              ", };
static std::string currentframe[15] = {};
static HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int col = 15;
int lastcol = 0;
bool firsttime = 0;
void refresh(int fruitx, int fruity, std::vector<int> snake) {
	if (firsttime == 0) { firsttime = 1; system("cls"); };
	for (int clearst = 0; clearst <= 14; clearst++) {
		currentframe[clearst] = {};
	}
	for (int a = 1; a <= 15; a++) {
		for (int b = 1; b <= 30; b++) {
			if (b == 1 || b == 30 || a == 1 || a == 15) {
				currentframe[a - 1] += '#'; //print border
				col = 15;
			}
			else if (snake[1]== (15-a) && snake[0] == b+1) { //snake[1] is head Y, snake[0] is head X
				currentframe[a - 1] += '+'; //print snake head
				col = 10;
			}
			else {
				if (fruity == 15-a && fruitx == b+1) { //check whether fruit is there
					currentframe[a - 1] += 'O';
					col = 12;
				}
				else { //check whether snake body is there
					bool found = 0; 
					for (int parse = 0; parse <= (snake.size() / 2) - 1; parse+=2) { //looks through vector
						if (snake[parse+1] == (15 - a) && snake[parse] == b +1) { // +1 is to compensate for border
							found = 1;
							break;
						}
					}
					if (found == 1) {
						currentframe[a - 1] += '%'; //print snake body
						col = 10;
					}
					else {
						currentframe[a - 1] += ' '; //print nothing, if all else fails
					}
				}
			}
			if ((currentframe[a - 1].at(b-1)) != (lastframe[a - 1].at(b - 1)) || lastcol != col) {
				COORD cord; cord.X = b - 1; cord.Y = a - 1;
				Color(col);
				SetConsoleCursorPosition(hand, cord);
				std::cout << (currentframe[a - 1].at(b - 1));
			}
			lastcol = col;
		}
	}
	for (int i = 0; i <= 14; i++) {
		lastframe[i] = currentframe[i];
	}
}
