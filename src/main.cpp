#pragma once
#include <iostream>
#include "graph.cpp"
#include <time.h>
#include <memory>
#include "lbfs.h"

using namespace std;

void print(std::map<int, Vertex>& order)
{
	for (auto u : order)
	{
		cout << u.second.id << " ";
	}
	cout << endl;
}

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

void ChordalTest()
{
	//chordal if and only if the ordering of V produced by any LBFS is a Perfect Elimination Ordering
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
	//auto n2 = LBFSplus(G, n);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "LBFS time: " << time_taken << "s" << endl;

	t = clock();
	if (PEO(G, n))
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

void NotChordalTest()
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
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "LBFS time: " << time_taken << "s" << endl;

	t = clock();
	if (PEO(G, n))
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

void UIGtest()
{
	cout << "[///UIG Test///]" << endl;
	int vertices = 1000;
	srand(time(NULL));
	cout << "Vertices: " << vertices << endl;
	vector<Vertex> Vertices;

	for (int i = 0; i < vertices; i++)
	{
		Vertices.push_back(*(make_shared<Vertex>()));
	}

	Graph G;
	clock_t t = clock();
	//G.generateNotChordal(Vertices, vertices*1.5);
	G.generateUIG(Vertices);
	t = clock() - t;
	//print(G);
	//cout << "Graph size:" << G.graph.size() << endl;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "Generation time: " << time_taken << "s" << endl;

	t = clock();
	//cout << "Graph size:" << G.graph.size() << endl;
	auto n = LBFS(G, *(Vertices.begin())); //NEED TO CALL ARBITARY LBFS TO CHECK IF IT'S CHORDAL
	//cout << "Graph size:" << G.graph.size() << endl;
	auto n2 = LBFSplus(G, n);
	auto n3 = LBFSplus(G, n2);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "LBFS, LBFS+ time: " << time_taken << "s" << endl;
	//print(n);
	//print(n2);
	//print(n3);
	t = clock();
	if (NeighbourhoodCondition(G, n3))
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "Test time: " << time_taken << "s" << endl;
		cout << "UIG! That's correct!" << endl;
	}
	else
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "Test time: " << time_taken << "s" << endl;
		cout << "Not UIG! That isn't correct!" << endl;
	}
	t = clock();
	if (PEO(G, n))
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Chordal! That is correct!" << endl;
	}
	else
	{
		t = clock() - t;
		time_taken = ((double)t) / CLOCKS_PER_SEC;
		cout << "PEO time: " << time_taken << "s" << endl;
		cout << "Not chordal! That isn't correct!" << endl;
	}
}

int main()
{
	unordered_map<int, int> A;
	A[0] = 1;
	A[0] = 2;
	cout << "A size:" << A.size() << endl;
	UIGtest();
	// ChordalTest();
	// cout << endl;
	// NotChordalTest();

	// int vertices = 1000;
	// vector<Vertex> Vertices;
	// int edges = vertices * 1.5;
	// for (int i = 0; i < vertices; i++)
	// {
	// 	Vertices.push_back(*(make_shared<Vertex>()));
	// }

	// Graph G;
	// G.generateUIG(Vertices);
	// if (G.IsConnected())
	// {
	// 	cout << "Connected!" << endl;
	// }
	system("pause");
}