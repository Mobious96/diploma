#include <iostream>
#include "graph.cpp"
#include <time.h>
#include <memory>
#include "lbfs.cpp"

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
	int vertices = 5;
	srand(time(NULL));
	int edges = vertices * 1.5; //having more than certain coefficent will dramatically decrease perfomance
	//I should try to connect this coefficent with max_degree to uniform distribution

	vector<Vertex> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex>()));
	}

	Graph G;
	clock_t t = clock();
	G.generateChordal(Vertices, edges);
	t = clock() - t;
	print(G);
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "time: " << time_taken << "s" << endl
		 << endl;

	cout << "Start with " << Vertices.end()->id << endl;
	auto n = LBFS(G, *(Vertices.end())); //NEED TO CALL ARBITARY LBFS TO CHECK IF IT'S CHORDAL
	cout << "LBFS:" << endl;
	for (auto i : n)
	{
		cout << i.second.id << ":" << i.first << std::endl;
	}
	auto n2 = LBFSplus(G, n);
	cout << "LBFSArbitary" << endl;
	for (auto i : n2)
	{
		cout << i.second.id << ":" << i.first << std::endl;
	}

	if (PEO(G, n2))
	{
		cout << "Chordal!" << endl;
	}
	else
	{
		cout << "Not chordal" << endl;
	}
}