//#include "graph.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <time.h>

static int vertices_count = 0;

template <typename T>
class Vertex
{
public:
    int id;
    mutable T data;
    Vertex()
    {
        id = vertices_count++;
    }

    bool operator==(const Vertex &v) const
    {
        return (id == v.id);
    }
};

//For defying custom key hash we need operator== and hash<Vertex<T>>
namespace std
{
template <typename T>
struct hash<Vertex<T>>
{
    std::size_t operator()(const Vertex<T> &vertex) const
    {
        return hash<int>()(vertex.id);
    }
};
} // namespace std

template <typename T>
class Graph
{
public:
    std::unordered_map<Vertex<T>, std::unordered_map<int, Vertex<T>>> graph;
    std::vector<Vertex<T>> vertices;

public:
    void deleteVertex(Vertex<T> &);
    std::vector<Vertex<T>> getNeighborhood(Vertex<T> &);

    bool addVertex(Vertex<T> &vertex)
    {
        if (graph.find(vertex) == graph.end()) //if graph[vertex.id] not found
        {
            graph[vertex] = {};
            return true;
        }
        return false;
    }

    void addEdge(const Vertex<T> &vertex, const Vertex<T> &new_vertex)
    {
        graph[vertex][new_vertex.id] = new_vertex; // O(1)
        graph[new_vertex][vertex.id] = vertex;     // O(1)
    }

    Graph()
    {
        graph = {};
    }

    Graph(std::vector<Vertex<T>> &Vertices)
    {
        vertices = Vertices;
        for (auto v : Vertices)
        {
            addVertex(v);
        }
    }

    const Vertex<T> &getRandomVertex()
    {
        srand(time(NULL));
        return std::next(graph.begin(), int(rand() % graph.size()))->first;
    }

    bool insert_query(Vertex<T> &u, Vertex<T> &v)
    {
        Graph I;
        for (auto x : graph[u])
        {
            if (graph[v].find(x.second.id) != graph[v].end())
            {
                I.addVertex(x.second);
            }
        }
        if (I.graph.size() == 0)
        {
            return false;
        }
        else
        {
            Graph Aux;
            //x is I.begin();
            for (auto n : graph[I.graph.begin()->first])
            {
                if (I.graph.find(n.second) != I.graph.end())
                {
                    Aux.addVertex(n.second);
                }
            }
            for (auto v : Aux.graph)
            {
                Aux.graph[v.first] = graph[v.first];
            }

            for (auto v : Aux.graph)
            {
                std::cout << v.first.id << ": ";
                for (auto v2 : v.second)
                {
                    std::cout << v2.first << " ";
                }
                std::cout << std::endl;
                //v.first.id = 3;
            }
        }
    }

    //input: edges number, graph G without vertices inside
    //output: graph G with vertices and edges
    void generateChordal(std::vector<Vertex<T>> &V, int E)
    {
        //generate a tree https://nokyotsu.com/qscripts/2008/05/generating-random-trees-and-connected.html
        std::vector<Vertex<T>> dst(V);
        addVertex(dst.back());
        //std::cout << graph.begin()->first.id << " is root" << std::endl;
        dst.pop_back();
        while (!dst.empty())
        {
            addEdge(getRandomVertex(), dst.back());
            dst.pop_back();
        }
        //for edges: insert_query;
    }
};
