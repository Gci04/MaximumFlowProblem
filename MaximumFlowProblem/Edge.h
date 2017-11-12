#pragma once 

class Vertex;

class Edge{
private:
	int value; // edge flow
	int capacity; 
	/// use indexes in Network::vertices instead of pointers
	Vertex * start;
	Vertex * end;

public:

	Edge(int val = 0, int cap = 0, Vertex * s = 0, Vertex * e = 0);

	void AddValue(int a); //modifying edge flow

	int getCapacity() const;
	void setCapacity(int cap);
	void upateCapacity(int capacity);

	int getValue() const;
	void setValue(int val);

	Vertex* getStart() const ;
	void setStart(Vertex * s) ;

	Vertex* getEnd() const ;
	void setEnd(Vertex * e) ;
};