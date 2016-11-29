#include "Network.h"

void Network:: AddEdge(const Edge &e){
	e.getEnd()->addEdge(e);
	e.getStart()->addEdge(e);

}
void Network:: AddVertex(Vertex* a){
	vertices.push_back(a);
}

void Network::SetSink(Vertex *a){
	sink = a;
}
Vertex * Network::getSink(){
	return sink;
}
void Network::SetSource(Vertex *a){
	source = a;
}
Vertex * Network::getSource(){
	return source;
}

const std::vector<Vertex*> Network:: getVertices() const {
	return vertices;
}

