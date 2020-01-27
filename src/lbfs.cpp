#include "graph.cpp"
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm> //max_element
#include <map>
#include <stack>

bool PEO(Graph &G, std::map<int, Vertex> &number)
{
    for (auto u = number.begin(); u != number.end(); u++)
    {
        auto n(u);
        std::unordered_set<Vertex> temp; //probably need order here to understand
        temp.insert(n->second);

        //I MUST USE N(ui)AND(uj: j<=i); NOT "OR" FUCKING HELL!!!!!!!!!!!!!!!!!!
        //PERFECT ELIMINTATION ORDERING DOCUEMNT;



        //Critical error: it won't reach .begin !!!
        while (n != number.begin()) //v[i] < u in number
        {
            n--;
            temp.insert(n->second);
        }
        for (auto v : G.graph[u->second]) //neighborhood
        {
            temp.insert(v.first);
        }

        for (auto &u2 : temp)
        {
            for (auto &v : temp)
            {
                if (!(u2 == v))
                {
                    if (!G.isAdjacent(u2, v))
                    {
                        std::cout << u2.id << " and " << v.id << " are not adjacent" << std::endl;
                        for (auto i : temp)
                        {
                            std::cout << i.id << " ";
                        }
                        std::cout << std::endl;
                        std::cout << "u is " << u->second.id << std::endl;
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
    //slices[N]      =   {u}            - slice
    //slcies[N-1]    =   {v1, v2}       - slice
    //slices[N-2]    =   {v3, v4, v5}   - slice
    //std::map<int, std::unordered_set<Vertex>> slices; //is better than label because

    std::unordered_map<Vertex, int> label; // to have fast access to appending label
    //it's better because we have label(w) calls much more than picking-largest-label
    //so label(w) costs O(1) and finding largest O(N), otherwise it would cost label(w) O(N) and finding O(1)

    //std::multimap<int, Vertex> label;
    //std::set<const Vertex> number;//O(logN) search, insert
    std::unordered_map<Vertex, int> number; //O(1) serach, insert, but requires sorting in the end, which is fast
    for (auto &v : G.graph)
    {
        label[v.first] = 0;
        //slices[0].insert(v.first);
    }
    label[u] = G.graph.size();
    //slices[0].erase(u);
    //slices[G.graph.size()].insert(u);

    for (int i = G.graph.size(); i > 0; i--) //O(N)
    {
        auto &v = std::max_element(label.begin(), label.end(), [](auto &a, auto &b) { //v must be unnumbered
                      return (a.second < b.second);
                  })
                      ->first; //O(N);
        //std::cout << v.id << ":" << label[v] << " ";
        //since vertex.number is unique, there's no need to store a map int-vertex
        number[v] = G.graph.size() + 1 - i;
        label.erase(v); //unnumber the v;
        //std::cout << v.id << ":" << number[v] << std::endl;
        for (auto &w : G.graph[v])
        {
            //std::cout << "found:" << w.first.id << ":" << label[w.first] << std::endl;
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

    std::cout << "INPUT:" << std::endl;
    for (auto &n : _number)
    {
        std::cout << n.second.id << " ";
    }
    std::cout << std::endl;
    //slices[N]      =   {u}            - slice
    //slcies[N-1]    =   {v1, v2}       - slice
    //slices[N-2]    =   {v3, v4, v5}   - slice
    //std::map<int, std::unordered_set<Vertex>> slices; //is better than label because

    std::unordered_map<Vertex, int> label; // to have fast access to appending label
    //it's better because we have label(w) calls much more than picking-largest-label
    //so label(w) costs O(1) and finding largest O(N), otherwise it would cost label(w) O(N) and finding O(1)

    //std::multimap<int, Vertex> label;
    //std::set<const Vertex> number;//O(logN) search, insert
    std::unordered_map<Vertex, int> number; //O(1) serach, insert, but requires sorting in the end, which is fast
    for (auto &v : G.graph)
    {
        label[v.first] = 0;
        //slices[0].insert(v.first);
    }
    //label[u] = G.graph.size();
    //slices[0].erase(u);
    //slices[G.graph.size()].insert(u);
    std::cout << "Graph size: " << G.graph.size() << std::endl;
    for (int i = G.graph.size(); i > 0; i--) //O(N)
    {
        std::cout << "i:" << i << std::endl;
        std::stack<Vertex> stack;
        auto it = _number.begin();
        int largest_label = label[it->second];
        //stack.push(it->second);

        while (it != _number.end()) //instead should use queue and .end()
        {
            std::cout << "it: " << it->second.id << " label = " << label[it->second] << std::endl;
            if (label[it->second] >= largest_label)
            {
                largest_label = label[it->second];
                stack.push(it->second);
            }
            it++;
        }
        auto &v = stack.top();
        std::cout << "v: " << v.id << " label = " << label[v] << std::endl;

        number[v] = G.graph.size() + 1 - i;
        label.erase(v); //unnumber the v;
        //std::cout << v.id << ":" << number[v] << std::endl;
        for (auto &w : G.graph[v])
        {
            //std::cout << "found:" << w.first.id << ":" << label[w.first] << std::endl;
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

std::map<int, Vertex> LBFSArbitary(Graph &G)
{
    //slices[N]      =   {u}            - slice
    //slcies[N-1]    =   {v1, v2}       - slice
    //slices[N-2]    =   {v3, v4, v5}   - slice
    //std::map<int, std::unordered_set<Vertex>> slices; //is better than label because

    std::unordered_map<Vertex, int> label; // to have fast access to appending label
    //it's better because we have label(w) calls much more than picking-largest-label
    //so label(w) costs O(1) and finding largest O(N), otherwise it would cost label(w) O(N) and finding O(1)

    //std::multimap<int, Vertex> label;
    //std::set<const Vertex> number;//O(logN) search, insert
    std::unordered_map<Vertex, int> number; //O(1) serach, insert, but requires sorting in the end, which is fast
    for (auto &v : G.graph)
    {
        label[v.first] = 0;
        //slices[0].insert(v.first);
    }
    //label[u] = G.graph.size();
    //slices[0].erase(u);
    //slices[G.graph.size()].insert(u);
    for (int i = G.graph.size(); i > 0; i--) //O(N)
    {
        auto &v = std::max_element(label.begin(), label.end(), [](auto &a, auto &b) { //v must be unnumbered
                      return (a.second < b.second);
                  })
                      ->first; //O(N);
        number[v] = G.graph.size() + 1 - i;
        label.erase(v); //unnumber the v;
        //std::cout << v.id << ":" << number[v] << std::endl;
        for (auto &w : G.graph[v])
        {
            //std::cout << "found:" << w.first.id << ":" << label[w.first] << std::endl;
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