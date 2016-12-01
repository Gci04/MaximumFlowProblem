#include "Vertex.h"
#include "Edge.h"
#include "Network.h"

#include <iostream>
#include <vector>
#include <map>


using namespace std;

Network* createGraph();
void printNetwork(Network* n);
Network * Residual(Network* G);
vector <Edge> computeAugmentingPath(const Network * G);
void printPath(vector<Edge> path);

int main(){
	Vertex v;
	Edge e;
	Network *test2 ; 
	Network *test = createGraph();
	printNetwork(test);
	test2 = Residual(test); 
	printNetwork(test2);
	vector <Edge> path = computeAugmentingPath(test2);
	printPath(path);
	delete test;
	delete test2;

	return 0;
}

Network* createGraph(){
	// Examle: page 726
	// original network - first row, right
	// residual - second row, left
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

	result->setSource(s);
	result->setSink(t);

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
void printPath (vector<Edge> path){
	for(int i = 0; i < path.size() ; i++){
		cout << path[i].getStart() <<"  " <<path[i].getEnd() << "  "<<path[i].getValue()<<" / "<<path[i].getCapacity()<<endl;
	}
}

Network * Residual(Network* G){
	Network* result = new Network();

	const vector<Vertex*>& vertices = G->getVertices();

	map<Vertex*,Vertex*> vertexMap; 
	for(size_t i = 0; i < vertices.size(); i++){
		Vertex *temp = new Vertex();
		result->AddVertex(temp);
		vertexMap.insert(std::pair<Vertex*, Vertex*>(vertices[i], temp));
		//vertexMap[vertices[i]] = temp;
	}

	result->setSink(vertexMap[G->getSink()]);
	result->setSource(vertexMap[G->getSource()]);

	for(size_t i = 0; i < vertices.size(); i++){
		vector<Edge> edgesOut = vertices[i]->getEdgesOut();
		for(size_t j = 0; j < edgesOut.size(); j++){
			// Vertices in the resudual network corresponding to start and end of the original edge
			Vertex* oldStart = vertexMap.at(edgesOut[j].getStart());
			Vertex* oldEnd = vertexMap.at(edgesOut[j].getEnd());
			if(edgesOut[j].getValue() == edgesOut[j].getCapacity())
				result->AddEdge(Edge(0,edgesOut[j].getCapacity(), oldEnd, oldStart));
			else if(edgesOut[j].getValue() == 0)
				result->AddEdge(Edge(0,edgesOut[j].getCapacity(), oldStart, oldEnd));
			else //if (edgesOut[j].getValue() < edgesOut[j].getCapacity())
			{
				result->AddEdge(Edge(0,(edgesOut[j].getCapacity() - edgesOut[j].getValue()), oldStart, oldEnd));
				result->AddEdge(Edge(0,edgesOut[j].getValue(), oldEnd, oldStart));
			}
		}
	}
	return result;
}

vector<Edge> constructPath(const Network * G, map<Vertex*, int>& distance) {
	vector<Edge> invertedPath;
	Vertex* currentVertex = G->getSink();
	while (currentVertex != G->getSource()) {
		const vector<Edge> edgesIn = currentVertex->getEdgesIn();
		int dist = distance[currentVertex];
		for (size_t i = 0; i < edgesIn.size(); i++)
			if (distance[edgesIn[i].getStart()] == dist - 1)
			{
				invertedPath.push_back(edgesIn[i]);
				currentVertex = edgesIn[i].getStart();
				break;
			}
	}
	vector<Edge> path;
	for (int i = invertedPath.size() - 1; i >= 0; i--)
		path.push_back(invertedPath[i]);
	return path;
}

vector <Edge> computeAugmentingPath(const Network * G){
	vector <Vertex *> next;
	map<Vertex*, int> distance;
	Vertex* source = G->getSource();
	next.push_back(source);
	distance[source] = 0;
	for (size_t i = 0; i < next.size(); i++) {
		Vertex* currentVertex = next[i];
		if (currentVertex == G->getSink())
			return constructPath(G, distance);
		const vector<Edge> edgesOut = currentVertex->getEdgesOut();
		for(size_t j =0; j < edgesOut.size(); j++){
			Vertex* endVertex = edgesOut[j].getEnd();
			if (distance.count(endVertex) == 0)
			{
				distance[endVertex] = distance[currentVertex] + 1;
				next.push_back(endVertex);
			}
		}
	}
	// If the loop is over and we did not construct a path, there is no path
	return vector<Edge>();
}
int minimumFlow(const vector<Edge*>& augPath){
	int result =augPath[0]->getValue() ;

	for(size_t i = 0; i < augPath.size(); i++){
		if(augPath[i]->getCapacity() < result)
			result = augPath[i]->getCapacity();
	}
	return result;
}