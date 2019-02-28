#include "Maze.h"
#include "CharMatrix.h"
#include "Graph.h"
#include "Coord.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <thread>


bool Maze::readMaze(list<string> &lines, size_t &rows, size_t &cols)
{

	rows = cols = 0;
	string line;

	//Read first line
	getline(cin, line);

	//Get its length
	cols = line.length();

	//Create string 'cline' (control line) with s.length() amount of 'X'
	string cline(cols, 'X');

	//If s is not XXXXXXXXXXXXX...XXX (is not a wall), that's not correct
	if (line != cline)
		return false;
	//Else save it to buffer
	lines.push_back(line);
	while (true)
	{
		//Read next line
		getline(cin, line);

		//Wrong Input Handling
		if (line.length() != cols || line.at(0) != 'X' || line.at(cols - 1) != 'X')
			return false;
		for (char c : line)
			if (c != 'X' && c != ' ')
				return false;

		lines.push_back(line);
		//If another XXXXXXXXXXX...XXX (a wall) occurs, return true
		if (line == cline)
		{
			rows = lines.size();
			return true;
		}
	}
}

bool Maze::readStartEnd(coord &start, coord &end)
{
	string lstart, lend;
	if (!(getline(cin, lstart) && getline(cin, lend)))
		return false;
	istringstream ss_st(lstart);
	istringstream ss_en(lend);

	string dummy1;
	char   dummy2;
	if (!(ss_st >> dummy1 >> start.first >> dummy2 >> start.second)
	    || dummy1 != "start"
	    || dummy2 != ',')
		return false;
	if (!(ss_en >> dummy1 >> end.first >> dummy2 >> end.second)
	    || dummy1 != "end"
	    || dummy2 != ',')
		return false;
	ss_st.get();
	ss_en.get(); //try to read one more char
	return ss_st.eof() && ss_en.eof();
}

bool Maze::getNeighbours(size_t row, size_t col, const CharMatrix &matrix, Graph &graph)
{
	const auto &actpair = make_pair(row, col);
	if (!matrix.checkBounds(row, col))
		return false;
	// OOO
	// O O
	// OXO
	if (row != matrix.getRows() - 1 && matrix(row + 1, col) != 'X')
		graph.addEdge(actpair, make_pair(row + 1, col), 1);

	// OOO
	// O X
	// OOO
	if (col != matrix.getCols() - 1 && matrix(row, col + 1) != 'X')
		graph.addEdge(actpair, make_pair(row, col + 1), 1);

	// OXO
	// O O
	// OOO
	if (row != 0 && matrix(row - 1, col) != 'X')
		graph.addEdge(actpair, make_pair(row - 1, col), 1);

	// OOO
	// X O
	// OOO
	if (col != 0 && matrix(row, col - 1) != 'X')
		graph.addEdge(actpair, make_pair(row, col - 1), 1);
	return true;
}

void Maze::parseMatrixtoGraph(CharMatrix &maze_matrix, Graph &graph, char wall)
{
	//Make vertices for each existing (i,j)
	for (size_t i        = 0; i < maze_matrix.getRows(); i++)
	{
		for (size_t j = 0; j < maze_matrix.getCols(); j++)
		{
			char &curchar = maze_matrix(i, j);
			if (curchar == 'X')
				continue;
			else
				graph.addVertex(make_pair(i, j));
		}
	}
	//Connect vertices via edges
	for (size_t i        = 0; i < maze_matrix.getRows(); i++)
	{
		for (size_t j = 0; j < maze_matrix.getCols(); j++)
		{
			char &curchar = maze_matrix(i, j);
			if (curchar == 'X')
				continue;
			else
				Maze::getNeighbours(i, j, maze_matrix, graph);
		}
	}
}

bool Maze::solveMaze(Algorithm alg)
{
	size_t rows, cols;
	rows = cols = 0;
	list<string> lines;
	if (!readMaze(lines, rows, cols))
	{
		cout << "Error reading maze array" << endl;
		return false;
	}

	//read coords
	coord start, end;
	if (!readStartEnd(start, end))
	{
		cout << "Error reading start/end coords" << endl;
		return false;
	}


	//Parse to m x n matrix

	CharMatrix maze_matrix(rows, cols);
	maze_matrix.FillFromStringVec(lines);
	//Reconstruct graph

	//swap indices?
	size_t tmp = start.first;
	start.first = start.second;
	start.second = tmp;

	tmp = end.first;
	end.first = end.second;
	end.second = tmp;


	Graph graph;
	parseMatrixtoGraph(maze_matrix,graph);


	list<coord> result;
	size_t      expanded = 0;
	switch (alg)
	{
		case BFS :
		{
			if (graph.BFS(start, end, maze_matrix, result, expanded))
			{
				break;
			} else
			{
				cout << "Nemá řešení =(" << endl;
				return false;
			}
		}
		case DFS :
		{
			if (graph.DFS(start, end, maze_matrix, result, expanded))
			{
				break;
			} else
			{
				cout << "Nemá řešení =(" << endl;
				return false;
			}
		}
		case Random:
		{
			if (graph.Random(start, end, maze_matrix, result, expanded))
			{
				break;
			} else
			{
				cout << "Nemá řešení =(" << endl;
				return false;
			}
		}
		case Greedy:
		{

		}
		case Dijkstra:
		{

		}
		case Astar:
		{

		}

	}
	cout << "Reconstructing path" << endl;
	//Path it!

	for (auto &coord : result)
	{
		if (coord != result.front() && coord != result.back())
			maze_matrix(coord) = 'o';
		std::this_thread::sleep_for(SLEEP_TIME);
		//cout << maze_matrix << endl;
	}
	//And print it!
	cout << maze_matrix << endl;
	cout << "Expanded " << expanded << " nodes" << endl;
	cout << "Path length: " << result.size() << endl;
	cout << "# - closed, X - wall, O - open, o - path" << endl;
	return true;


}
