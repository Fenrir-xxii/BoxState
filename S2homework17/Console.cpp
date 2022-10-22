
#include "console.h"

void SetColor(ConsoleColor text, ConsoleColor background = BLACK)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}

void SetColor(short text, short background = BLACK)
{
	SetColor((ConsoleColor)text, (ConsoleColor)background);
}

void ResetColor()
{
	SetColor(WHITE, BLACK);
}

void SetCursorPosition(const COORD& coord) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetCursorPosition(short x, short y) //#include <Windows.h>
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getKey() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}
