#include "FordFulkersonBasics.h"

Network* createGraph(){
	Vertex *s = new Vertex;
	Vertex *t = new Vertex;
	Vertex *v1 = new Vertex;
	Vertex *v2 = new Vertex;
	Vertex *v3 = new Vertex;
	Vertex *v4 = new Vertex;

	Network *result = new Network;
	s->setIndex(0);
	result->AddVertex(s);
	v1->setIndex(1);
	result->AddVertex(v1);
	v2->setIndex(2);
	result->AddVertex(v2);
	v3->setIndex(3);
	result->AddVertex(v3);
	v4->setIndex(4);
	result->AddVertex(v4);
	t->setIndex(5);
	result->AddVertex(t);
	

	result->setSource(s);
	result->setSink(t);

	result->AddEdge(Edge(0,15,s,v1)); //s to A

	result->AddEdge(Edge(0,10,s,v2)); // s to B
	
	result->AddEdge(Edge(0,9,v2,v4)); // B to D
	
	result->AddEdge(Edge(0,7,v1,v3)); // A to C

	result->AddEdge(Edge(0, 7, v1, v4)); // A to D
	
	result->AddEdge(Edge(0,4,v1,v2)); // A to B
	
	
	result->AddEdge(Edge(0,25,v3,t)); // C to t
	
	result->AddEdge(Edge(0,15,v4,v3)); // D to C
	
	result->AddEdge(Edge(0,5,v4,t)); // D to t
	
	return result;
}

void printNetwork(Network* n) {
	const vector<Vertex*>& vertices = n->getVertices();
	for (size_t i = 0; i < vertices.size(); i++) {
		vertices[i]->print();
	}
	cout<<'\n';
}
void printPath (vector<Edge> path){
	cout<<"Path found : "<<'\n';
	for(int i = 0; i < path.size() ; i++){
		cout << path[i].getStart()->getIndex() <<" -> " <<path[i].getEnd()->getIndex() << "  "<<path[i].getValue()<<"/"<<path[i].getCapacity()<<endl;
	}
	cout<<'\n';
}



Network * Residual(Network* G){
	
	Network* result = new Network();
	const vector<Vertex*>& vertices = G->getVertices();
	vector<Vertex*> newVertices ;
	newVertices.resize(vertices.size());
	for(size_t i = 0; i < vertices.size(); i++){
		newVertices[i] = new Vertex;
		newVertices[i]->setIndex(i);
		result->AddVertex(newVertices[i]);
	}

	result->setSink(newVertices[G->getSink()->getIndex()]);
	result->setSource(newVertices[G->getSource()->getIndex()]);

	for(size_t i = 0; i < vertices.size(); i++){
		vector<Edge> edgesOut = vertices[i]->getEdgesOut();
		for(size_t j = 0; j < edgesOut.size(); j++){
			// Vertices in the resudual network corresponding to start and end of the original edge
			Vertex* oldStart = newVertices[edgesOut[j].getStart()->getIndex()];    
			Vertex* oldEnd = newVertices[edgesOut[j].getEnd()->getIndex()];    
			if(edgesOut[j].getValue() == edgesOut[j].getCapacity())
				result->AddEdge(Edge(0,edgesOut[j].getCapacity(), oldEnd, oldStart));
			else if(edgesOut[j].getValue() == 0)
				result->AddEdge(Edge(0,edgesOut[j].getCapacity(), oldStart, oldEnd));
			else //if (edgesOut[j].getValue() < edgesOut[j].getCapacity())
			{
				result->AddEdge(Edge(0,(edgesOut[j].getCapacity() - edgesOut[j].getValue()), oldStart, oldEnd));
				result->AddEdge(Edge(0,edgesOut[j].getValue(), oldEnd, oldStart));
			}
		}
	}
	
	return result;
}

vector<Edge> constructPath(const Network * G, map<Vertex*, int>& distance) {
	vector<Edge> invertedPath;
	Vertex* currentVertex = G->getSink();
	while (currentVertex != G->getSource()) {
		const vector<Edge> edgesIn = currentVertex->getEdgesIn();
		int dist = distance[currentVertex];
		for (size_t i = 0; i < edgesIn.size(); i++)
			if (distance[edgesIn[i].getStart()] == dist - 1)
			{
				invertedPath.push_back(edgesIn[i]);
				currentVertex = edgesIn[i].getStart();
				break;
			}
	}
	vector<Edge> path;
	for (int i = invertedPath.size() - 1; i >= 0; i--)
		path.push_back(invertedPath[i]);
	return path;
}

vector <Edge> computeAugmentingPath(const Network * G){
	vector <Vertex *> next;
	map<Vertex*, int> distance;
	Vertex* source = G->getSource();
	next.push_back(source);
	distance[source] = 0;
	for (size_t i = 0; i < next.size(); i++) {
		Vertex* currentVertex = next[i];
		if (currentVertex == G->getSink())
			return constructPath(G, distance);
		const vector<Edge> edgesOut = currentVertex->getEdgesOut();
		for(size_t j =0; j < edgesOut.size(); j++){
			Vertex* endVertex = edgesOut[j].getEnd();
			if (distance.count(endVertex) == 0)
			{
				distance[endVertex] = distance[currentVertex] + 1;
				next.push_back(endVertex);
			}
		}
	}
	// If the loop is over and we did not construct a path, there is no path
	return vector<Edge>();
}


int minCapacity(const vector<Edge>& augPath){
	int result = augPath[0].getCapacity() ;
	for(size_t i = 0; i < augPath.size(); i++){
		if (augPath[i].getCapacity() < result)
			result = augPath[i].getCapacity();
	}
	return result;
}

void updateFlow(const vector<Edge>& augPath , Network* Original){
	int valueIncrement = minCapacity(augPath);
	const vector<Vertex*>& vertices = Original->getVertices();
	for(size_t i = 0; i < augPath.size(); i++){
		int startIdx = augPath[i].getStart()->getIndex();
		int endIdx = augPath[i].getEnd()->getIndex();
		// Check if edge in the path is same direction as in network
		std::vector<Edge> edgesOut = vertices[startIdx]->getEdgesOut();
		for (size_t j = 0; j < edgesOut.size(); j++)
			if (edgesOut[j].getEnd()->getIndex() == endIdx) {
				// found edge in the same direction as in the path
				Edge newEdge = edgesOut[j];
				newEdge.setValue(newEdge.getValue() + valueIncrement);
				Original->changeEdge(newEdge);
				break;
			}
		// Check if edge in the path in opposite direction as in network
		std::vector<Edge> edgesIn = vertices[startIdx]->getEdgesIn();
		for (size_t j = 0; j < edgesIn.size(); j++)
			if (edgesIn[j].getStart()->getIndex() == endIdx) {
				// found edge in the same direction as in the path
				Edge newEdge = edgesIn[j];
				newEdge.setValue(newEdge.getValue() - valueIncrement);
				Original->changeEdge(newEdge);
				break;
			}
	}
}

void FordFulkerson(Network * n)
{
	Network * residual;
	bool stop = false;
	while (stop == false) {
		std::cout << "New step\n\n\n";
		printNetwork(n);
		residual = Residual(n);
		//std::cout << "Residual network:\n";
		//printNetwork(test2);
		vector <Edge> path = computeAugmentingPath(residual);
		if (path.size() == 0) {
			stop = true;
			std::cout << "Stopped\n";
		}
		else {
			printPath(path);
			updateFlow(path, n);
			std::cout << "Updated network:\n";
			//printNetwork(n);
		}
	}
	delete residual;
}