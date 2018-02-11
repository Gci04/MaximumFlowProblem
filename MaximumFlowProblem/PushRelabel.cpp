#include "PushRelabel.h"
#include "FordFulkersonBasics.h"
#include<algorithm>
#include<iostream>



void Init_Preflow(Network * G)
{
	const Vertex *Src = G->getSource();
	std::vector<Edge> Source_Out = Src->getEdgesOut();
	G->getSource()->setHeight(G->totalVertices());
	for (size_t i = 0; i < Src->getEdgesOut().size(); i++) {
		Edge newEdge = Source_Out[i]; 
		//newEdge.setValue(newEdge.getValue() + Source_Out[i].getCapacity());
		newEdge.setValue(Source_Out[i].getCapacity());
		G->changeEdge(newEdge);
		//Source_Out[i].setValue(Source_Out[i].getCapacity());
		//below line commented for working with residual net in the push-relabel 
		G->AddEdge(Edge(0, Source_Out[i].getCapacity(), Source_Out[i].getEnd(), Source_Out[i].getStart())); //set reverse edge from source
		Source_Out[i].getEnd()->setEcxess(Source_Out[i].getCapacity());
	}
}

void GenericPushRelabel(Network * G)
{
    Network * res;
    res = Residual(G);
	Init_Preflow(res);
	std::vector<Vertex*> vertices = res->getVertices();
	while (overFlowingVertex(vertices))
	{
		//std::cout << j++ << std::endl;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			if (vertices[i] == res->getSource() || vertices[i] == res->getSink())
				continue;
			if(TryPush(vertices[i]))
			{
				Relabel(vertices[i]);
				i--;
			}
		}
	}
    printNetwork(res);
}

void PushRelabel(Network * G)
{/*
	std::queue<Vertex *> active;
	std::vector<Edge> source_out = G->getSource()->getEdgesOut(); //getEdgesOut() - returns constant value
	for (size_t i = 0; i < source_out.size(); i++) {
		active.push(source_out[i].getEnd()); 
	}
	while (!active.empty()) {
		Vertex * v;
        //v = active.pop() or
         v = active.front();
		//std::vector<Edge> v_out = v->getEdgesOut();
        if (TryPush(v)) {
			Relabel(v);
		}
		else {
            //push(v);
			if((v->getExcess() == 0))
                active.pop();
		}
	}*/
}
//bool TryPush(Vertex * u, std::queue<Vertex *> * q )
bool TryPush(Vertex * u/*, std::vector<int> v = std::vector<int>()*/)
{
	bool isOverflowing = (u->getExcess() > 0);
	if (!isOverflowing)
		return false;
	// from now on u is overflowing
	bool result = true;
	std::vector<Edge>& u_out = u->getEdgesOut();
	for (size_t i = 0; i < u_out.size(); i++)
	{
		Vertex* v = u_out[i].getEnd();
		bool isHeightMatching = (u->getHeight() == v->getHeight() + 1);
		bool isEdgeNotSaturated = (u_out[i].getValue() < u_out[i].getCapacity());
		if (isHeightMatching && isEdgeNotSaturated)
		{
			Push(u, v, &u_out[i]);
            
            /*if(!q->empty())
                q->push(v);*/
			//maybe check if its still overflowing , if no return true
			if (u->getExcess() == 0) {
				result = false;
				break;
			}	
		}
	}
    return result;
}

void Push(Vertex * u, Vertex * v, Edge * uv) //push from u to v
{
	int delta = std::min(u->getExcess(), uv->getCapacity() - uv->getValue());
	u->setEcxess(u->getExcess() - delta);
	v->setEcxess(v->getExcess() + delta);

	// Modify uv edge . Only modifies u.out edges
	uv->AddValue(delta); 
	//for v.in edges update
	std::vector<Edge>& v_InEdges = v->getEdgesIn();
	for (size_t j = 0; j < v_InEdges.size(); j++)
	{
		if (v_InEdges[j].getStart() == u)
		{
			v_InEdges[j].AddValue(delta);
			break;
		}
	} 
	//for back edge - vu modification
	bool Exist = false;
	std::vector<Edge>& v_OutEdges = v->getEdgesOut();
	for (size_t i = 0; i < v_OutEdges.size(); i++)
	{
		if (v_OutEdges[i].getEnd() == u) {
			Exist = true;
			v_OutEdges[i].AddValue(-delta);
			std::vector<Edge>& u_InEdges = u->getEdgesIn();
			for (size_t j = 0; j < u_InEdges.size(); j++)
			{
				if (u_InEdges[j].getStart() == v)
				{
					u_InEdges[j].AddValue(-delta);
					break;
				}
			}
			break;
		}	
	}
	if (Exist == false) {
		int temp = uv->getCapacity() - delta;
		v->addEdge(Edge(temp, uv->getCapacity(), v, u));
		u->addEdge(Edge(temp, uv->getCapacity(), v, u));
	}
}

bool TryRelabel(Vertex * u)
{
	bool isOverflowing = (u->getExcess() > 0);
	if (!isOverflowing)
		return false;
	// u is overflowing
	std::vector<Edge>& u_out = u->getEdgesOut();
	int minHeight = u_out[1].getEnd()->getHeight(); // will need to fix
	for (size_t i = 0; i < u_out.size(); i++)
	{
		Vertex* v = u_out[i].getEnd();
		//bool isEdgeNotSaturated = (u_out[i].getCapacity() > 0);
		bool isEdgeNotSaturated = (u_out[i].getValue() < u_out[i].getCapacity());
		if (isEdgeNotSaturated && v->getHeight() < minHeight) {
			minHeight = v->getHeight();
		}
	}
	/*if (isEdgeNotSaturated && ((v->getHeight() < minHeight) || (minHeight < 0)))
		minHeight = v->getHeight();*/
	if (u->getHeight() <= minHeight) {
		u->setHeight(minHeight + 1);
		return true;
	}
	else
		return false;
}

void Relabel(Vertex * u)
{
	bool isOverflowing = (u->getExcess() > 0);
	if (!isOverflowing)
		return;
	// u is overflowing
	std::vector<Edge>& u_out = u->getEdgesOut();
	int minHeight = 100000; // will need to fix
	for (size_t i = 0; i < u_out.size(); i++)
	{
		Vertex* v = u_out[i].getEnd();
		bool isEdgeNotSaturated = (u_out[i].getValue() < u_out[i].getCapacity());
		if (isEdgeNotSaturated) {
			minHeight = std::min(minHeight, v->getHeight());
		}
	}
	if (u->getHeight() <= minHeight) {
		u->setHeight(minHeight + 1);
	}
}
bool overFlowingVertex(std::vector<Vertex*> vertices)
{
	for (size_t  i = 1; i < vertices.size() - 1 ; i++)
	{
		if (vertices[i]->getExcess() > 0 )
			return true;
	}
	return false;
}
void UpdateOriginalNetwork(Network * Original , std::vector<Vertex *> res_vertices){
    std::vector<Vertex*> Original_vertices = Original->getVertices();
    for (int i = 0; i < Original_vertices.size() ; i++) {
         std::vector<Edge>& current_out = Original_vertices[i]->getEdgesOut();
        for (int j = 0; j < current_out.size(); j++) {
            
        }
        
    }
}
