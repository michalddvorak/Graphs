//
// Created by mdvorak on 21.2.19.
//

#include "graph.h"
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <thread>
#include <limits>

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
		cerr << "Vertex " << start << " or " << end << " does not exist.";
		return false;
	}
	/**
	 * We store vertices in 3 structures. Node is in an open set if and only if it is in a queue.
	 * Open nodes are those which can be expanded, after they've been expanded, they become closed.
	 * Initially, nothing is open and nothing is closed.
	 * Prev is used to reconstruct path
	 */
	map<coord, bool> open;
	map<coord, bool> closed;

	map<coord, coord> prev;

	queue<coord> queue;

	//We start by opening the start node
	queue.push(start);
	open[start] = true;

	//While there are open nodes to be expanded

	while (!queue.empty())
	{
		//Pop front from queue
		auto x = queue.front();
		queue.pop();

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
		for (auto &it : vertices[x]->adjacent) //Loop through all x's adjacent nodes
		{
			const auto &curdata = it.second->data; //Const reference to current node

			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				queue.push(curdata); //Push it to the queue

				open[curdata] = true; //Open it
				space(curdata) = 'O';

				prev[curdata] = x; //save path

			}
		}
		//Close node 'x'
		closed[x] = true;
		space(x) = '#';

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

size_t random_number(size_t lo, size_t hi)
{
	srand((unsigned)time(nullptr));
	int random = rand();
	return lo + random % (hi - lo);
}

coord remove_at(std::vector<coord> &v, std::vector<coord>::size_type n)
{
	coord res = v[n];
	v.erase(v.begin() + n);
	return res;
}

bool Graph::Random(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}
	/**
	 * We store vertices in 3 structures - @open, @closed, @random. Node is in @open if
	 * and only if it is in a @random. Nodes in @open are those which can be expanded,
	 * after they've been expanded, they become in @closed. Initially, nothing is open
	 * and nothing is closed. set @prev is used to reconstruct path.
	 */
	map<coord, bool> open; //queue = open
	map<coord, bool> closed;

	map<coord, coord> prev;

	vector<coord> random;

	random.push_back(start);
	open[start] = true;

	while (!open.empty())
	{

		size_t randindex = random_number(0, random.size());
		//Pop front from queue
		auto   x         = remove_at(random, randindex);



		//If it is the end, reconstruct path and return
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}

		//Expand node 'x'
		nodes_expanded++;
		cout << "\033[2J" << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				random.push_back(curdata); //push it to the front
				open[curdata] = true; //open it
				space(curdata) = 'O';

				prev[curdata] = x; //save path

			}
		}
		//Close node 'x'
		closed[x] = true;
		space(x) = '#';

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
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


	stack.push(start);
	while (!open.empty())
	{
		//Pop front from queue
		auto x = stack.top();
		stack.pop();

		//If it is the end, reconstruct path and return
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}

		//Expand node 'x'
		nodes_expanded++;
		cout << "\033[2J" << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				stack.push(curdata); //push it to the front
				open[curdata] = true; //open it
				space(curdata) = 'O';

				prev[curdata] = x; //save path

			}
		}
		//Close node 'x'
		closed[x] = true;
		space(x) = '#';

		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}


bool Graph::Astar(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}

	map<coord, double>              dist;
	map<coord, coord>               prev;
	multimap<double, coord, less<>> queue;
	for (auto                       &it:vertices)
		dist[it.first] = std::numeric_limits<double>::infinity();

	dist[start] = 0;
	queue.insert(make_pair(sqrdiffer(start, end), start));

	while (!queue.empty())
	{
		auto x = queue.begin()->second;
		queue.erase(queue.begin());//extract element with least distance
		//If it is the end, reconstruct path and return

		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}
		//Expand node 'x'
		nodes_expanded++;
		cout << "\033[2J" << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			const auto &curdata = it.second->data; //take actual neighbour and get its coord
			double     d        = dist[x] + it.first; //d = distance to x + distance to it;
			bool       isbetter = d < dist[curdata];

			if (isbetter) //If we can to curdata with less distance than we already did once
				//update it, if curdata was unvisited, this always occurs
			{
				dist[curdata] = d; // insert this better result
				queue.insert(make_pair(d+sqrdiffer(curdata,end), curdata)); //update curdata in distances
				prev[curdata] = x; //for path

				space(curdata) = 'O'; //dec
			}
		}
		space(x) = '#';
		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool Graph::Greedy(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}

	map<coord, bool>  open; //queue = open
	map<coord, bool>  closed;
	map<coord, coord> prev;

	multimap<double, coord, less<>> queue;
	queue.insert(make_pair(sqrdiffer(start, end), start));

	while (!queue.empty())
	{
		auto x   = queue.begin()->second;
		queue.erase(queue.begin());
		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}
		//Expand node 'x'
		nodes_expanded++;
		cout << "\033[2J" << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			//current node
			auto curdata = it.second->data;
			//If it is not open or closed already
			if (!closed[curdata] && !open[curdata])
			{
				queue.insert(make_pair(sqrdiffer(curdata, end), curdata)); //push it to the front
				open[curdata] = true; //open it
				prev[curdata] = x; //save path
				space(curdata) = 'O';
			}
		}
		closed[x] = true;
		space(x)     = '#';
		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}

bool Graph::Dijkstra(coord start, coord end, CharMatrix &space, list<coord> &path, size_t &nodes_expanded)
{
	if (!vertices[start] || !vertices[end])
	{
		cerr << "Vertex " << start << " does not exist.";
		return false;
	}

	map<coord, double>              dist;
	map<coord, coord>               prev;
	multimap<double, coord, less<>> queue;
	for (auto                       &it:vertices)
		dist[it.first] = std::numeric_limits<double>::infinity();

	dist[start] = 0;
	queue.insert(make_pair(0, start));

	while (!queue.empty())
	{
		auto x       = queue.begin()->second;
		queue.erase(queue.begin());//extract element with least distance
		//If it is the end, reconstruct path and return

		if (x == end)
		{
			path = reconstruct_path(prev, x);
			space(end) = 'E'; //detail
			return true;
		}
		space(x)     = '#';
		//Expand node 'x'
		nodes_expanded++;
		cout << "\033[2J" << "Closing and expanding node " << x << endl;
		for (auto &it : vertices[x]->adjacent)
		{
			const auto &curdata = it.second->data; //take actual neighbour and get its coord
			double     d        = dist[x] + it.first; //d = distance to x + distance to it;
			bool       isbetter = d < dist[curdata];

			if (isbetter) //If we can to curdata with less distance than we already did once
				//update it, if curdata was unvisited, this always occurs
			{
				dist[curdata] = d; // insert this better result
				queue.insert(make_pair(d, curdata)); //update curdata in distances
				prev[curdata] = x; //for path

				space(curdata) = 'O'; //dec
			}
		}
		//Revalidate possibly doomed letters
		space(start) = 'S';
		space(end)   = 'E';
		cout << space << endl;
#ifndef NO_SLEEP
		std::this_thread::sleep_for(SLEEP_TIME);
#endif
	}
	return false;
}


