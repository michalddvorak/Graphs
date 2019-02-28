#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include "Coord.h"
#include "CharMatrix.h"

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

	size_t vertexCnt();

	bool addVertex(const coord &val);

	bool addEdge(const coord &from, const coord &to, double val);

	bool BFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool DFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Greedy(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Random(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

	bool Dijkstra(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded);

};
