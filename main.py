# Aristos Athens

from typing import *
from mapping import *


def main():
    A = MapNode(11, 15, name = "NodeA")
    B = MapNode(13, 17, name = "NodeB")
    C = MapNode(18, 15, name = "NodeC")
    D = MapNode(12, 1, name = "NodeD")

    A.add_neighbor(B)
    B.add_neighbor(C)
    C.add_neighbor(D)

    p1 = Path()
    p1.add_node(A)
    p1.add_node(B)
    print(p1)

    p2 = Path()
    p2.add_node(C)
    p2.add_node(D)
    print(p2)

    p1.extend(p2)
    print(p1)


if __name__ == "__main__":
    main()