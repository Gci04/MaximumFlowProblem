#include "Vertex.h"
#include "Edge.h"
#include "FordFulkersonBasics.h"
#include "PushRelabel.h"
#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	
	Network *test = createGraph(10);

	cout << "\n\n\n************ Input Flow Network ***************\n";
	printNetwork(test);

	cout << "\n\n\n************ After push-relabel ***************\n";
	GenericPushRelabel(test);

	FordFulkerson(test);
	cout << "\n\n\n************ After Ford-Fulkerson *************\n";
	printNetwork(test);

	delete test;
	return 0;
}
