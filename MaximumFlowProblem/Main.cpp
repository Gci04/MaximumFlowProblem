#include "Vertex.h"
#include "Edge.h"
#include "FordFulkersonBasics.h"
#include "PushRelabel.h"
#include "Network.h"
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
	
    const int nodes = (argc > 1 ? atoi(argv[1]) : 300);
	Network *test = createGraph(nodes, 200 , 250);
    
	cout << "\n\n\n************ Input Flow Network ***************\n";
	//printNetwork(test);
    
    double t1 = omp_get_wtime();
	cout << "\n\n\n************ After push-relabel ***************\n";
	GenericPushRelabel(test);
    double t2 = omp_get_wtime();

    cout <<"Push-relabel Time : "<<t2-t1<<endl;
    
    double t3 = omp_get_wtime();
	FordFulkerson(test);
    double t4 = omp_get_wtime();
	cout << "\n\n\n************ After Ford-Fulkerson *************\n";
	//printNetwork(test);
    cout <<"Ford-Fulkerson Time : "<<t4-t3<<endl;

	delete test;
	return 0;
}