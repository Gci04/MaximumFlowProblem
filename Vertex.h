#pragma once

#include "Edge.h"

#include <vector>
#include <iostream>


class Vertex {
private:

	std::vector<Edge> edgesOut;
	std::vector<Edge> edgesIn;

public:
	void addEdge(const Edge& edge);
	
};