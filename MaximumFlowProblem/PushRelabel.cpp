#include "PushRelabel.h"
#include<algorithm>

void Push(Vertex * u, Vertex * v , Edge * uv /*edge uv*/) //push from u to v
{
	if (u->getExcess() > 0 && u->getHeight() > v->getHeight()) {
		int push = std::min(u->getExcess(), uv->getCapacity());
		//int newCapacity = uv->getCapacity() + push;
		//uv->setCapacity(newCapacity)
		//vu->setCapacity(vu->getCapacity() - push);
		int u_newExess = u->getExcess() - push;
		int v_newExess = v->getExcess() + push;
		u->setEcxess(u_newExess);
		v->setEcxess(v_newExess);
	}
	else
		return;
}

void Relabel(Vertex * v)
{
	if (v->getExcess() > 0) {
		std::vector<Edge> temp = v->getEdgesOut();
		int increase = v->getHeight();
		for (size_t i = 0; i < v->sizeEdgesOut(); i++) {
			increase = std::min(temp[i].getEnd()->getHeight(), increase);
		}
		v->setHeight(increase + 1);
		return;
	}
	else
	{
		return;
	}
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

void PushRelabel(Network * G)
{
	std::queue<Vertex *> active;
	std::vector<Edge> source_out = G->getSource()->getEdgesOut(); //getEdgesOut() - returns constant value
	for (size_t i = 0; i < source_out.size(); i++) {
		active.push(source_out[i].getEnd()); 
	}
	while (!active.empty()) {
		Vertex * v;// v = active.pop()
		std::vector<Edge> v_out = v->getEdgesOut();
		for (size_t i = 0; i < v_out.size(); i++)
		{
			Push(v, v_out[i].getEnd(), &v_out[i]);
			if (i == v_out.size() && v->getExcess() != 0) {
				Relabel(v);
				i = 0;
			}
			else if (v->getExcess() == 0)
				break;
		}
	}
	//UpdateOriginalGraph(G);
	
}
