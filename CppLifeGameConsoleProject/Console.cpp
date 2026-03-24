#include "Console.h"

HANDLE outConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
HANDLE inConsole{ GetStdHandle(STD_INPUT_HANDLE) };

void SetBackColor(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outConsole, &info);
	
	WORD colorCurrent{ info.wAttributes };
	WORD colorNew = (colorCurrent & 0b1111) | ((WORD)color << 4);

	SetConsoleTextAttribute(outConsole, colorNew);
}

void SetForeColor(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outConsole, &info);

	WORD colorCurrent{ info.wAttributes };
	WORD colorNew = ((colorCurrent >> 4) << 4) | (WORD)color;

	SetConsoleTextAttribute(outConsole, colorNew);
}

void SetPosition(int row, int column)
{
	COORD position;
	position.X = column;
	position.Y = row;
	SetConsoleCursorPosition(outConsole, position);
}

void Write(const char* message)
{
	LPDWORD writter{};
	WriteConsoleA(
		outConsole,
		message,
		strlen(message),
		writter,
		nullptr);
}

void Write(char symbol)
{
	const char* message = new char[2] { symbol, '\0' };
	Write(message);
}

void WritePosition(int row, int column, const char* message)
{
	SetPosition(row, column);
	Write(message);
}

void WritePosition(int row, int column, char symbol)
{
	SetPosition(row, column);
	Write(symbol);
}

void CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(outConsole, &info);
	info.bVisible = visible;
	SetConsoleCursorInfo(outConsole, &info);
}

int ReadKey()
{
	return _getch();
}

void Clear()
{
	system("cls");
}
