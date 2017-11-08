#pragma once 
#include "Vertex.h"
#include "Edge.h"
#include "Network.h"

#include <map>
#include <vector>
#include <iostream>
#include "PushRelabel.h"

using namespace std;

void updateFlow(const vector<Edge>& augPath , Network* Original);
Network* createGraph();
void printNetwork(Network* n);
Network * Residual(Network* G);
std ::vector <Edge> computeAugmentingPath(const Network * G);
void printPath(vector<Edge> path);
void FordFulkerson(Network * n);