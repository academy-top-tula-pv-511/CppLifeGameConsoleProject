#pragma once

struct Position
{
	int row;
	int column;
};

enum CellType
{
	Alife,
	Dead,
	Born
};

struct Cell
{
	Position position{};
	CellType type{ CellType::Alife };
	int neighbors{};
};

bool Equile(const Cell& left, const Cell& right)
{
	return left.position.row == right.position.row
		&& left.position.column == right.position.column;
}

Position offsets[]{ {-1, -1}, {-1, 0}, {-1, 1},
					{0, -1}, {0, 1},
					{1, -1}, {1, 0}, {1, 1} };
