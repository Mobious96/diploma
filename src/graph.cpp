//#include "graph.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <time.h>

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
        graph[vertex] = {}; // O(1);
        // if (graph.find(vertex) == graph.end()) //if graph[vertex.id] not found  // O(n)
        // {
        //     graph[vertex] = {};
        //     return true;
        // }
        // return false;
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
        try
        {
            graph.at(v).at(u);
            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }

    //returns true if graph have the v vertex
    bool isValid(const Vertex &v)
    {
        try
        {
            graph.at(v);
            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }

    bool insert_query(const Vertex &u, const Vertex &v)
    {
        Graph I;
        for (auto &n : graph[u]) //for all neighborhoods of u O(m)
        {
            if (isAdjacent(v, n.first))
            {
                I.addVertex(n.first);
                //std::cout << "Adding " << n.first.id << std::endl;
            }

            // if (graph[v].find(n.first) != graph[v].end()) //if n contains in v.neighborhood
            // {
            //     I.addVertex(n.first);
            //     std::cout << "Adding " << n.first.id << std::endl;
            // }
        }
        if (I.graph.size() == 0)
        {
            return false; //Graph is not chordal
        }
        else
        {
            Graph Aux;
            //x is I[1] vertex
            for (auto &n : graph[I.graph.begin()->first]) //for all n = neighborhoods of x in graph G; O(m)-(very small)
            {
                if (!I.isValid(n.first))
                {
                    Aux.addVertex(n.first);
                    //std::cout << n.first.id << " ";
                }
                // if (I.graph.find(n.first) != I.graph.end()) //if I doesn't have the n, then add, overwise don't
                // {
                //     Aux.addVertex(n.first);
                // }
            }
            // std::cout << std::endl;
            for (auto &v : Aux.graph) //add edges from graph G to Aux O(m) (small)
            {
                for (auto &u : Aux.graph)
                {
                    if (isAdjacent(u.first, v.first)) //O(1)
                    {
                        Aux.addEdge(u.first, v.first);
                    }
                }
                //Aux.graph[v.first] = graph[v.first];
            }
            return !Aux.BFS(u, v);

            // Aux.BFS(u, v)
            // {
            // }

            // for (auto v : Aux.graph)
            // {
            //     std::cout << v.first.id << ": ";
            //     for (auto v2 : v.second)
            //     {
            //         std::cout << v2.first.id << " ";
            //     }
            //     std::cout << std::endl;
            // }
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
                try
                {
                    labeled.at(n.first); //if exists -> labeled -> do nothing
                }
                catch (const std::exception &e)
                {
                    labeled[n.first] = true;
                    Q.push(n.first);
                }
            }
        }
        return false;
    }

    // input: edges number, graph G without vertices inside
    // output: graph G with vertices and edges
    void generateChordal(std::vector<Vertex> &V, int E)
    {
        //generate a tree https://nokyotsu.com/qscripts/2008/05/generating-random-trees-and-connected.html
        std::vector<Vertex> dst(V);
        addVertex(dst.back());
        std::cout << graph.begin()->first.id << " is root" << std::endl;
        dst.pop_back();
        while (!dst.empty())
        {
            addEdge(getRandomVertex(), dst.back());
            dst.pop_back();
        }
        //for edges: insert_query;
        int edges = E - (V.size() - 1); //m-(n-1) where (n-1) has been spent on tree edges
        std::cout << "New edges: " << edges << std::endl;
        unsigned int max_degree = (V.size() - 1);

        // for (auto &v : graph)
        // {
        //     std::cout << v.first.id << ": ";
        //     for (auto &v2 : v.second)
        //     {
        //         std::cout << v2.first.id << " ";
        //     }
        //     std::cout << std::endl;
        //     //v.first.id = 3;
        // }
        //std::cout << std::endl;
        //int max_degree = 4 + (V.size() / edges);

        while (edges > 0) //Add edge  until desired number is achived
        {
            std::cout << edges << " out of " << E - (V.size() - 1) << std::endl;

            //Very long method, O(n^2*m) with many colisions
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
                    if (v.second.size() > max_degree)
                    {
                        break;
                    }
                    if (u.second.size() > max_degree)
                    {
                        continue;
                    }
                    if (!isAdjacent(v.first, u.first) && !(v.first == u.first))
                    {
                        if (insert_query(v.first, u.first))
                        {
                            addEdge(v.first, u.first);
                            edges = edges - 1;
                        }
                    }
                }
            }
            // for (auto v : graph) //makes 0th vertex have all edges instead of uniform distribution
            // {
            //     if (edges <= 0)
            //         break;
            //     for (auto u : graph)
            //     {
            //         if (edges <= 0)
            //             break;
            //         if (!isAdjacent(v.first, u.first) && !(v.first == u.first))
            //         {
            //             //std::cout << "true" << std::endl;
            //             if (insert_query(v.first, u.first))
            //             {
            //                 //std::cout << "adding " << v.first.id << "~" << u.first.id << std::endl;
            //                 std::cout << "Edges:" << edges << std::endl;
            //                 addEdge(v.first, u.first);
            //                 edges = edges - 1;
            //             }
            //         }
            //     }
            // }
        }
    }
};
