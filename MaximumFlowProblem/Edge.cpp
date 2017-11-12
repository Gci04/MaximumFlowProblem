#include "Edge.h"
#include "Vertex.h"

Edge::Edge(int val, int cap, Vertex * s, Vertex * e): value(val), capacity(cap), start(s), end(e)
{}

void Edge::AddValue(int a){
	value +=a; 
}

int Edge::getCapacity() const{
	return capacity;
}

void Edge::setCapacity(int cap){ 
	capacity = cap;
}

void Edge::upateCapacity(int capacity)
{
	this->capacity += capacity;
}

int Edge::getValue() const{
	return value;
}

void Edge::setValue(int val){
	value = val;
}

Vertex* Edge::getStart() const {
	return start;
}

void Edge::setStart(Vertex * s) {
	start = s;
}

Vertex* Edge::getEnd() const {
	return end;
}

void Edge::setEnd(Vertex * e) {
	end = e;
}
