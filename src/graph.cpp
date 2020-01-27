#pragma once
//#include "graph.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <time.h>
#include <unordered_set>

static int vertices_count = 0;

struct VertexData
{
    double value;
};
struct EdgeData
{
    double weight;
};

class Vertex
{
public:
    int id;
    mutable VertexData data;
    Vertex()
    {
        id = vertices_count++;
    }

    bool operator==(const Vertex &v) const
    {
        return (id == v.id);
    }
};

//For defying custom key hash we need operator== and hash<Vertex>
namespace std
{
template <>
struct hash<Vertex>
{
    std::size_t operator()(const Vertex &vertex) const
    {
        return hash<int>()(vertex.id);
    }
};
} // namespace std

class Graph
{
public:
    std::unordered_map<Vertex, std::unordered_map<Vertex, EdgeData>> graph;
    std::vector<Vertex> vertices;

public:
    void deleteVertex(Vertex &);
    std::vector<Vertex> getNeighborhood(Vertex &);

    void addVertex(const Vertex &vertex)
    {
        graph[vertex]; // O(1);
    }

    void addEdge(const Vertex &vertex, const Vertex &new_vertex)
    {
        graph[vertex][new_vertex] = {}; // O(1)
        graph[new_vertex][vertex] = {}; // O(1)
    }

    Graph()
    {
        graph = {};
    }

    Graph(std::vector<Vertex> &Vertices)
    {
        graph = {};
        vertices = Vertices;
        for (auto &v : Vertices)
        {
            addVertex(v);
        }
    }

    const Vertex &getRandomVertex()
    {
        srand(time(NULL));
        return std::next(graph.begin(), int(rand() % graph.size()))->first;
    }

    //returns true if u and v are adjacent
    bool isAdjacent(const Vertex &u, const Vertex &v) //average O(1), worst O(n); (hash)
    {
        if (isValid(u))
        {
            if (graph[u].find(v) != graph[u].end())
            {
                return true;
            }
            return false;
        }
    }

    //returns true if graph have the v vertex
    bool isValid(const Vertex &v)
    {
        if (graph.find(v) != graph.end())
        {
            return true;
        }
        return false;
    }

    bool insert_query(const Vertex &v, const Vertex &u)
    {
        Graph I;
        for (auto &n : graph[u]) //for all neighborhoods of u O(m)
        {
            if (graph[v].find(n.first) != graph[v].end())
            {
                I.addVertex(n.first);
            }
        }
        if (I.graph.size() == 0)
        {
            return false; //Graph is not chordal
        }
        else
        {
            //New implementation: instead of computing Aux explicitly, I'll need just mark those vertices for BFS; Aux = Adj(x) - Iu,v; x from Iu,v
            //std::vector<Vertex> Aux; //slow search
            std::unordered_set<Vertex> Aux; //is a hash table, O(1) for search, insert
            for (auto &n : graph[I.graph.begin()->first])
            {
                if (!I.isValid(n.first))
                {
                    Aux.insert(n.first);
                }
            }
            return !BFS(u, v, Aux);
        }
    }

    bool BFS(const Vertex &u, const Vertex &v)
    {
        std::unordered_map<Vertex, bool> labeled;
        std::queue<Vertex> Q;
        labeled[u] = true;
        Q.push(u);
        while (!Q.empty())
        {
            Vertex x = Q.front();
            Q.pop();
            if (x == v)
            {
                return true;
            }
            for (auto &n : graph[x])
            {
                if (labeled.find(n.first) == labeled.end())
                {
                    labeled[n.first] = true;
                    Q.push(n.first);
                }
            }
        }
        return false;
    }

    bool BFS(const Vertex &u, const Vertex &v, const std::unordered_set<Vertex> &marked)
    {
        std::unordered_map<Vertex, bool> labeled;
        std::queue<Vertex> Q;
        labeled[u] = true; //u,v are marked by programmer;
        Q.push(u);
        while (!Q.empty())
        {
            Vertex x = Q.front();
            Q.pop();
            if (x == v)
            {
                return true;
            }
            for (auto &n : graph[x])
            {
                if (marked.find(n.first) != marked.end())
                {
                    if (labeled.find(n.first) == labeled.end())
                    {
                        labeled[n.first] = true;
                        Q.push(n.first);
                    }
                }
            }
        }
        return false;
    }

    void generateTree(std::vector<Vertex> &V)
    {
        std::vector<Vertex> dst(V);
        addVertex(dst.back());
        std::cout << graph.begin()->first.id << " is root" << std::endl;
        dst.pop_back();
        while (!dst.empty())
        {
            addEdge(getRandomVertex(), dst.back());
            dst.pop_back();
        }
    }

    // input: edges number, graph G without vertices inside
    // output: graph G with vertices and edges
    void generateChordal(std::vector<Vertex> &V, int E)
    {
        //generate a tree https://nokyotsu.com/qscripts/2008/05/generating-random-trees-and-connected.html
        std::vector<Vertex> dst(V);
        addVertex(dst.back());
        dst.pop_back();
        while (!dst.empty())
        {
            addEdge(getRandomVertex(), dst.back());
            dst.pop_back();
        }
        //for edges: insert_query;
        int edges = E - (V.size() - 1); //m-(n-1) where (n-1) has been spent on tree edges
        unsigned int max_degree = (V.size() - 1);
        while (edges > 0) //Add edge  until desired number is achived
        {
            for (auto &v : graph)
            {
                if (edges <= 0)
                    break;
                if (v.second.size() > max_degree)
                {
                    continue;
                }
                for (auto &u : graph)
                {
                    if (edges <= 0)
                        break;
                    if (v.first == u.first)
                        continue;
                    if (v.second.size() > max_degree)
                    {
                        break;
                    }
                    if (u.second.size() > max_degree)
                    {
                        continue;
                    }
                    if (!isAdjacent(v.first, u.first))
                    {
                        if (insert_query(v.first, u.first))
                        {
                            addEdge(v.first, u.first);
                            edges = edges - 1;
                        }
                    }
                }
            }
        }
    }
};
