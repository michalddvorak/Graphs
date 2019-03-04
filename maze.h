#pragma once

#include "coord.h"
#include "charmatrix.h"
#include "graph.h"
#include <vector>
#include <iostream>

enum Algorithm
{
	BFS, DFS, Random, Greedy, Astar, Dijkstra
};

class Maze
{
private:
	/**
	 * Retrieves all neighbours from @matrix at [@rows, @cols] index. Adds edges to @graph.
	 * @param row - the row index.
	 * @param col - the col index.
	 * @param matrix - matrix to read from.
	 * @param graph - graph to make connections in.
	 * @return true if addition was successful, false if rows or cols are out of range.
	 */
	static bool getNeighbours (size_t& row, size_t& col, const CharMatrix& matrix, Graph& graph);

	/**
	 * Extracts @maze_matrix matrix and reconstructs a graph from it and save it to @graph.
	 * @param maze_matrix - the input matrix
	 * @param graph - the graph
	 * @param wall - letter representing a wall in @maze_matrix, default 'X'.
	 */

	static void parseMatrixToGraph(const CharMatrix& maze_matrix, Graph& graph, char wall = 'X');

	/**
	 * Reads maze from inputstream @istream (default std::cin).
	 * @param lines - list of strings to which the entire stream will be parsed to.
	 * @param rows - amount of rows read.
	 * @param cols - amount of cols read.
	 * @return true if read was successful, false otherwise.
	 */
	static bool readMaze(std::list<std::string> & lines, size_t &rows, size_t &cols, std::istream& is = std::cin);

	/**
	 * Reads the start and end coordinates for the maze solving problem.
	 * @param start - start coord.
	 * @param end - end coord.
	 * @return true if read was successful, false otherwise.
	 */
	static bool readStartEnd(coord& start, coord& end, std::istream& is = std::cin);

public:

	Maze() = delete;
	/**
	 * Solves a MAZE!
	 * @param alg - algorithm to be used.
	 * @return true if maze was successfully solved, false otherwise.
	 */
	static bool solveMaze(Algorithm alg);
};