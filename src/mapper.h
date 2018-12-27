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
#include <iostream>

//
// Define
//

#define DEFAULT_NUM_TO_LOAD 2000

//
// Enum
//

enum DataSetType
{
    DIMACS,
};

enum SearchMethod
{
    BFS,
    DFS,
    Djikstra,
    A_Star,
};

//
// Helpers
//

template<typename T>
inline void print(T val)
{
    std::cout << val << std::flush;
}

template<typename T>
inline void println(T val)
{
    print(val);
    print("\n");
}

//
// Classes
//

class Point
{
    //
    // Public
    //
    public:
    // Constructor
    Point() {};
    Point(float in_x, float in_y) : x(in_x), y(in_y) {};

    // Access methods
    float distance_to(Point) const;
    float distance_to(Point*) const;

    float x;
    float y;
};

class Node
{
    //
    // Public
    //
    public:
    // Constructor
    Node() {};
    Node(size_t in_index) : index(in_index) {};
    
    // Access methods
    float get_neighbor_cost(Node*) const;
    bool has_neighbor(Node*) const;

    // Modifier methods
    void add_neighbors(std::map<Node*, float>);
    void add_neighbor(Node*, float);
    
    size_t index;
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
    // Constructor
    Path() {};
    Path(Node* n) : nodes(std::vector<Node*> {n}) {};
    Path(Path* old) : nodes(old->nodes), total_cost(old->total_cost) {};
    
    // Access methods
    float cost() const { return total_cost; }
    size_t num_nodes() const { return nodes.size(); }
    std::string string() const;

    Node* start() const;
    inline Node* first() const { return start(); }
    inline Node* front() const { return start(); }

    Node* end() const;
    inline Node* last() const { return end(); }
    inline Node* back() const { return end(); }

    // Modifier methods
    template<typename C>
    void add_nodes(C container) { for (auto item : container) { add_node(item); } }
    void add_node(Node*);

    // Operators
    bool operator<(const Path& rhs) { return (1.0 / cost()) < (1.0 / rhs.cost()) ; }

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
    // Constructor
    Graph() {};
    Graph(bool v) : verbose(v) {};

    // Access methods
    bool contains_index(size_t, Node** = NULL) const;
    bool contains_node(Node*) const;
    Path* shortest_path(size_t, size_t, SearchMethod = Djikstra) const;
    Path* shortest_path(Node*, Node*, SearchMethod = Djikstra) const;

    // Modifier methods
    void load_dataset(std::string, DataSetType, size_t = DEFAULT_NUM_TO_LOAD);

    template<typename C>
    void add_nodes(C container) { for (auto item : container) { add_node(item); } };
    void add_node(Node*);

    //
    // Private
    //
    private:
    bool verbose;
    std::unordered_set<Node*> nodes;
    std::map<size_t, Node*> index_map;

    Path* djikstras(Node*, Node*) const;

    void load_DIMACS_dataset(std::string, size_t);
};
