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