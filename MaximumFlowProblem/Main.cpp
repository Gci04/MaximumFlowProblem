#include "Vertex.h"
#include "Edge.h"
#include "Network.h"

#include <iostream>
#include <vector>


using namespace std;

Network* createGraph();
void printNetwork(Network* n);
Network * Residual(Network* G);


int main(){
	Vertex v;
	Edge e;
	Network *test2 ; 
	Network *test = createGraph();
	printNetwork(test);
	test2 = Residual(test); 
	printNetwork(test2);
	delete test;
	delete test2;
	return 0;
}

Network* createGraph(){

	Vertex *s = new Vertex;
	Vertex *t = new Vertex;
	Vertex *v1 = new Vertex;
	Vertex *v2 = new Vertex;
	Vertex *v3 = new Vertex;
	Vertex *v4 = new Vertex;

	Network *result = new Network;
	result->AddVertex(s);
	result->AddVertex(v1);
	result->AddVertex(v2);
	result->AddVertex(v3);
	result->AddVertex(v4);
	result->AddVertex(t);

	result->SetSource(s);
	result->SetSink(t);

	result->AddEdge(Edge(4,16,s,v1));
	result->AddEdge(Edge(0,13,s,v2));
	result->AddEdge(Edge(4,14,v2,v4));
	result->AddEdge(Edge(4,12,v1,v3));
	result->AddEdge(Edge(0,4,v2,v1));
	result->AddEdge(Edge(4,9,v3,v2));
	result->AddEdge(Edge(0,20,v3,t));
	result->AddEdge(Edge(0,7,v4,v3));
	result->AddEdge(Edge(4,4,v4,t));

	return result;
}

void printNetwork(Network* n) {
	const vector<Vertex*>& vertices = n->getVertices();
	for (size_t i = 0; i < vertices.size(); i++) {
		std::cout << "\nvertex #" << i << ":\n";
		vertices[i]->print();
	}
	cout<<'\n';
}

Network * Residual(Network* G){
	Network* result = new Network();
	//Network* result(G); 
	//result = G;

	const vector<Vertex*>& vertices = G->getVertices();

	for(size_t i = 0; i < G->totalVertices(); i++){
		vector<Edge> edgesOut = vertices[i]->getEdgesOut();
		vertices[i]->clearEdges(); //removing the edges linked to each vertex
		result->AddVertex(vertices[i]); // add the vertex to result network

		for(size_t j = 0; j < edgesOut.size(); j++){

			if(edgesOut[j].getValue() == edgesOut[j].getCapacity()){
				result->AddEdge(Edge(0,edgesOut[j].getCapacity(), edgesOut[j].getEnd(), edgesOut[j].getStart()));
				continue;
			}
			else if(edgesOut[j].getValue() == 0){
				result->AddEdge(Edge(0,edgesOut[j].getCapacity() , edgesOut[j].getStart(), edgesOut[j].getEnd()));
				continue;
			}
			else //if (edgesOut[j].getValue() < edgesOut[j].getCapacity())
			{
				result->AddEdge(Edge(0,(edgesOut[j].getCapacity() - edgesOut[j].getValue()), edgesOut[j].getStart(), edgesOut[j].getEnd()));
				result->AddEdge(Edge(0,edgesOut[j].getValue(), edgesOut[j].getEnd(), edgesOut[j].getStart()));
				continue;
			}
			
		}
	}
	return result;
}
int minimumFlow(const vector<Edge*>& augPath){
	int result =augPath[0]->getValue() ;

	for(size_t i = 0; i < augPath.size(); i++){
		if(augPath[i]->getCapacity() < result)
			result = augPath[i]->getCapacity();
	}
	return result;
}