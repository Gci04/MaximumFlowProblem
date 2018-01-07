#pragma once
#include"Vertex.h"
#include "Network.h"
#include <queue> 

void Push(Vertex* u, Vertex* v , Edge * uv);
void Init_Preflow(Network *G);
void GenericPushRelabel(Network * G);
void PushRelabel(Network * G);
//bool TryPush(Vertex* u, std::queue<Vertex*> * q = (NULL));
bool TryPush(Vertex* u);
bool TryRelabel(Vertex * u);
void Relabel(Vertex * u);
bool overFlowingVertex(std::vector<Vertex*> vertices);
void UpdateOriginalNetwork(Network * Original , std::vector<Vertex *> res_vertices);
