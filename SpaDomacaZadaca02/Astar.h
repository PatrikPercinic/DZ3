#pragma once
#include <cmath>
#include <utility>
#include <iostream>
#include <set>
#include <stack>
#include "Astar.h"
using namespace std;

#define ROW 50
#define COL 25
struct cell {
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

	// Creating a shortcut for int, int pair type
	typedef pair<int, int> Pair;

	// Creating a shortcut for pair<int, pair<int, int>> type
	typedef pair<double, pair<int, int> > pPair;
class Astar
{

private:
	bool isValid(int row, int col);
	bool isDestination(int row, int col, Pair dest);
	bool isUnBlocked(int grid[][COL], int row, int col);
	stack<Pair> tracePath(cell cellDetails[][COL], Pair dest);
	double calculateHValue(int, int, Pair);
public:
	stack<Pair> aStarSearch(int grid[][COL], Pair src, Pair dest);
	//void run();
};

