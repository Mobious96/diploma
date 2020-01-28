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

bool ChordalTest()
{
	cout << "[///Chordal Test///]" << endl;
	int vertices = 1000;
	srand(time(NULL));
	int edges = vertices * 1.5; //having more than certain coefficent will dramatically decrease perfomance
	//I should try to connect this coefficent with max_degree to uniform distribution
	cout << "Vertices: " << vertices << "\tedges: " << edges << endl;
	vector<Vertex> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex>()));
	}

	Graph G;
	clock_t t = clock();
	G.generateChordal(Vertices, edges);
	t = clock() - t;
	//print(G);
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "Generation time: " << time_taken << "s" << endl;

	t = clock();
	auto n = LBFS(G, *(Vertices.end())); //NEED TO CALL ARBITARY LBFS TO CHECK IF IT'S CHORDAL
	auto n2 = LBFSplus(G, n);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "LBFS, LBFS+ time: " << time_taken << "s" << endl;

	t = clock();
	if (PEO(G, n2))
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Chordal! That's correct!" << endl;
	}
	else
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Not chordal! That isn't correct!" << endl;
	}
}

bool NotChordalTest()
{
	cout << "[///Not Chordal Test///]" << endl;
	int vertices = 1000;
	srand(time(NULL));
	int edges = vertices * 1.5; //having more than certain coefficent will dramatically decrease perfomance
	//I should try to connect this coefficent with max_degree to uniform distribution
	cout << "Vertices: " << vertices << "\tedges: " << edges << endl;
	vector<Vertex> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex>()));
	}

	Graph G;
	clock_t t = clock();
	G.generateNotChordal(Vertices, edges);
	t = clock() - t;
	//print(G);
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "Generation time: " << time_taken << "s" << endl;

	t = clock();
	auto n = LBFS(G, *(Vertices.end())); //NEED TO CALL ARBITARY LBFS TO CHECK IF IT'S CHORDAL
	auto n2 = LBFSplus(G, n);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "LBFS, LBFS+ time: " << time_taken << "s" << endl;

	t = clock();
	if (PEO(G, n2))
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Chordal! That isn't correct!" << endl;
	}
	else
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Not chordal! That's correct!" << endl;
	}
}

int main()
{
	ChordalTest();
	cout << endl;
	NotChordalTest();
}