#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "charmatrix.h"


#ifdef SLEEP_LONG
#define SLEEP_TIME 1s
#else
#define SLEEP_TIME 0.05s
#endif

#ifdef NO_PRINT
#define NO_SLEEP
#endif


struct Vertex
{
	explicit Vertex(const coord &s) : data(s) { }

	std::vector<std::pair<double, Vertex *>> adjacent;
	coord                                    data;
};

class Graph
{
public:
	std::map<coord, Vertex *> vertices;

	virtual ~Graph()
	{
		for (auto &it: vertices)
			delete it.second;
	}

	Graph() = default;

	/**
	 * Adds vertex to this graph. If vertex with the same data already exists, this returns
	 * false.
	 * @param val - value to be stored in the vertex
	 * @return true if vertex was successfully added, false otherwise.
	 */
	bool addVertex(const coord &val);

	/**
	 * Adds edge connecting vertices with data @from and @to. If vertices @from or @to do
	 * not exist, this function return false.
	 * @param from - vertex where new edge begins
	 * @param to - vertex where new edge ends
	 * @param val - value of the edge
	 * @return true if edge was successfully added, false otherwise.
	 */
	bool addEdge(const coord &from, const coord &to, double val);

	/**
	 * Breadth first search
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool BFS(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

	/**
	 * Depth first search
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool DFS(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

	/**
	 * Random search
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool
	Random(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

	/**
	 * Dijkstra's algorithm
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool
	Dijkstra(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

	/**
	 * Greedy algorithm
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool
	Greedy(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

	/**
	 * A* algorithm
	 * @param start - starting coord of the algorithm
	 * @param end - ending coord of the algorithm
	 * @param space - matrix which representing 2D array on which the algorithm acts.
	 * @param path - here the final path is stored, if path was not found, this remains unchanged.
	 * @param nodes_expanded - amount of nodes expanded during the algorithm.
	 * @return true if path was found, false otherwise.
	 */

	bool Astar(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded);

private:

	double squareHeuristics(const coord &a, const coord &b)
	{
		size_t res = 0;
		if (a.first > b.first)
			res += a.first - b.first;
		else
			res += b.first - a.first;
		if (a.second > b.second)
			res += a.second - b.second;
		else
			res += b.second - a.second;
		return res;
	}
};