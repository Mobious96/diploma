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
    T data;
    Vertex()
    {
        id = vertices_count++;
    }
};
template <typename T>
size_t hashVertex(const Vertex<T> &vertex)
{
    return std::hash<int>()(vertex.id);
}

template <typename T>
class Graph
{
private:
    std::unordered_map<Vertex<T>, std::unordered_map<int, Vertex<T> &>, hashVertex> graph;

public:
    void insertVertex(Vertex<T> &);
    void deleteVertex(Vertex<T> &);
    void addEdge(Vertex<T> &, Vertex<T> &);
    std::vector<Vertex<T>> getNeighborhood(Vertex<T> &);
    /*
    void generateChordal(std::vector<Vertex<T>> vertices, int edges)
    {

        //generate a tree https://nokyotsu.com/qscripts/2008/05/generating-random-trees-and-connected.html
        srand(time(NULL));
        graph[vertices.front().id] = {}; //make a root
        vertices.erase(vertices.front());
        for (auto vertex : vertices)
        {
            addEdge(graph[std::next(graph.begin(), rand() % graph.size)->first], vertices.pop_back()); //graph[rand]->vertex, vertices[end];
            graph[vertex.id] = vertex;
            //vertices.erase(auto);
        }

        //for edges: insert_query;
    }
*/
};
