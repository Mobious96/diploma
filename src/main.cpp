#include <iostream>
#include "graph.cpp"
#include <time.h>
#include <memory>

using namespace std;

int main()
{
	int vertices = 10;
	srand(time(NULL));
	int edges = rand() % (vertices * (vertices - 1) / 2) + (vertices - 1);
	vector<Vertex<int>> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex<int>>()));
	}

	//cout << Vertices.front().id << endl;

	unordered_map<int, unordered_map<int, double>> B;
	B[1][1] = 11;
	B[1][3] = 13;
	B[2][4] = 24;
	B[3] = {};
	if (B.find(4) == B.end())
	{
		cout << "Not found" << endl;
	}
	for (auto i : B)
	{
		for (auto j : i.second)
			cout << j.second << endl;
	}
	cout << hashVertex(Vertices[2]) << endl;
}