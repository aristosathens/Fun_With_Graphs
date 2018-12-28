# Fun_With_Graphs
Custom class for generating graphs and finding shortest paths

## Description
This tool is for finding shortest paths through graphs.
Provides different search methods (DFS, Djikstra's, etc.) and different data loaders (DIMACS format, etc.)

## Usage
`make`: Compile using the makefile. \*nix only.

`g++ main.cc mapper.h mapper.cc`: Simple compile on Windows. Requires g++ installation (MinGW).

`main <num_edges> <start_index> <end_index>`: Run main(). Loads num_edges then find shortest path between nodes represented by start_index and end_index. Example: `a.exe 100000 2 576`.
At the time of this writing, executable will be `main` on \*nix, `a.exe` on windows.
