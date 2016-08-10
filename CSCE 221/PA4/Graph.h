#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "LocatorHeap.h"
using namespace std;

class Edge;

class Vertex
{
public:
	int data;
	bool marked = false;
	vector<Edge *> edges;
	float d;
	Vertex *parent = nullptr;
	Heap<Vertex>::Locator locator;

	Vertex ( int newData ) : data ( newData ) ,d(numeric_limits<float>::infinity()) { }

	bool operator < ( const Vertex &v ) const 
	{ 
		return d < v.d;
	}
};

class Edge
{
public:
	Vertex *v1, *v2;
	float weight;

	Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};

// you should implement the adjacency list data structure
class Graph
{
protected:
	vector<Vertex *> verts;
	// vector<Edge *> edges;

public:
	Graph ( void ) { }

	~Graph ( void )
	{
		for(int i = 0; i < verts.size(); i++)
		{
			delete verts[i];
		}
	}

	void insertVertex ( int data )
	{
		verts.push_back(new Vertex(data));
	}

	void insertEdge ( int v, int w, float weight )
	{
		verts[v]->edges.push_back(new Edge(verts[v], verts[w], weight));
		verts[w]->edges.push_back(new Edge(verts[w], verts[v], weight)); 
	}

	vector<Vertex *> shortestPath ( int start, int goal )
	{
		Heap<Vertex> vertexheap;
		vector<Vertex *> vertPath;
		verts[start]->d=0;
		
		for(int j = 0; j < verts.size(); j++)
		{
			verts[j]->locator=vertexheap.insertElement(verts[j]);
		}		
		
		while(!vertexheap.isEmpty())
		{
			Vertex *u = vertexheap.removeMin();
			u->marked = true;
			
			for(int k = 0; k < u->edges.size(); k++)
			{
				Vertex *v = u->edges[k]->v2;
				if(u->edges[k]->weight+u->d<v->d && v->marked==false)
				{
					v->d = u->edges[k] -> weight+u->d;
					v->parent = u;
					vertexheap.update(v->locator);
				}
			}
		}
		
		Vertex *child = verts[goal];
		
		for(;child->parent!=nullptr;child=child->parent)
		{
			vertPath.insert(vertPath.begin(),child);
		}
		
		vertPath.insert(vertPath.begin(),child);
		
		return vertPath;
	}	
};

#endif
