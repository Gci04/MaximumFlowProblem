#include "Vertex.h"
#include "Edge.h"
#include "Network.h"
#include "FordFulkersonBasics.h"

#include <iostream>
#include <vector>



using namespace std;



int main(){
	Vertex v;
	Edge e;
	Network *test2 ; 
	Network *test = createGraph();
	bool stop = false;
	while (stop == false) {
		std::cout << "New step\n\n\n";
		printNetwork(test);
		test2 = Residual(test); 
		printNetwork(test2);
		vector <Edge> path = computeAugmentingPath(test2);
		if (path.size() == 0) {
			stop = true;
			std::cout << "Stopped\n";
		}
		else{
			printPath(path);
			updateFlow(path, test);
			std::cout << "Updated network:\n";
			printNetwork(test);
		}
	}
	delete test;
	delete test2;

	return 0;
}
