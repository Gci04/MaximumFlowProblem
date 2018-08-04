#pragma once

#include "Edge.h"

#include <vector>
#include <iostream>


class Vertex {
private:

	std::vector<Edge> edgesOut;
	std::vector<Edge> edgesIn;
	size_t index;
	int height = 0;
	int excess = 0;

public:
    Vertex()
    {}
    Vertex (size_t ind, int h, int ex): index(ind), height(h), excess(ex)
    {}
	void addEdge(const Edge& edge);
	std::vector<Edge>& getEdgesOut();
	const std::vector<Edge>& getEdgesOut() const;
	std::vector<Edge>& getEdgesIn();
	const std::vector<Edge> getEdgesIn() const;
	int sizeEdgesOut()const;
	void setIndex(size_t newIndex);
	size_t getIndex() const;
	void setEdgeIn(size_t idx, Edge edge);
	void setEdgeOut(size_t idx, Edge edge);

	//For height init and modification
	void setHeight(int h);
	int getHeight() const;

	//for ecxess init and modification
	void addEcxess(int ex);
	void setEcxess(int ex);
	int getExcess() const;

	// Temporary for debugging
	void print() const {
		std::cout << "Index: " << getIndex() << "\n";
		std::cout << "Height: " << getHeight() << "\n";
		std::cout << "Excess: " << getExcess() << "\n";
		std::cout << "Edges out: ";
		for (size_t i = 0; i < edgesOut.size(); i++)
			std::cout <<edgesOut[i].getValue() << "/" << edgesOut[i].getCapacity() << "    ";
		std::cout << "\nEdges in: ";
		for (size_t i = 0; i < edgesIn.size(); i++)
			std::cout <<edgesIn[i].getValue() << "/" << edgesIn[i].getCapacity() << "   ";
		std::cout << "\n\n";
	}
	
};
