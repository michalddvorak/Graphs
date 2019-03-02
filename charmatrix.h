#pragma once

#include <cstdlib>
#include <list>
#include <string>
#include "coord.h"

using namespace std;

class CharMatrix
{
public:
	CharMatrix(size_t rows, size_t cols);

	CharMatrix(const CharMatrix &other);

	virtual ~CharMatrix()
	{
		delete[](internal_array);
	}

	size_t getCols() const { return cols; }

	size_t getRows() const { return rows; }

	bool checkBounds(size_t row, size_t col) const { return (row < this->rows) && (col < this->cols); }


	char &operator ()(size_t row, size_t col)
	{
		if (!checkBounds(row, col))
			throw out_of_range("Index out of range");
		return internal_array[cols * row + col];
	}

	const char &operator ()(size_t row, size_t col) const
	{
		if (!checkBounds(row, col))
			throw out_of_range("Index out of range");
		return internal_array[cols * row + col];
	}

	char &operator ()(coord coord)
	{
		return operator ()(coord.first, coord.second);
	}

	const char &operator ()(coord coord) const
	{
		return operator ()(coord.first, coord.second);
	}

	bool FillFromStringVec(list<string> &lines);

	friend ostream &operator <<(ostream &os, const CharMatrix &matrix);

private:
	char * internal_array;
	const size_t rows, cols, totalsize;
};