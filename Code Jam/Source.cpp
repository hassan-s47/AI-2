#include<iostream>
#include<vector>
#include<queue>

char grid[10000][10000];

struct node
{
	int x;
	int y;
	int heuristic;
	int pathcost;
	vector<node*> pred;

};