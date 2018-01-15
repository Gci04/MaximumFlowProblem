#include "Vertex.h"
#include "Edge.h"
#include "FordFulkersonBasics.h"
#include "PushRelabel.h"
#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	//Vertex v;
	//Edge e;
	Network *test2;
	Network *test = createGraph();
	//FordFulkerson(test);
	//Init_Preflow(test);
	//printNetwork(test);
	Init_Preflow(test);
	//printNetwork(test);

	std::cout << "\n\n\\n\nAfter push-relabel:\n";
	GenericPushRelabel(test);
	//printNetwork(test);
	//test2 = Residual(test);

	delete test;

	return 0;
}
