#pragma once

#include <cstdlib>
#include <list>
#include <string>
#include <cstring>
#include <sstream>
#include "coord.h"

#define BLINK "\033[5m"
#define ATTRIBUTES_END "\033[0m"


class CharMatrix
{
public:
	CharMatrix(const size_t &rows, const size_t &cols) : rows(rows), cols(cols), totalsize(rows * cols)
	{
		internal_array = new char[totalsize];
	}

	CharMatrix(const CharMatrix &other) : rows(other.rows), cols(other.cols), totalsize(other.totalsize)
	{
		internal_array = new char[totalsize];
		memcpy(internal_array, other.internal_array, totalsize * sizeof(char));
	}

	virtual ~CharMatrix() { delete[](internal_array); }

	/**
	 * Gets the number of columns of this matrix.
	 * @return the number of columns of this matrix.
	 */
	size_t getCols() const { return cols; }

	/**
	 * Gets the number of rows of this matrix.
	 * @return the number of rows of this matrix.
	 */
	size_t getRows() const { return rows; }

	char &operator ()(const size_t &row, const size_t &col) { return internal_array[cols * row + col]; }

	const char &operator ()(const size_t &row, const size_t &col) const { return internal_array[cols * row + col]; }

	char &operator ()(const coord &coord) { return operator ()(coord.first, coord.second); }

	const char &operator ()(const coord &coord) const { return operator ()(coord.first, coord.second); }

	/**
	 * Fills this matrix with list of strings, each string.length() should be
	 * equal to cols and lines.size() should be equal to rows, otherwise this
	 * has undefined behaviour.
	 * @param lines - list of strings to be copied to this matrix
	 */
	void FillFromStrings(const std::list<std::string> &lines);

	friend std::ostream &operator <<(std::ostream &os, const CharMatrix &matrix);

	/**
	 * Checks bounds
	 * @param row - row to check
	 * @param col - col to check
	 * @return true if bounds are ok, othwerise false
	 */
	bool checkBounds(const size_t &row, const size_t &col) const { return (row < this->rows) && (col < this->cols); }

private:

	char * internal_array;
	const size_t rows, cols, totalsize;

};