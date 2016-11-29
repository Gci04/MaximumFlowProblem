#pragma once 

class Vertex;

class Edge{
private:
	int value; // edge flow
	int capacity; 
	Vertex * start;
	Vertex * end;

public:
	/*Edge(){}
	Edge(const Edge& other)
	{
		value = other.value;
		capacity = other.capacity;
		start = new Vertex();
		start = other.start;
		end = new Vertex(*other.end);
	}*/
	Edge(int val = 0, int cap = 0, Vertex * s = 0, Vertex * e = 0);

	void AddValue(int a); //modifying edge flow

	int getCapacity() const;
	void setCapacity(int cap);

	int getValue() const;
	void setValue(int val);

	Vertex* getStart() const ;
	void setStart(Vertex * s) ;

	Vertex* getEnd() const ;
	void setEnd(Vertex * e) ;
};