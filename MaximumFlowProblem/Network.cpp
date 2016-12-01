#include "Network.h"

void Network:: AddEdge(const Edge &e){
	e.getEnd()->addEdge(e);
	/// vertices[e.getEnd()]->addEdge(e);
	e.getStart()->addEdge(e);

}
void Network:: AddVertex(Vertex* a){
	vertices.push_back(a);
	/// call setIndex for a vertex
}

void Network::setSink(Vertex *a){
	sink = a;
}
Vertex * Network::getSink() const{
	return sink;
}
void Network::setSource(Vertex *a){
	source = a;
}
Vertex * Network::getSource() const{
	return source;
}

const std::vector<Vertex*> Network:: getVertices() const {
	return vertices;
}

