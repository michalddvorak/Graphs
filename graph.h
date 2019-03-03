#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include "coord.h"
#include "charmatrix.h"
#ifdef SLEEP_LONG
	#define SLEEP_TIME 1s
#else
	#define SLEEP_TIME 0.05s
#endif
#ifdef NO_PRINT
	#define NO_SLEEP
#endif
using namespace std;

class Vertex
{
public:
	explicit Vertex(const coord &s);

	typedef pair<double, Vertex *> ve; //Adjacent vertex + distance (value of edge)
	vector<ve>                     adjacent; //Vector of adjacent edges
	coord                          data; //data in Vertex
};


class Graph
{
public:
	typedef map<coord, Vertex *> vertmap;
	vertmap                      vertices; //Map of vertices

	virtual ~Graph();

	Graph();

	size_t vertexCnt() { return vertices.size(); }

	bool addVertex(const coord &val);

	bool addEdge(const coord &from, const coord &to, double val);

	bool BFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool DFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Greedy(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Random(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Dijkstra(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Astar(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

private:
	size_t sqrdiffer(coord a, coord b)
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