#pragma once
#include "lbfs.h"
using namespace std;


//O(n^2)
bool NeighbourhoodCondition(Graph &G, std::map<int, Vertex> &number)
{
    for (auto u : G.graph) //O(N)
    {
        for (auto it = number.begin(); it != number.end(); it++) // <O(N)
        {
            if (u.second.find(it->second) != u.second.end() || (it->second == u.first)) //we've found first element
            {
                for (int i = 0; i < u.second.size() + 1; i++)
                {
                    if ((u.second.find(it->second) == u.second.end()) && ((it->second.id != u.first.id)))
                    {
                        return false;
                    }
                    it++;
                }
            }
            if (it == number.end()) //the sad part is that in current stage "it" is the end and cycle 'for' will increment it, so it will be like end++ and then make comparison;
            {
                break;
            }
        }
    }
    return true;
}

bool PEO(Graph &G, std::map<int, Vertex> &number)
{
    for (auto u = number.begin(); u != number.end(); u++)
    {
        auto n(u);
        n++;
        std::unordered_set<Vertex> temp; //probably need order here to understand
        temp.insert(u->second);

        auto it = number.begin();
        while (it != n)
        {
            //std::cout << "it::" << it->second.id << std::endl;
            if (G.graph[u->second].find(it->second) != G.graph[u->second].end())
            {
                temp.insert(it->second);
            }
            it++;
        }

        for (auto &u2 : temp)
        {
            for (auto &v : temp)
            {
                if (!(u2 == v))
                {
                    if (!G.isAdjacent(u2, v))
                    {
                        std::cout << "[Error]: " << std::endl;
                        // std::cout << "\t"
                        //           << "u is " << u->second.id << std::endl;
                        std::cout << "\tNeighborhood of " << u->second.id << " with previous vertices in the LBFS+ ordering: ";
                        for (auto i : temp)
                        {
                            std::cout << i.id << " ";
                        }
                        std::cout << std::endl;
                        std::cout << "\t" << u2.id << " and " << v.id << " are not adjacent -> not a clique" << std::endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

std::map<int, Vertex> LBFS(Graph &G, const Vertex &u)
{
    
    std::unordered_map<Vertex, int> label; // to have fast access to appending label
    //it's better because we have label(w) calls much more than picking-largest-label
    //so label(w) costs O(1) and finding largest O(N), otherwise it would cost label(w) O(N) and finding O(1)

    std::unordered_map<Vertex, int> number; //O(1) serach, insert, but requires sorting in the end, which is fast
    for (auto &v : G.graph)
    {
        label[v.first] = 0;
        //slices[0].insert(v.first);
    }
    label[u] = G.graph.size();
    for (int i = G.graph.size(); i > 0; i--) //O(N)
    {
        auto v = std::max_element(label.begin(), label.end(), [](auto &a, auto &b) { //v must be unnumbered
                      return (a.second < b.second);
                  })
                      ->first; //O(N);
        if (number.find(v) != number.end())
        {
            cout << "LBFS ERROR: WORK WITH NUMBERED VERTEX: " << v.id << " i:" << i << endl;
        }
        number[v] = G.graph.size() + 1 - i;
        label.erase(v); //unnumber the v;
       // cout << "v:" << v.id;
        for (auto &w : G.graph[v])
        {
            if (number.find(w.first) == number.end()) //O(1)~O(graph[v].size)
            {
                label[w.first] = label[w.first] + i;
            }
        }
    }
    std::map<int, Vertex> result;
    for (auto u : number) //O(N)
    {
        result[u.second] = u.first;
    }
    return result;
};

std::map<int, Vertex> LBFSplus(Graph &G, std::map<int, Vertex> &_number)
{
    std::unordered_map<Vertex, int> label; // to have fast access to appending label
    //it's better because we have label(w) calls much more than picking-largest-label
    //so label(w) costs O(1) and finding largest O(N), otherwise it would cost label(w) O(N) and finding O(1)

    std::unordered_map<Vertex, int> number; //O(1) serach, insert, but requires sorting in the end, which is fast
   /* for (auto &v : G.graph)
    {
        label[v.first] = 0;
    }
    cout << "Graph size:" << G.graph.size() << endl;
    cout << "_number: ";
    for (auto n : _number)
    {
        cout << n.second.id << " ";
    }
    cout << endl << "_nunmber size:" << _number.size() << endl;*/
    for (int i = G.graph.size(); i > 0; i--) //O(N)
    {
        //std::stack<Vertex> stack;
        auto it = _number.begin();
        auto largest_vertex = it;
        int largest_label = 0;
        while (it != _number.end()) //instead should use queue and .end()
        {
            if (number.find(it->second) == number.end()) //
            {
                if (label[it->second] >= largest_label)
                {
                    largest_label = label[it->second];
                    largest_vertex = it;
                }
            }
            it++;
        }
        auto v = largest_vertex->second;

        /*cout << "v:" << v.id << " label:" << label[v] << endl;
        for (auto u : number)
        {
            cout << u.first.id << " ";
        }
        cout << endl;*/
        if (number.find(v) != number.end())
        {
            cout << "LFBS+ ERROR: WORK WITH NUMBERED VERTEX: " << v.id << " i:" << i << endl;
        }
        number[v] = G.graph.size() + 1 - i;
        //label.erase(v); //unnumber the v; //we erase, but above it give nno effect since lable[it] add it again;
        for (auto &w : G.graph[v])
        {
            if (number.find(w.first) == number.end()) //O(1)~O(graph[v].size)
            {
                label[w.first] = label[w.first] + i;
            }
        }
    }
    std::map<int, Vertex> result;
    for (auto u : number) //O(N)
    {
        result[u.second] = u.first;
    }
    return result;
};