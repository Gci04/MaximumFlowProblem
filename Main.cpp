#include "Vertex.h"
#include "Edge.h"

#include <iostream>
#include <vector>

using namespace std;

class Network {
private:
	vector<Vertex*> graph;
	Vertex* source;
	Vertex* sink;

public:

	void AddEdge(Edge &e){
		for (int i=0 ; i<graph.size();i++)
			if(e.getStart() == graph[i])
				graph[i]->addEdge(e);
	
			else if(e.getEnd() ==graph[i]){
				graph[i]->addEdge(e);
			}
	}
	void AddVertex(Vertex* a){
		graph.push_back(a);
	}
	Network* Residual(){
	}

};


int main(){
	Vertex v;
	Edge e;

	return 0;
}