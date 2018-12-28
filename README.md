# Fun_With_Graphs
Custom class for generating graphs and finding shortest paths

## Description
This tool is for finding shortest paths through graphs.
Provides different search methods (DFS, Djikstra's, etc.) and different data loaders (DIMACS format, etc.)

## Usage
`g++ main.cc mapper.h mapper.cc`: Build the files.

`main.exe <num_edges> <start_index> <end_index>`: Run main(). Loads num_edges then find shortest path between nodes represented by start_index and end_index. Example: `a.exe 100000 2 576`.
