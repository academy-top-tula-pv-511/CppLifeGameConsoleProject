#include <iostream>
#include <conio.h>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#include "Vector.h"
#include "Cell.h"
#include "Console.h"

Vector<Cell> colony;

void Generate();
int IsColony(const Cell& cell);

bool SetColony();
void ShowColony();

int main()
{
	if (SetColony())
	{
		Key key;
		CursorVisible(false);

		while (true)
		{
			if (_kbhit() && (Key)ReadKey() == Key::Esc)
				break;
			if (colony.size == 0)
				break;

			Generate();
			ShowColony();
			std::this_thread::sleep_for(500ms);
		}
	}
}

void Generate()
{
	int offsetsSize{ sizeof(offsets) / sizeof(Position) };

	// counting neighbors
	for (int i{}; i < colony.size; i++)
	{
		colony.items[i].neighbors = 0;
		for (int j{}; j < offsetsSize; j++)
		{
			int row{ colony.items[i].position.row + offsets[j].row };
			int column{ colony.items[i].position.column + offsets[j].column };
			Cell candidat;
			candidat.position.row = row;
			candidat.position.column = column;
			if (IsColony(candidat) != -1)
				colony.items[i].neighbors++;
		}
		if (colony.items[i].neighbors < 2 || colony.items[i].neighbors > 3)
			colony.items[i].type = CellType::Dead;
	}

	for (int i{}; i < colony.size; i++)
	{
		for (int j{}; j < offsetsSize; j++)
		{
			Cell candidat;
			candidat.position.row
				= colony.items[i].position.row + offsets[j].row;
			candidat.position.column
				= colony.items[i].position.column + offsets[j].column;
			candidat.type = CellType::Born;

			if (IsColony(candidat) == -1)
			{
				for (int k{}; k < offsetsSize; k++)
				{
					Cell temp;
					temp.position.row
						= candidat.position.row + offsets[k].row;
					temp.position.column
						= candidat.position.column + offsets[k].column;
					
					int index = IsColony(temp);
					if (index != -1)
					{
						if (colony.items[index].type != CellType::Born)
							candidat.neighbors++;
					}
				}

				if (candidat.neighbors == 3)
					PushBack(colony, candidat);
			}
		}
	}

	for (int i{}; i < colony.size; i++)
	{
		if (colony.items[i].type == CellType::Dead)
		{
			Remove(colony, i);
			i--;
		}
		else
			colony.items[i].type = CellType::Alife;
	}		
}

int IsColony(const Cell& cell)
{
	for (int i{}; i < colony.size; i++)
		if (Equile(cell, colony.items[i]))
			return i;
	return -1;
}

bool SetColony()
{
	int row{};
	int column{};

	Key key;

	bool isExit{};
	bool isQuit{};

	while (true)
	{
		if (_kbhit())
		{
			key = (Key)ReadKey();

			switch (key)
			{
			case ArrayLeft:
				if (column > 0)
					column--;
				break;
			case ArrayRight:
				column++;
				break;
			case ArrayUp:
				if (row > 0)
					row--;
				break;
			case ArrayDown:
				row++;
				break;
			case Space:
			{
				Cell candidat;
				candidat.position.row = row;
				candidat.position.column = column;

				int index = IsColony(candidat);
				if (index != -1)
					Remove(colony, index);
				else
					PushBack(colony, candidat);

				ShowColony();
				break;
			}
			case Esc:
				isExit = true;
				isQuit = true;
				break;
			case Enter:
				isExit = true;
				break;
			default:
				break;
			}

			if (isExit)
				break;

			SetPosition(row, column * 2);
		}
	}
	return !isQuit;
}

void ShowColony()
{
	Clear();
	for (int i{}; i < colony.size; i++)
	{
		int row = colony.items[i].position.row;
		int column = colony.items[i].position.column;

		if (row < 0 || column < 0) continue;

		WritePosition(row, column * 2, (char)178);
		WritePosition(row, column * 2 + 1, (char)178);
	}
}


