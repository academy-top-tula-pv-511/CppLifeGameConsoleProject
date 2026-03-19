#include <iostream>

#include "Vector.h"
#include "Cell.h"

Vector<Cell> colony;
void Generate();

int IsColony(const Cell& cell);

int main()
{
	PushBack(colony, Cell{ 5, 5 });
	PushBack(colony, Cell{ 5, 6 });
	PushBack(colony, Cell{ 5, 7 });

	Generate();

	std::cout << "\n";
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

	//for (int i{}; i < colony.size; i++)
		
}

int IsColony(const Cell& cell)
{
	for (int i{}; i < colony.size; i++)
		if (Equile(cell, colony.items[i]))
			return i;
	return -1;
}
