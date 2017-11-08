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
 int Network :: totalVertices() const{
		return vertices.size();
	}
const std::vector<Vertex*> Network:: getVertices() const {
	return vertices;
}
/*void Network::InitializePreflow( Network *G)
{
	source->setHeight(vertices.size());
	std::vector<Edge> SourceOutEdges = source->getEdgesOut();
	for (size_t j = 0; j < source->sizeEdgesOut(); j++) {
		SourceOutEdges[j].setValue(SourceOutEdges[j].getCapacity());
		SourceOutEdges[j].getEnd()->setEcxess(SourceOutEdges[j].getCapacity());
	}

}*/
/*void Network::InitPreflow(Network * G)
{
	source->setHeight(vertices.size());
	std::vector<Edge> SourceOutEdges = source->getEdgesOut();
	for (size_t j = 0; j < source->sizeEdgesOut(); j++) {
		SourceOutEdges[j].setValue(SourceOutEdges[j].getCapacity());
		SourceOutEdges[j].getEnd()->setEcxess(SourceOutEdges[j].getCapacity());
	}

}*/
void Network::changeEdge(Edge newEdge) {
	Vertex* start = newEdge.getStart();
	Vertex* end = newEdge.getEnd();
	std::vector<Edge> edgesOut = start->getEdgesOut();
	for (size_t i = 0; i < edgesOut.size(); i++)
		if (edgesOut[i].getEnd() == end)
			start->setEdgeOut(i, newEdge);
	std::vector<Edge> edgesIn = end->getEdgesIn();
	for (size_t i = 0; i < edgesIn.size(); i++)
		if (edgesIn[i].getStart() == start)
			end->setEdgeIn(i, newEdge);
}