#pragma once

#include <cstdlib>
#include <list>
#include <string>
#include "Coord.h"

using namespace std;

class CharMatrix
{
public:
	CharMatrix(size_t rows, size_t cols);

	CharMatrix(const CharMatrix &other);

	virtual ~CharMatrix();

	char& operator ()(size_t row, size_t col);

	const char& operator ()(size_t row, size_t col) const;

	char& operator ()(coord coord);

	const char& operator ()(coord coord) const;

	bool FillFromStringVec(list<string> &lines);

	friend ostream &operator <<(ostream &os, const CharMatrix &matrix);

	size_t getRows() const;

	size_t getCols() const;

	bool checkBounds(size_t row, size_t col) const;

private:
	char * internal_array;
	const size_t rows, cols, totalsize;
};
