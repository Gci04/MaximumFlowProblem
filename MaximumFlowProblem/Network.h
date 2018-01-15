#pragma once
#include"Vertex.h"

#include <vector>


class Network {
private:
	std::vector <Vertex*> vertices; 
	Vertex* source;
	Vertex* sink;

public:

    //bool getEdge(Vertex * start, Vertex * end)
	void changeEdge(Edge newEdge);
	void AddEdge(const Edge &e);
	void AddVertex(Vertex* a);
	
	void setSink(Vertex *a) ;
	Vertex * getSink() const;

	void setSource(Vertex *a) ;
	Vertex * getSource() const;

	int totalVertices() const;

	const std::vector<Vertex*> getVertices() const ;
};
