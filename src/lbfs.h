#pragma once
#include "graph.cpp"
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm> //max_element
#include <map>
#include <stack>

bool NeighbourhoodCondition(Graph& G, std::map<int, Vertex>& number);

bool PEO(Graph& G, std::map<int, Vertex>& number);

std::map<int, Vertex> LBFS(Graph& G, const Vertex& u);

std::map<int, Vertex> LBFSplus(Graph& G, std::map<int, Vertex>& _number);
