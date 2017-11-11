#pragma once
#include"Vertex.h"
#include "Network.h"
#include <queue> 

void Push(Vertex* u, Vertex* v , Edge * uv);
void Relabel(Vertex* v);
void Init_Preflow(Network *G);
void UpdateOriginalGraph(Network * G);
void PushRelabel(Network * G);
bool TryPush(Vertex* u);
bool TryRelabel(Vertex * u);