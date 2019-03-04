#include "charmatrix.h"

std::string COLOR_BACKGROUND(int r, int g, int b)
{
	std::stringstream ss;
	ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
	std::string res;
	ss >> res;
	return res;
}

std::string COLOR_FONT(int r, int g, int b)
{
	std::stringstream ss;
	ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	std::string res;
	ss >> res;
	return res;
}

void CharMatrix::FillFromStrings(const std::list<std::string> &lines)
{
	size_t i = 0;
	for (auto &it : lines)
	{
		strncpy(internal_array + i, it.c_str(), cols);
		i += cols;
	}
}

std::ostream& operator <<(std::ostream &os, const CharMatrix &matrix)
{
	os << std::endl;
	for (size_t i = 0, q = 0; i < matrix.totalsize; q++)
	{
		auto const &cur = matrix.internal_array[i++];
		q &= -(q != matrix.cols); //If q reached cols, reset it to 0
		if (cur == 'O')
			os << COLOR_FONT(255,0,0) << cur << ATTRIBUTES_END; //Red
		else if (cur == 'S')
			os << COLOR_FONT(0,255,0) << cur << ATTRIBUTES_END; //Green
		else if (cur == 'E')
			os << COLOR_FONT(255,255,0) << cur << ATTRIBUTES_END; //Yellow
		else if (cur == 'o')
			os << COLOR_FONT(0,0,255) << BLINK << cur << ATTRIBUTES_END; //Blue
		else if (cur == '#')
			os << COLOR_FONT(255,0,255) << cur << ATTRIBUTES_END; //Magenta
		else if (cur == 'X')
			os << COLOR_BACKGROUND(0,0,0) << ' ' << ATTRIBUTES_END; //Black
		else
			os << cur;
		if (q == matrix.cols - 1)
			os << std::endl;
	}
	return os;
}