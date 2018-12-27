// Aristos Athens

#include "mapper.h"
#include <iostream>

using namespace::std;

int main()
{
    size_t num_to_load;
    print("How many data points to load: ");
    cin >> num_to_load;
    println("");

    size_t start_index;
    print("Starting node number: ");
    cin >> start_index;
    print("");

    size_t end_index;
    print("Destination node number: ");
    cin >> end_index;
    print("");

    string file_name = "./../data/USA-road-d.NY.gr";
    Graph mapper(true);
    mapper.load_dataset(file_name, DIMACS, num_to_load);
    cout << "here" << endl << flush;
    Path* p = mapper.shortest_path(start_index, end_index);
    cout << "there" << endl << flush;
    cout << "Path cost: " << p->cost() << endl ;
    cout << flush;
    return 0;
}