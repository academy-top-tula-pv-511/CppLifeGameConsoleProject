#pragma once
#include <Windows.h>
#include <conio.h>

enum Key
{
	ArrayLeft = 75,
	ArrayRight = 77,
	ArrayUp = 72,
	ArrayDown = 80,
	Space = 32,
	Esc = 27,
	Enter = 13
};

enum Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	LightGray,

	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

void SetBackColor(Color color);
void SetForeColor(Color color);

void SetPosition(int row, int column);
void Write(const char* message);
void Write(char symbol);

void WritePosition(int row, int column, const char* message);
void WritePosition(int row, int column, char symbol);

void CursorVisible(bool visible);

int ReadKey();

void Clear();