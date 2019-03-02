#include <iostream>
#include <sstream>
#include <fstream>
#include "maze.h"

void Menu()
{
	cout << "Usage: MazeSolve <alg> <filename>" << endl;
	cout << "alg = 1,...,6" << endl;
	cout << "1 ... Breadth First Search" << endl;
	cout << "2 ... Depth First Search" << endl;
	cout << "3 ... Random Search" << endl;
	cout << "4 ... Dijkstra's Algorithm" << endl;
	cout << "5 ... Greedy Algorithm" << endl;
	cout << "6 ... A*" << endl;
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		Menu();
		return 1;
	}
	int x;
	stringstream ss;
	ss << argv[1];
	ss >> x;
	if(!ss || x < 1 || x > 6)
	{
		cout << "Invalid Input" << endl;
		Menu();
		return 1;
	}

	fstream fs;
	fs.open(argv[2]);
	if(!fs)
	{
		cout << "File \"" << argv[2] << "\" could not be opened, maybe it doesn't exist?" << endl;
		return 2;
	}
	freopen(argv[2], "r",stdin);
	switch(x)
	{
		case 1:
		{
			Maze::solveMaze(BFS);
			break;
		}
		case 2:
		{
			Maze::solveMaze(DFS);
			break;
		}
		case 3:
		{
			Maze::solveMaze(Random);
			break;
		}
		case 4:
		{
			Maze::solveMaze(Dijkstra);
			break;
		}
		case 5:
		{
			Maze::solveMaze(Greedy);
			break;
		}
		case 6:
		{
			Maze::solveMaze(Astar);
			break;
		}
		default:
			break;
	}
	return 0;
}
