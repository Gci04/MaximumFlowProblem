#pragma once
#include"Vertex.h"

#include <vector>


class Network {
private:
	std::vector <Vertex*> vertices; 
	Vertex* source;
	Vertex* sink;

public:
	/*Network(){}
	Network(const Network& other)
	{
		int N = other.vertices.size();
		vertices.resize(N);
		for(int i = 0; i < N; i++)
		{
			vertices[i] = new Vertex;
			this->AddVertex(vertices[i]);
		}
		
		//TODO we need copy constructor for VERTEX
		source = new Vertex();
		source = other.source;
		sink = new Vertex;
		sink = other.sink;
		for(int i = 0; i < N; i++)
		{
			vertices[i] = new Vertex();
			vertices[i] = *other.vertices[i];
		}

	}*/
	void AddEdge(const Edge &e);
	void AddVertex(Vertex* a);
	
	void setSink(Vertex *a) ;
	Vertex * getSink() const;

	void setSource(Vertex *a) ;
	Vertex * getSource() const;

	int totalVertices() const{
		return vertices.size();
	}

	const std::vector<Vertex*> getVertices() const ;
};