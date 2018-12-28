// Aristos Athens

#include "mapper.h"
#include <iostream>
#include <cstdlib>

using namespace::std;

#define NUM_PARAMS 4
#define HELP_MESSAGE "Currently this program takes 3 arguments. Num edges to load, starting node index, destination node index."

void test_DIMACS(size_t start_index, size_t end_index, size_t num_to_load)
{
    string file_name = "./../data/USA-road-d.NY.gr";
    Graph mapper(true);
    mapper.load_dataset(file_name, DIMACS, num_to_load);
    Path* p = mapper.shortest_path(start_index, end_index);
    println(p->string());
}

void test_SNAP(size_t start_index, size_t end_index, size_t num_to_load)
{
    string file_name = "./../data/roadNet-CA.txt";
    Graph mapper(true);
    mapper.load_dataset(file_name, SNAP, num_to_load);
    Path* p = mapper.shortest_path(start_index, end_index);
    println(p->string());
}

int main(int argc, char** argv)
{
    size_t num_to_load;
    size_t start_index;
    size_t end_index;

    if (argc != NUM_PARAMS) {
        println(HELP_MESSAGE);
        exit(-1);
    } else {
        num_to_load = atoi(argv[1]);
        start_index = atoi(argv[2]);
        end_index = atoi(argv[3]);
    }

    test_SNAP(start_index, end_index, num_to_load);


    // print("How many data points to load: ");
    // cin >> num_to_load;
    // println("");

    // print("Starting node number: ");
    // cin >> start_index;
    // print("");

    // print("Destination node number: ");
    // cin >> end_index;
    // print("");



    return 0;
}