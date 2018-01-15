#include "Vertex.h"
#include "Edge.h"
#include "FordFulkersonBasics.h"
#include "PushRelabel.h"
#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	
	Network *test2 = createGraph();
	FordFulkerson(test2);
	cout << "\n\n\n************ After Ford-Fulkerson *************\n";
	printNetwork(test2);

	cout << "\n\n\n************ After push-relabel ***************\n";
	Network *test = createGraph();
	GenericPushRelabel(test);

	delete test;
	delete test2;

	return 0;
}
