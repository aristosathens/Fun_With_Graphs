// Aristos Athens

//
// Compiler Guard
//

#pragma once

//
// Include
//

#include <map>
#include <vector>
#include <string>
#include <unordered_set>

//
// Types
//

enum SearchMethod
{
    BFS,
    DFS,
    Djikstra,
    A_Star
};

//
// Classes
//

class Point
{
    public:
    Point(float in_x, float in_y) : x(in_x), y(in_y) { };
    float x;
    float y;
};

class Node
{
    //
    // Public
    //
    public:
    Node();
    void add_neighbors(std::map<Node*, float>);
    void add_neighbor(Node*, float);
    bool has_neighbor(Node*) const;
    float get_neighbor_cost(Node*) const;

    //
    // Private
    //
    private:
    std::string name;
    Point location;
    std::map<Node*, float> neighbors;
};

class Path
{
    //
    // Public
    //
    public:
    // Path();
    Path(Node* n) : nodes(std::vector<Node*> {n});
    float cost() const { return total_cost; }
    size_t num_nodes() const { return nodes.size(); }

    Node* start() const;
    Node* first() const { return start(); }
    Node* front() const { return start(); }

    Node* end() const;
    Node* last() const { return end(); }
    Node* back() const { return end(); }

    template<typename C>
    void add_nodes(C container) { for (auto item : container) { add_node(item); } }
    void add_node(Node*);

    bool operator<(const Path& rhs) { return cost() < rhs.cost() ; }

    //
    // Private
    //
    private:
    std::vector<Node*> nodes;
    float total_cost;
};

class Graph 
{
    //
    // Public
    //
    public:
    template<typename C>
    void add_nodes(C container) { for (auto item : container) { add_node(item); } };
    void add_node(Node*);

    Path* shortest_path(Node*, Node*, SearchMethod);
    Path* djikstras(Node*, Node*);

    //
    // Private
    //
    private:
    std::unordered_set<Node*> nodes;
};
