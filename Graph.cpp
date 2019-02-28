//
// Created by mdvorak on 21.2.19.
//

#include "Graph.h"
#include "Coord.h"
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <thread>
#define SLEEP_TIME 0.005s

Vertex::Vertex(const coord &s) : data(s) { }


Graph::Graph() = default;

Graph::~Graph()
{
	for (auto &it : vertices)
		delete (it.second);
}


bool Graph::addVertex(const coord &name)
{
	auto itr = vertices.find(name); //iterator
	if (itr == vertices.end()) // if end was reached, we didnt find the vertex with name, we create a new one
	{
		auto * v = new Vertex(name);
		vertices[name] = v;
		return true;
	}
	cerr << "Vertex \"(" << name.first << ", " << name.second << ")\" already exists." << endl;
	return false;
}

bool Graph::addEdge(const coord &from, const coord &to, double val)
{
	auto itrf = vertices.find(from);
	auto itrt = vertices.find(to);
	if (itrf == vertices.end())
	{
		cerr << "Vertex \"" << from << "\" doesn't exist." << endl;
		return false;
	}
	if (itrt == vertices.end())
	{
		cerr << "Vertex \"" << to << "\" doesn't exist." << endl;
		return false;
	}
	Vertex * f = itrf->second;
	Vertex * t = itrt->second;
	auto edge = make_pair(val, t);
	f->adjacent.push_back(edge);
	return true;
}


inline size_t Graph::vertexCnt() { return vertices.size(); }


list<coord> reconstruct_path(map<coord, coord> prev, coord goal)
{
	auto                       x     = goal;
	list<coord>                path;
	const pair<size_t, size_t> &comp = make_pair(0, 0);
	while (x != comp) //dangerous, but (0,0) will never be a valid point, so if returned it is really an end
	{
		path.push_back(x);
		x = prev[x];
	}
	return path;
}


bool Graph::BFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex \"(" << start << "\" does not exist.";
		return false;
	}


	map<coord, bool>  open; //queue = open
	map<coord, bool>  closed;
	map<coord, coord> prev;

	queue<coord> queue;


	//Mark every node as not open
	for (auto &it : vertices)
		open[it.first] = false;


	queue.push(start);
	while (!open.empty())
	{
		//Pop front from queue
		auto x = queue.front();
		queue.pop();

		//Open it
		open[x] = true;
		space(x) = '#';

		//If it is the end, reconstruct path and return
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}

		//Expand node 'x'
		nodes_expanded++;
		cout << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				queue.push(curdata); //push it to the front
				open[curdata] = true; //open it
				prev[curdata] = x; //save path

				space(curdata) = 'O';
			}
		}
		//Close node 'x'
		closed[x] = true;

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
		std::this_thread::sleep_for(SLEEP_TIME);
	}
	return false;
}

size_t random_number(size_t lo, size_t hi)
{
	srand((unsigned)time(nullptr));
	int random = rand();
	return lo + random % (hi - lo);
}

coord remove_at(std::vector<coord>&v, std::vector<coord>::size_type n)
{
	coord res = std::move_if_noexcept(v[n]);
	v[n] = std::move_if_noexcept(v.back());
	v.pop_back();
	return res;
}

bool Graph::Random(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}

	map<coord, bool>  open; //queue = open
	map<coord, bool>  closed;
	map<coord, coord> prev;

	vector<coord> random;


	//Mark every node as not open
	for (auto &it : vertices)
		open[it.first] = false;


	random.push_back(start);
	while (!open.empty())
	{

		size_t randindex = random_number(0,random.size());
		//Pop front from queue
		auto x = remove_at(random,randindex);

		//Open it
		open[x] = true;
		space(x) = '#';

		//If it is the end, reconstruct path and return
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}

		//Expand node 'x'
		nodes_expanded++;
		cout << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				random.push_back(curdata); //push it to the front
				open[curdata] = true; //open it
				prev[curdata] = x; //save path

				space(curdata) = 'O';
			}
		}
		//Close node 'x'
		closed[x] = true;

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
		std::this_thread::sleep_for(SLEEP_TIME);
	}
	return false;
}

bool Graph::DFS(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}


	map<coord, bool>  open; //queue = open
	map<coord, bool>  closed;
	map<coord, coord> prev;

	stack<coord> stack;


	//Mark every node as not open
	for (auto &it : vertices)
		open[it.first] = false;


	stack.push(start);
	while (!open.empty())
	{
		//Pop front from queue
		auto x = stack.top();
		stack.pop();

		//Open it
		open[x] = true;
		space(x) = '#';

		//If it is the end, reconstruct path and return
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}

		//Expand node 'x'
		nodes_expanded++;
		cout << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				stack.push(curdata); //push it to the front
				open[curdata] = true; //open it
				prev[curdata] = x; //save path

				space(curdata) = 'O';
			}
		}
		//Close node 'x'
		closed[x] = true;

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
		std::this_thread::sleep_for(SLEEP_TIME);
	}
	return false;
}

bool Graph::Greedy(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{

}

bool Graph::Dijkstra(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{

}



