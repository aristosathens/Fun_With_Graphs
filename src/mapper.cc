// Aristos Athens

//
// Include
//

#include "mapper.h"
#include <queue>

//
// Using
//

using namespace::std;

//
// Node class methods
//

// Add multiple neighbor nodes, from map of Node
void Node::add_neighbors(map<Node*, float> in_neighbors)
{
    for (auto n : in_neighbors) {
        add_neighbor(n.first, n.second);
    }
}

// Add new neighbor node.
void Node::add_neighbor(Node* neighbor, float cost)
{
    neighbors[neighbor] = cost;
}

// Check if Node has neighbor node.
bool Node::has_neighbor(Node* neighbor) const
{
    if (neighbors.find(neighbor) != neighbors.end()) {
        return true;
    } else {
        return false;
    }
}

// Get cost of neighbor. Throws an exception of neighbor is not valid.
float Node::get_neighbor_cost(Node* neighbor) const
{
    if (has_neighbor(neighbor)) {
        return (*neighbors.find(neighbor)).second;
    } else {
        throw runtime_error("Cannot get_neighbor_cost. This node does not contain that neighbor.");
    }
}

//
// Path class methods
//

// Return first element in Path.
Node* Path::start() const
{
    if (nodes.empty()) {
        return NULL;
    }
    return nodes.front();
}

// Return last element in Path.
Node* Path::end() const
{
    if (nodes.empty()) {
        return NULL;
    }
    return nodes.back();
}

// Add node to Path. Throw exception if cannot be added.
void Path::add_node(Node* new_node)
{
    Node* last_node = end();
    if (last_node == NULL) {
        nodes.push_back(new_node);
    } else if (last_node->has_neighbor(new_node)) {
        total_cost += last_node->get_neighbor_cost(new_node);
        nodes.push_back(new_node);
    } else {
        throw runtime_error("Cannot add node to Path. Last node does not contain new_node as neighbor.");
    }
}

//
// Graph class methods
//

Path* Graph::shortest_path(Node* start, Node* end, SearchMethod method = Djikstra)
{
    switch (method) {
    case Djikstra:
        return djikstras(start, end);
    default:
        throw runtime_error("Passed in SearchMethod is not implemented.");
    }
}

Path* Graph::djikstras(Node* start, Node* end)
{
    priority_queue<Path*> pq();
    pq.push(Path())

    
}



int main()
{

}