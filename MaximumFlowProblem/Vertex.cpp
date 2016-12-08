#include "Vertex.h"

void Vertex::addEdge(const Edge& edge) {
	if (this == edge.getStart())
		edgesOut.push_back(edge);
	else if (this == edge.getEnd())
		edgesIn.push_back(edge);
	else 
		std::cout<<" Error!!! Edge already exists!!"<<std::endl;
	// else report an error
}

const std::vector<Edge> Vertex:: getEdgesOut() const{
	return edgesOut;
}

const std::vector<Edge> Vertex:: getEdgesIn() const{
	return edgesIn;
}

int Vertex::sizeEdgesOut()const {
	return edgesOut.size();
}

void Vertex::setIndex(size_t newIndex){
	index = newIndex;
}

size_t Vertex::getIndex() const {
	return index;
}

void Vertex::setEdgeIn(size_t idx, Edge edge) {
	edgesIn[idx] = edge;
}

void Vertex::setEdgeOut(size_t idx, Edge edge) {
	edgesOut[idx] = edge;
}