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

std::vector<Edge>& Vertex::getEdgesOut() {
	return edgesOut;
}

const std::vector<Edge>& Vertex:: getEdgesOut() const{
	return edgesOut;
}

std::vector<Edge>& Vertex::getEdgesIn()
{
	return edgesIn;
}


const std::vector<Edge> Vertex:: getEdgesIn() const{
	return edgesIn;
}

int Vertex::sizeEdgesOut()const {
	return (int)edgesOut.size();
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

void Vertex::setHeight(int h)
{
	height = h;
}

int Vertex::getHeight() const
{
	return height;
}

void Vertex::addEcxess(int ex)
{
	excess += ex;
}

void Vertex::setEcxess(int ex)
{
	excess = ex;
}

int Vertex::getExcess() const
{
	return excess;
}
