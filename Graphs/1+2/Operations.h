#pragma once
#include "MyGraph.h"

//Input for operations
int InputEdgeCount(const MyGraph& graph);
int InputShimbelMode();
int InputNumberOfVert(const MyGraph& graph);
int InputAlgorithmMode();

void ShimbellMethod(const MyGraph& graph);
void ReachabilityOperation(const MyGraph& graph);
void DijkstraAlgorithm(const MyGraph& graph);
void BellmanFordAlgorithm(const MyGraph& graph);
void FloydWarshallAlgorithm(const MyGraph& graph);
void MinCostFlow(const MyGraph& graph);
