#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Maze.h"
#define CMP(x, n) !strncmp(algstr, (x), (n))

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		cerr << "Usage: mazesolver <algorithm> <file>" << endl;
		return 256;
	}

	char *&algstr = argv[1];
	Algorithm alg;
	if (CMP("bfs", 3))
		alg = BFS;
	else if (CMP("dfs", 3))
		alg = DFS;
	else if(CMP("random", 3))
		alg = Random;
	else if (CMP("a*",2))
		alg = Astar;
	else if(CMP("dijkstra",8))
		alg = Dijkstra;
	else if(CMP("greedy", 6))
		alg = Greedy;
	fstream fs;
	fs.open(argv[2],fstream::in);
	if(!fs.good())
	{
		cerr << "Error opening file  \"" << argv[2] << "\", probably file doesn't exist?" << endl;
		return 256;
	}




	// + Y, N - navrhnout metody
	freopen(argv[2], "r", stdin);
	Maze m;
	m.ChangeSleepTime(x); //TADY
	m.solveMaze(alg);
	/*Graph<coord>  g;
	vector<coord> res;
	g.addVertex(make_pair(0, 0));
	g.addVertex(make_pair(1, 1));
	g.addVertex(make_pair(2, 2));
	g.addVertex(make_pair(3, 3));
	g.addEdge(make_pair(0, 0), make_pair(1, 1), 1);
	g.addEdge(make_pair(0, 0), make_pair(2, 2), 1);
	g.addEdge(make_pair(1, 1), make_pair(2, 2), 1);
	g.addEdge(make_pair(2, 2), make_pair(0, 0), 1);
	g.addEdge(make_pair(2, 2), make_pair(3, 3), 1);
	g.addEdge(make_pair(3, 3), make_pair(3, 3), 1);
	g.BFS(make_pair(2, 2), res);*/

}