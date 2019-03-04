#include "graph.h"
#include <stack>
#include <queue>
#include <set>
#include <random>
#include <thread>
#include <limits>


using namespace std;
using Stack = stack<coord>;
using Queue = queue<coord>;
using DblCoordPair = pair<double, coord>;
using CoordDblPair = pair<coord, double>;
using CoordDblMap = map<coord, double>;
using CoordCoordMap = map<coord, coord>;
using Set = set<coord>;
using Vector = vector<coord>;


bool Contains(const Set &S, const coord &item)
{
	return S.find(item) != S.end();
}


/**
 * This class is needed by priority_queue
 */
class Comparer
{
public:
	inline bool operator ()(const DblCoordPair &a, const DblCoordPair &b) { return a.first > b.first; }
};

using PrQueue = priority_queue<DblCoordPair, vector<DblCoordPair>, Comparer>;

bool Graph::addVertex(const coord &val)
{
	if (vertices.find(val) == vertices.end())
	{
		auto * v = new Vertex(val);
		vertices[val] = v;
		return true;
	}
	cerr << "Vertex " << val << "already exists." << endl;
	return false;
}

bool Graph::addEdge(const coord &from, const coord &to, double val)
{
	auto itrf = vertices.find(from);
	auto itrt = vertices.find(to);

	if (itrf == vertices.end())
	{
		cerr << "Vertex " << from << " doesn't exist." << endl;
		return false;
	}
	if (itrt == vertices.end())
	{
		cerr << "Vertex " << to << " oesn't exist." << endl;
		return false;
	}

	Vertex * f = itrf->second;
	Vertex * t = itrt->second;

	auto edge = make_pair(val, t);
	f->adjacent.push_back(edge);
	return true;
}

list<coord> reconstruct_path(CoordCoordMap &prev, const coord &goal)
{
	auto        x     = goal;
	list<coord> path;
	const coord &comp = make_pair(0, 0);
	while (x != comp)
	{
		path.push_back(x);
		x = prev[x];
	}
	return path;
}


bool Graph::BFS(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	Set           open = {start};
	Set           closed;
	CoordCoordMap prev;
	Queue         queue;

	queue.push(start);

	while (!queue.empty())
	{
		auto x = queue.front();
		queue.pop();
		open.erase(x);

		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}

#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			auto curdata = it.second->data;

			if (!Contains(open, curdata) && !Contains(closed, curdata))
			{
				queue.push(curdata);
				open.insert(curdata);
				space(curdata) = 'O';

				prev[curdata] = x;
			}
		}

		closed.insert(x);
		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

/**
 * Function to return random number in rango lo - hi.
 * @param lo - lower bound.
 * @param hi - upper bound.
 * @return the random number.
 */
size_t random_number(const size_t &lo, const size_t &hi)
{
	srand((unsigned)time(nullptr));
	int random = rand();
	return lo + random % (hi - lo);
}

/**
 * Removes element from vector @vec at position @n.
 * @param vec - the vector.
 * @param n - the index from which to be removed.
 * @return data removed.
 */
coord remove_at(vector<coord> &vec, const size_t &n)
{
	coord res = vec[n];
	vec.erase(vec.begin() + n);
	return res;
}

bool
Graph::Random(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	Set           open = {start};
	Set           closed;
	CoordCoordMap prev;

	Vector random;


	random.push_back(start);

	while (!open.empty())
	{
		auto randindex = random_number(0, random.size());
		auto x         = remove_at(random, randindex);
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}

#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			const auto& curdata = it.second->data;

			if (!Contains(open, curdata) && !Contains(closed, curdata))
			{
				random.push_back(curdata);
				open.insert(curdata);
				space(curdata) = 'O';

				prev[curdata] = x;
			}
		}

		closed.insert(x);
		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool Graph::DFS(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	Set           open = {start};
	Set           closed;
	CoordCoordMap prev;
	Stack         stack;

	stack.push(start);

	while (!open.empty())
	{
		auto x = stack.top();
		stack.pop();
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}

#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			const auto& curdata = it.second->data;

			if (!Contains(open, curdata) && !Contains(closed, curdata))
			{
				stack.push(curdata);
				open.insert(curdata);
				prev[curdata] = x;
				space(curdata) = 'O';
			}
		}

		closed.insert(x);
		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool
Graph::Greedy(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	Set           open = {start};
	Set           closed;
	CoordCoordMap prev;

	PrQueue queue;

	queue.push(make_pair(squareHeuristics(start, end), start));

	while (!queue.empty())
	{
		auto x = queue.top().second;
		queue.pop();
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}

#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			const auto& curdata = it.second->data;

			if (!Contains(open, curdata) && !Contains(closed, curdata))
			{
				queue.push(make_pair(squareHeuristics(curdata, end), curdata));
				open.insert(curdata);

				prev[curdata] = x;
				space(curdata) = 'O';
			}
		}

		closed.insert(x);
		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool
Graph::Dijkstra(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	CoordDblMap   dist;
	CoordCoordMap prev;

	PrQueue queue;

	for (auto &it: vertices)
		dist[it.first] = numeric_limits<double>::infinity();

	dist[start] = 0;
	queue.push(make_pair(0, start));

	while (!queue.empty())
	{
		auto x = queue.top().second;
		queue.pop();
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}
#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			const auto& curdata = it.second->data;
			double d = dist[x] + it.first;

			if (d < dist[curdata])
			{
				dist[curdata] = d;
				queue.push(make_pair(d,curdata));

				prev[curdata] = x;
				space(curdata) = 'O';
			}
		}

		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool
Graph::Astar(const coord &start, const coord &end, CharMatrix &space, std::list<coord> &path, size_t &nodes_expanded)
{
	nodes_expanded = 0;
	CoordDblMap   dist;
	CoordCoordMap prev;

	PrQueue queue;

	for (auto &it: vertices)
		dist[it.first] = numeric_limits<double>::infinity();

	dist[start] = 0;
	queue.push(make_pair(squareHeuristics(start,end), start));

	while (!queue.empty())
	{
		auto x = queue.top().second;
		queue.pop();
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(start) = 'S';
			space(end)   = 'E';
			return true;
		}

#ifdef DEBUG
		cout << "Closing and expanding node " << x <<endl;
#endif
		for (auto &it: vertices[x]->adjacent)
		{
			const auto& curdata = it.second->data;
			double d = dist[x] + it.first;

			if (d < dist[curdata])
			{
				dist[curdata] = d;
				queue.push(make_pair(d + squareHeuristics(curdata, end),curdata));

				prev[curdata] = x;
				space(curdata) = 'O';
			}
		}

		space(x) = '#';
		nodes_expanded++;

#ifndef NO_PRINT
		cout << space << endl;
#endif
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}