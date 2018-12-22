# Aristos Athens

from typing import *
from mapping import *


def main():
    '''
        Testing
    '''
    A = MapNode(11, 15, name = "NodeA")
    B = MapNode(13, 17, name = "NodeB")
    C = MapNode(18, 15, name = "NodeC")
    D = MapNode(12, 1, name = "NodeD")
    Z = MapNode(11.5, 10, name = "NodeZ")

    A.add_neighbor(B)
    B.add_neighbors([A, C, Z])
    Z.add_neighbor(D)
    C.add_neighbor(B)


    print("A neighbors: ", A.neighbors)
    print("B neighbors: ", B.neighbors)
    print("C neighbors: ", C.neighbors)
    print("D neighbors: ", D.neighbors)
    print("Z neighbors: ", Z.neighbors)





    nodes = [A, B, C, D, Z]

    mapper = Mapper(nodes)

    path = mapper.shortest_path(A, D, SearchMethod.BFS_Djikstra)
    print(path)


    # p1 = Path()
    # p1.add_node(A)
    # p1.add_node(B)
    # print(p1)

    # p2 = Path()
    # p2.add_node(C)
    # p2.add_node(D)
    # print(p2)

    # p1.extend(p2)
    # print(p1)


if __name__ == "__main__":
    main()