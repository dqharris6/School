#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph g;
	
	ifstream file;
	file.open("Rand200.txt");
	
	int numverts, numedges, start, goal;
	
	int inputv1, inputv2;
	float inputweight;
	
	file >> numverts >> numedges;
	
	for(int i =0; i < numverts; i++)
	{
		g.insertVertex(i);
	}
	
	for(int i =0; i < numedges; i++)
	{
		file >> inputv1 >> inputv2 >> inputweight;
		g.insertEdge(inputv1,inputv2,inputweight);
	}
	
	file >> start >> goal;
	
	vector<Vertex *> shortPath = g.shortestPath(start,goal);
	
	for(int i = 0; i < shortPath.size(); i++)
	{
		cout << shortPath[i]->data << endl; 
	}
	
	return 0;	
}
