// Aristos Athens

//
// Include
//

#include "mapper.h"

#include <math.h>
#include <queue>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>

//
// Using
//

using namespace::std;

//
// Class methods
//

//
// -------------------------- Point class methods --------------------------
//

// Get string representation of Point object.
std::string Point::string(bool show_type /* = false */) const
{
    std::string str = "";
    if (show_type) {
        str += "Point: ";
    }
    str += "{" + to_string(x) + ", " + to_string(y) + "}";
    return str;
}

float Point::distance_to(Point p) const
{
    return pow(pow(x - p.x, 2) + pow(y - p.y, 2), 0.5);
}

float Point::distance_to(Point* p) const
{
    return pow(pow(x - p->x, 2) + pow(y - p->y, 2), 0.5);
}

//
// -------------------------- Node class methods --------------------------
//

// Get string representation of Node object.
std::string Node::string(bool index_only /* = false */) const
{
    if (index_only) {
        return to_string(index);
    }
    std::string str = "Node {";
    if (!name.empty()) {
        str += "Name: " + name + ", ";
    }
    str += "Index: " + to_string(index) + ", ";
    if (location != NULL) {
        str += "Location: " + location->string() + ", ";
    }
    return str.substr(0, str.size() - 2) + "}";
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

//
// -------------------------- Path class methods --------------------------
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

// Get string representation of Path object.
string Path::string(bool index_only /* = false */) const
{
    std::string str = "Path {Cost: " + to_string(cost()) + ", Number of nodes: " + to_string(num_nodes()) + "}\n";
    for (auto node : nodes) {
        str += "--> " + node->string(index_only) + " ";
    }
    return str;
}

//
// -------------------------- Graph class methods --------------------------
//

// Descructor. Free all Node objects.
Graph::~Graph()
{
    for (Node* node : nodes) {
        delete node;
    }
}

// Add node to graph.
void Graph::add_node(Node* node)
{
    nodes.insert(node);
    index_map[node->index] = node;
}

// Check if Graph has node.
bool Graph::contains_node(Node* node) const
{
    if (nodes.find(node) != nodes.end()) {
        return true;
    } else {
        return false;
    }
}

// Check if Graph has node with matching index. If ptr not NULL, put found node into ptr.
bool Graph::contains_index(size_t index, Node** ptr /* = NULL */) const
{
    if (index_map.empty()) {
        return false;
    }
    auto node = index_map.find(index);
    if (node != index_map.end()) {
        if (ptr != NULL) {
            auto val = (*node).second;
            if (val == NULL) {
                throw runtime_error("Node* value in index_map is NULL.");
            }
            *ptr = val;
        }
        return true;
    } else {
        return false;
    }
}

// Add new edge.
void Graph::load_edge(size_t start_index, size_t end_index, float cost)
{
    // If nodes already exist, get them. Else, create new objects and add to Graph.
    Node *start_node, *end_node;
    if (!contains_index(start_index, &start_node)) {
        start_node = new Node(start_index);
        add_node(start_node);
    }
    if (!contains_index(end_index, &end_node)) {
        end_node = new Node(end_index);
        add_node(end_node);
    }
    // Add edge.
    start_node->add_neighbor(end_node, cost);
}

// Load dataset.
void Graph::load_dataset(string file_name, DataSetType data_set_type, size_t num_to_load /* = NUM_TO_LOAD */)
{
    if (verbose) print("Loading dataset at " + file_name + "...");
    switch (data_set_type) {
    case DIMACS:
        load_DIMACS_dataset(file_name, num_to_load);
        break;
    case SNAP:
        load_SNAP_dataset(file_name, num_to_load);
        break;
    default:
        throw runtime_error("No implementation for that DataSetType.");
    }
    if (verbose) println("Finished loading dataset.");
}

// Load DIMACS dataset. (http://www.dis.uniroma1.it/challenge9/download.shtml)
void Graph::load_DIMACS_dataset(string file_name, size_t num_to_load)
{
    ifstream file(file_name);
    string line, first_char;
    size_t index_1, index_2, num_loaded = 0;
    float cost;
    while (getline(file, line) && num_loaded <= num_to_load) {
        istringstream ss(line); 
        ss >> first_char;
        if (first_char != "a") {
            continue;
        }
        ss >> index_1;
        ss >> index_2;
        ss >> cost;
        load_edge(index_1, index_2, cost);
        num_loaded++;
    }
}

// Load SNAP dataset. (https://snap.stanford.edu/data/)
void Graph::load_SNAP_dataset(string file_name, size_t num_to_load)
{
    ifstream file(file_name);
    string line;
    size_t index_1, index_2, num_loaded = 0;
    while (getline(file, line) && num_loaded <= num_to_load) {
        istringstream ss(line); 
        if (ss.peek() == '#') {
            continue;
        }
        ss >> index_1;
        ss >> index_2;
        load_edge(index_1, index_2, DEFAULT_COST);
        num_loaded++;
    }
}

// Get shortest Path. Throw exception if invalid nodes or no path exists.
Path* Graph::shortest_path(size_t start_index, size_t end_index, SearchMethod method /* = Djikstra*/) const
{
    Node *start_node, *end_node;
    if (!contains_index(start_index, &start_node) || !contains_index(end_index, &end_node)) {
        throw runtime_error("Passed in node index that does not exit in this graph.");
    }
    return shortest_path(start_node, end_node, method);
}

// Get shortest Path. Throw exception if invalid nodes or no path exists.
Path* Graph::shortest_path(Node* start, Node* end, SearchMethod method /* = Djikstra */) const
{
    if (verbose) print("Finding shortest path...");
    if (!contains_node(start) || !contains_node(end)) {
        throw runtime_error("Passed in node that does not exist in this graph.");
    }
    Path* ptr;
    switch (method) {
    case Djikstra:
        ptr = djikstras(start, end);
        break;
    default:
        throw runtime_error("Passed in SearchMethod is not implemented.");
    }
    if (verbose) println("Finished finding shortest path.");
    return ptr;
}

// Find shortest path using Depth First Search.
Path* Graph::DFS(Node* start, Node* destination) const
{
    stack<Path*> stack;
    stack.push(new Path(start));
    unordered_set<Node*> seen;

    while (!stack.empty()) {
        Path* current_path = stack.top();
        stack.pop();
        Node* current_node = current_path->last();
        if (current_node == destination) {
            return current_path;
        }
        if (seen.find(current_node) != seen.end()) {
            continue;
        }
        seen.insert(current_node);
        for (auto node_pair : current_node->neighbors) {
            stack.push(new Path(current_path, node_pair.first));
        }
    }
    throw runtime_error("No path found between nodes using Depth First Search method.");
}

// Find shortest path using Djikstra's algorithm.
Path* Graph::djikstras(Node* start, Node* destination) const
{
    priority_queue<Path*> pq;
    pq.push(new Path(start));
    unordered_set<Node*> seen;

    while (!pq.empty()) {
        Path* current_path = pq.top();
        pq.pop();
        Node* current_node = current_path->last();
        if (current_node == destination) {
            return current_path;
        }
        if (seen.find(current_node) != seen.end()) {
            continue;
        }
        seen.insert(current_node);
        for (auto node_pair : current_node->neighbors) {
            pq.push(new Path(current_path, node_pair.first));
        }
    }
    throw runtime_error("No path found between nodes using Djikstra's search method.");
}