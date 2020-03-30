#include<iostream>
 
#include<fstream>
#include<math.h>

using namespace std;


char grid[100][100];

struct node
{
	int x;
	int y;
	int heuristic=-1;
	int pathcost=0;
	bool visited=false;
	bool explored = false;
	int parent_x = -1;
	int parent_y = -1;
	char data;

};


node graph[100][100];
int start_x, start_y;
int goal_x, goal_y;
int row, col;
const int QUEUE_SIZE = 1000;


struct queue
{
	node* arr[QUEUE_SIZE];
	int current = -1;

	queue()
	{
		for (int i = 0; i < QUEUE_SIZE; i++)
		{
			arr[i] = NULL;
		}
	}
	bool isempty()
	{
		if (current == -1)
			return true;
		else return false;
	}
	void enqueue(node* n)
	{
		current++;
		if (current == QUEUE_SIZE)
		{
			cout << "Queue Overflow! Program Crashed";
			exit(1);
		}
		arr[current] = n;
	}

	

	node* dequeue(int mode)
	{

		node* temp = arr[0];
		int minIndex = 0;
		if (mode == 0)
		{
			minIndex = 0;
		}
		else
		{

			for (int i = 0; i < QUEUE_SIZE; i++)
			{
				if (arr[i] == NULL)
					break;
				if (mode == 2)
				{
					if (temp->pathcost > arr[i]->pathcost)
					{
						temp = arr[i];
						minIndex = i;
					}
				}
				else
				{
					if (temp->pathcost+temp->heuristic > arr[i]->pathcost+arr[i]->heuristic)
					{
						temp = arr[i];
						minIndex = i;
					}
				}
			}
		}

		for (int i = minIndex; i < QUEUE_SIZE-1; i++)
		{
			arr[i] = arr[i + 1];
		}
		current--;

		return temp;
	}

};
 int calculateHeuristic(int i, int j,int mode)
{
	 if (mode == 1)
	 {
		 return abs(goal_x - i) + abs(goal_y - j);
	 }
	 else
	 {
		 return sqrt(pow(goal_x - i, 2) + pow(goal_y - j, 2));
	 }
}


int main(int argc, char* argv[])
{
	
	//string algo = argv[1];
	//string heuristic = argv[2];
	ifstream fin("grid.txt");

	int algo = 3;

	int heu_mode = 2;// heuristic == "M" ? 1 : 2;

	//Reading Files
	fin >> row>>col;
	fin >> start_x >> start_y;
	fin >> goal_x >> goal_y;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin >> grid[i][j];
		}
	}
	//Calculating Heuristic of Nodes
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			graph[i][j].heuristic = calculateHeuristic(i + 1, j + 1,heu_mode);
			graph[i][j].data = grid[i][j];
			graph[i][j].x = i;
			graph[i][j].y = j;
		}
	}

	 //Main Loop

	bool goalfound = false;
	node* temp = &graph[start_x-1][start_y-1];
	node* resultnode = NULL;
	queue q;
	temp->visited = true;
	q.enqueue(temp);
	int counter = 0;;
	while (!goalfound && !q.isempty())
	{
		 node* current = q.dequeue(algo);
		 

		 //cout << current->pathcost+current->heuristic << endl;;

		 current->explored = true;

		 int x = current->x, y = current->y;
		 
		 //Uncomment to see the traversal of nodes

		 //cout<<x+1<<' '<<y+1<<endl;        
		 counter++;
		 // Checking Goal Node
		 if (current->x == goal_x-1 && current->y == goal_y-1)
		 {
			 cout << "Goal Found";
			 resultnode = current;
			 goalfound = true;
			 break;
		 }
		 // Adding Childs to Queue Or Looking for Moves

		 // Up Move
		 if (x - 1 >= 0)
		 {
			 if (graph[x - 1][y].data != 'X' && !graph[x - 1][y].visited)
			 {
				 graph[x - 1][y].visited = true;
				 graph[x - 1][y].parent_x = x;
				 graph[x - 1][y].parent_y = y;
				 if (graph[x - 1][y].data > current->data)
					 graph[x - 1][y].pathcost = current->pathcost + 1 + abs(current->data - graph[x - 1][y].data);
				 else
					 graph[x - 1][y].pathcost = current->pathcost + 1;

				 q.enqueue(&graph[x - 1][y]);
			 }
			
		 }
		//Down Move
		 if (x + 1 <= row)
		 {
			 if (graph[x + 1][y].data != 'X' && !graph[x + 1][y].visited)
			 {
				 graph[x + 1][y].visited = true;
				 graph[x + 1][y].parent_x = x;
				 graph[x + 1][y].parent_y = y;
				 if (graph[x + 1][y].data > current->data)
					 graph[x + 1][y].pathcost = current->pathcost + 1 + abs(current->data - graph[x + 1][y].data);
				 else
					 graph[x + 1][y].pathcost = current->pathcost + 1;
				 q.enqueue(&graph[x + 1][y]);

			 }

		 }
		 //Left Move
		 if (y - 1 >= 0)
		 {
			 if (graph[x][y - 1].data != 'X' && !graph[x][y - 1].visited)
			 {
				 graph[x][y - 1].visited = true;
				 graph[x][y - 1].parent_x = x;
				 graph[x][y - 1].parent_y = y;
				 if (graph[x ][y-1].data > current->data)
					 graph[x][y-1].pathcost = current->pathcost + 1 + abs(current->data - graph[x ][y-1].data);
				 else
					 graph[x][y-1].pathcost = current->pathcost + 1;
				 q.enqueue(&graph[x][y - 1]);

			 }

		 }
		 //Right Move
		 if (y + 1 < row)
		 {
			 if (graph[x][y + 1].data != 'X' && !graph[x][y + 1].visited)
			 {
				 graph[x][y + 1].visited = true;
				 graph[x][y + 1].parent_x = x;
				 graph[x][y + 1].parent_y = y;
				 if (graph[x][y+1].data > current->data)
					 graph[x][y + 1].pathcost = current->pathcost + 1 + abs(current->data - graph[x][y + 1].data);
				 else
					 graph[x][y + 1].pathcost = current->pathcost + 1;
				 q.enqueue(&graph[x][y + 1]);

			 }

		 }
	}
	cout << "\n";
	if (resultnode == NULL)
		cout << "null";
	else
	{
		cout << resultnode->x + 1 << ' ' << resultnode->y + 1;
		cout << "\nCost = " << resultnode->pathcost << endl;
		cout << "Counter:" << counter << endl;

		temp = resultnode;
		while (true)	//Backtracking from goal to start
		{
			temp = &graph[temp->parent_x][temp->parent_y];
			if (temp->x == start_x - 1 && temp->y == start_y - 1)break;
			grid[temp->x][temp->y] = '*';

		}

		grid[start_x - 1][start_y - 1] = 'S';
		grid[goal_x - 1][goal_y - 1] = 'G';



		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << grid[i][j] << ' ';
			}
			cout << endl;
		}
	}

	system("pause>0");

	


	
}
