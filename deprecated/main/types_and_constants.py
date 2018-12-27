# Aristos Athens

from enum import Enum


# -------------------------------- Exceptions -------------------------------- #

class NotImplementedException(Exception):
    pass

class TypeException(Exception):
    pass

class SameNodeException(Exception):
    pass

class SamePathException(Exception):
    pass

class MissingNodeException(Exception):
    pass

class NotANeighborException(Exception):
    pass

class NoPathException(Exception):
    pass


# -------------------------------- Enum Types ---------------------------------- #

class Units(Enum):
    km = 1
    mi = 2
    longlat = 3

class SearchMethod(Enum):
    DFS = 1
    BFS = 2
    A_Star = 3
    Djikstra = 4

class DataSet(Enum):
    DIMACS = 1  # ex: http://www.dis.uniroma1.it/challenge9/download.shtml
    SNAP = 2    # ex: https://snap.stanford.edu/data/roadNet-CA.html