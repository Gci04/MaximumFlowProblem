#include "PushRelabel.h"
#include<algorithm>

void Push(Vertex * u, Vertex * v , Edge * uv ) //push from u to v
{
	int value = std::min(u->getExcess(), uv->getCapacity());
	bool vuExist = false; 
	Edge * vu = NULL;
	std::vector<Edge> v_outEdges = v->getEdgesOut();
	for (size_t i = 0; i < v->getEdgesOut().size(); i++)//find edge form v to u
	{
		if (v_outEdges[i].getEnd() == u) {
			vu = &v_outEdges[i];
			vuExist = true;
			break;
		}
	}
	int newCapacity = uv->getCapacity() + value;
	/*if(uv->getCapacity() == value)
	{ delete uv from graph}*/
	uv->setCapacity(newCapacity);
	if (vuExist) {
		vu->upateCapacity(-value);
	}
	else {
		v->addEdge(Edge(0, value, v, u)); //create new edge form v to u 
	}
	int u_newExcess = u->getExcess() - value;
	int v_newExcess = v->getExcess() + value;
	u->setEcxess(u_newExcess);
	v->setEcxess(v_newExcess);
}

void Relabel(Vertex * u)
{
	//if (v->getExcess() > 0) { //no need to check the height precondition here since its will ve already checked in TryPush()
		std::vector<Edge> u_outEdges = u->getEdgesOut();
		int increase = u_outEdges[0].getEnd()->getHeight();
		for (size_t i = 1; i < u->sizeEdgesOut(); i++) {
			int v_height = u_outEdges[i].getEnd()->getHeight();
			increase = std::min(v_height,increase);

		}
		u->setHeight(increase + 1);
}

void Init_Preflow(Network * G)
{
	int sum_capacities = 0;
	const Vertex *Src = G->getSource();
	std::vector<Edge> Source_Out = Src->getEdgesOut();
	G->getSource()->setHeight(G->totalVertices());
	for (size_t i = 0; i < Src->getEdgesOut().size(); i++) {
		sum_capacities += Source_Out[i].getCapacity();
		Edge newEdge = Source_Out[i];
		newEdge.setValue(newEdge.getValue() + Source_Out[i].getCapacity());
		G->changeEdge(newEdge);
		//Source_Out[i].setValue(Source_Out[i].getCapacity());
		Source_Out[i].getEnd()->setEcxess(Source_Out[i].getCapacity());
		
	}
	//G->getSource()->setEcxess(sum_capacities);

}
void UpdateOriginalGraph(Network * G)
{

}
void GenericPushRelabel(Network * G)
{
	Init_Preflow(G);
	std::vector<Vertex*> vertices = G->getVertices();
	bool isOver = false;
	while (!isOver)
	{
		isOver = true;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i] == G->getSource() || vertices[i] == G->getSink())
				continue;
			else
			{
				isOver = isOver && !TryPush(vertices[i]);
				isOver = isOver && !TryRelabel(vertices[i]);
			}
			
		}
	}

}

void PushRelabel(Network * G) 
{
	std::queue<Vertex *> active;
	std::vector<Edge> source_out = G->getSource()->getEdgesOut(); //getEdgesOut() - returns constant value
	for (size_t i = 0; i < source_out.size(); i++) {
		active.push(source_out[i].getEnd()); 
	}
	while (!active.empty()) {
		Vertex * v;
		// v = active.pop() or v = active.front();
		//std::vector<Edge> v_out = v->getEdgesOut();
		if (!TryPush) {
			Relabel(v);
		}
		else {
			//push(v);
			//if((v->getExcess() == 0){ active.pop() }
		}
		/*
		for (size_t i = 0; i < v_out.size(); i++)
		{
			
			Push(v, v_out[i].getEnd(), &v_out[i]);
			if (i == v_out.size() && v->getExcess() != 0) {
				Relabel(v);
				i = 0;
			}
			else if (v->getExcess() == 0)
				break;
				
		}*/
	}
	//UpdateOriginalGraph(G);
	
}

bool TryPush(Vertex * u)
{
	bool isOVerflowing = (u->getExcess() > 0);
	if(isOVerflowing){
		std::vector<Edge> u_out = u->getEdgesOut();
		// here go through all vertices v instead
		for (size_t i = 0; i < u_out.size(); i++)
		{
			Vertex* v = u_out[i].getEnd();
			bool isHeightMatching = (u->getHeight() == v->getHeight() + 1);

			/*if (isOVerflowing == false) {
			return true;
			}*/
			//add condition for cf(u, v) > 0
			if (isOVerflowing && isHeightMatching && u_out[i].getCapacity() > 0) {
				Push(u, v, &u_out[i]);
			}
			else if (i == u_out.size() && isOVerflowing) {
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool TryRelabel(Vertex * u)
{
	bool isOverflowing = (u->getExcess() > 0);
	if (isOverflowing)
	{
		bool lessHeight = false;
		std::vector<Edge> u_outEdges = u->getEdgesOut();
		for (size_t i = 0; i < u->getEdgesOut().size(); i++)
		{
			Vertex* temp = u_outEdges[i].getEnd();
			if (u->getHeight() < temp->getHeight()) {
				lessHeight = true;
			}
		}
		if (lessHeight) {
			Relabel(u);
			
		}
		return true;
	}
	else {
		return false;
	}
}

