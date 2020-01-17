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

	// unordered_map<int, unordered_map<int, double>> A;
	// unordered_map<int, unordered_map<int, double>> B;
	// B[1][1] = 11;
	// B[1][3] = 13;
	// B[2][4] = 24;
	// B[3] = {};
	// A[1] = B[1];
	// cout << A[1][3] << endl;
	// if (B.find(4) != B.end())
	// {
	// 	cout << "Found" << endl;
	// }
	// else
	// {
	// 	cout << "Not found" << endl;
	// }

	// for (auto i : B)
	// {
	// 	for (auto j : i.second)
	// 		cout << j.second << endl;
	// }
	// cout << "\n\n";

	//Graph<int> G(Vertices);
	//G.graph.begin()->first.data = 3;
	//G.addEdge(Vertices[1], Vertices[3]);
	//cout << "Random: " << std::next(G.graph.begin(), int(rand() % G.graph.size()))->first.id << endl;
	//auto it = G.graph.begin();
	//std::advance(it, int(rand() % G.graph.size()));
	//it->first.id = 3;
	//G.getRandomVertex().data = 10;
	Graph<int> G;
	G.generateChordal(Vertices, edges);
	for (auto v : G.graph)
	{
		cout << v.first.id << ": ";
		for (auto v2 : v.second)
		{
			cout << v2.first << " ";
		}
		cout << endl;
		//v.first.id = 3;
	}
	cout << endl;
	G.insert_query(Vertices[7], Vertices[6]);

	//cout << hashVertex(Vertices[2]) << endl;
}