#pragma once

#include "Coord.h"
#include "Graph.h"
#include "CharMatrix.h"
#include <vector>

enum Algorithm
{
	BFS, DFS, Random, Greedy, Astar, Dijkstra
};

class Maze
{
private:

	static bool getNeighbours(size_t row, size_t col, const CharMatrix &matrix, Graph &graph);

	static void parseMatrixtoGraph(CharMatrix &maze_matrix, Graph &graph, char wall = 'X');

	static bool readMaze(list<string> &lines, size_t &rows, size_t &cols);

	static bool readStartEnd(coord &start, coord &end);

public:

	Maze() = delete;

	bool solveMaze(Algorithm alg);


};