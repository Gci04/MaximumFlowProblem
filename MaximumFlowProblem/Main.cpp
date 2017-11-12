#include "Vertex.h"
#include "Edge.h"
#include "FordFulkersonBasics.h"
#include "PushRelabel.h"
#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
	//Vertex v;
	//Edge e;
	//Network *test2 ; 
	Network *test = createGraph();
	//FordFulkerson(test);
	Init_Preflow(test);
	printNetwork(test);
	test = Residual(test);
	//printNetwork(test);
	delete test;
	//delete test2;

	return 0;
}
