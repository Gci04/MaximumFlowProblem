#pragma once

#include "Edge.h"

#include <vector>
#include <iostream>


class Vertex {
private:

	std::vector<Edge> edgesOut;
	std::vector<Edge> edgesIn;
	/// size_t index;

public:
	/*Vertex(){}
	Vertex(const Vertex& other)
	{
	}*/
	void addEdge(const Edge& edge);
	const std::vector<Edge> getEdgesOut() const;
	const std::vector<Edge> getEdgesIn() const;

	// Temporary for debugging
	void print() const {
		std::cout << "Edges out: ";
		for (size_t i = 0; i < edgesOut.size(); i++)
			std::cout << edgesOut[i].getValue() << "/" << edgesOut[i].getCapacity() << "    ";
		std::cout << "\nEdges in: ";
		for (size_t i = 0; i < edgesIn.size(); i++)
			std::cout << edgesIn[i].getValue() << "/" << edgesIn[i].getCapacity() << "   ";

	}
	void clearEdges(){
		edgesOut.erase(edgesOut.begin(),edgesOut.end());
		edgesIn.erase(edgesIn.begin(),edgesIn.end());
	}
	int sizeEdgesOut()const {
		return edgesOut.size();
	}

	/// void setIndex(size_t newIndex);
	/// size_t getIndex() const;
};