#include <iostream>
#include "graph.cpp"
#include <time.h>
#include <memory>

using namespace std;

void print(Graph &G)
{
	for (auto &v : G.graph)
	{
		cout << v.first.id << ": ";
		for (auto &v2 : v.second)
		{
			cout << v2.first.id << " ";
		}
		cout << endl;
	}
}

int main()
{
	int vertices = 3000;
	srand(time(NULL));
	int edges = vertices * 3;

	vector<Vertex> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex>()));
	}

	Graph G;
	clock_t t = clock();
	G.generateChordal(Vertices, edges);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "time: " << time_taken << "s" << endl;
}