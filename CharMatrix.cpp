#include "CharMatrix.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

CharMatrix::CharMatrix(size_t rows, size_t cols) : rows(rows), cols(cols), totalsize(rows * cols)
{
	internal_array = new char[totalsize];
}

CharMatrix::CharMatrix(const CharMatrix &other) : rows(other.rows), cols(other.cols), totalsize(other.totalsize)
{
	internal_array = new char[totalsize];
	memcpy(internal_array, other.internal_array, totalsize * sizeof(char));
}

CharMatrix::~CharMatrix()
{
	delete[](internal_array);
}

size_t CharMatrix::getCols() const { return cols; }

size_t CharMatrix::getRows() const { return rows; }

bool CharMatrix::checkBounds(size_t row, size_t col) const { return (row < this->rows) && (col < this->cols); }


char &CharMatrix::operator ()(size_t row, size_t col)
{
	if (!checkBounds(row, col))
		throw out_of_range("Index out of range");
	return internal_array[cols * row + col];
}

const char &CharMatrix::operator ()(size_t row, size_t col) const
{
	if (!checkBounds(row, col))
		throw out_of_range("Index out of range");
	return internal_array[cols * row + col];
}

char &CharMatrix::operator ()(coord coord)
{
	return operator ()(coord.first, coord.second);
}

const char &CharMatrix::operator ()(coord coord) const
{
	return operator ()(coord.first, coord.second);
}

bool CharMatrix::FillFromStringVec(list<string> &lines)
{
	size_t    i = 0;
	for (auto &it : lines)
	{
		strncpy(internal_array + i, it.c_str(), cols);
		i += cols;
	}
	return true;
}

ostream &operator <<(ostream &os, const CharMatrix &matrix)
{
	os << endl;
	for (size_t i = 0, q = 0; i < matrix.totalsize; q++)
	{
		auto const &cur = matrix.internal_array[i++];
		q &= -(q != matrix.cols); //If q reached cols, reset it to 0
		if (cur == 'O')
			os << "\033[31m" << cur << "\033[0m";
		else if (cur == 'S')
			os << "\033[32m" << cur << "\033[0m";
		else if (cur == 'E')
			os << "\033[33m" << cur << "\033[0m";
		else if (cur == 'o')
			os << "\033[34m" << cur << "\033[0m";
		else if (cur == '#')
			os << "\033[35m" << cur << "\033[0m";
		else
			os << cur;
		if (q == matrix.cols - 1)
			os << endl;
	}
	return os;
}




