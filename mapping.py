# Aristos Athens

from typing import *

from enum import Enum



# -------------------------------- Exceptions -------------------------------- #

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


# ---------------------------------- Types ----------------------------------- #

class Units(Enum):
    km = 1
    mi = 2
    longlat = 3

class SearchMethod(Enum):
    DFS = 1
    BFS_Djikstra = 2
    BFS_Unweighted = 3


# --------------------------------- Classes ---------------------------------- #

class MapNode():
    '''
        MapNode class
        Use in Mapper class.
    '''

    def __init__(self,
                    x : float,
                    y : float,
                    name : str = "Unnamed",
                    neighbors : Dict['MapNode', float] = {}):
        '''
            Initialize MapNode
        '''
        self.x = x
        self.y = y
        self.name = name
        self.neighbors = {}

        if type(neighbors) is dict:
            self.neighbors = neighbors
        elif type(neighbors) is list:
            for n in neighbors:
                self.add_neighbor(n)
        else:
            raise TypeException("Neighbors must be of type dict{MapNode, float} or list[MapNode].")


    def __repr__(self):
        '''
            Generate string representation of MapNode object.
        '''
        return type(self).__name__ + ": " + self.name + " (x: " + str(self.x) + ", y: " + str(self.y) + ")"


    def add_neighbor(self, 
                        neighbor : 'MapNode',
                        cost : float = None):
        '''
            Add new neighbor node.
        '''
        if neighbor is self:
            raise SameNodeException("Cannot add node as own neighbor.")
        elif neighbor in self.neighbors:
            raise SameNodeException("This node already exists as a neighbor. Use update_neighbor_cost() instead.")

        # Default cost
        if cost is None:
            cost = distance(self, neighbor)

        self.neighbors.update({neighbor : cost})


    def update_neighbor_cost(self,
                                neighbor : 'MapNode',
                                cost : float):
        '''
            Update the pathing cost between self and neighbor node, if node exists.
        '''
        if neighbor not in self.neighbors:
            raise MissingNodeException("Cannot update neighbor node's cost. Neighbor not in node.neighbors.")

        self.neighbors[neighbor] = cost


class Path():
    '''
        Path class
    '''

    def __init__(self):
        '''
            Initialize Path
        '''
        self.nodes = []
        self.cost = 0
        self.num_nodes = 0
        self.index = 0  # Used for iterating


    def __iter__(self) -> 'Path':
        '''
            Generate iterable representation of Path object.
        '''
        return self


    def __next__(self) -> MapNode:
        '''
            Get next item from Path. Used for iterable representation of Path object.
        '''
        try:
            node = self.nodes[self.index]
        except IndexError:
            self.index = 0
            raise StopIteration()
        self.index += 1
        return node


    def __repr__(self) -> str:
        '''
            Generate string representation of Path object.
        '''
        string = type(self).__name__ + " | "
        string +=  "cost: " + str(self.cost) + " num_nodes: " + str(self.num_nodes) + "\n"
        for n in self.nodes:
            string += str(n) + " -> "
        return string[:-4]

    def start(self) -> MapNode:
        '''
            Return first node in Path.
        '''
        if len(self.nodes) is 0:
            return None
        else:
            return self.nodes[0]

    def end(self) -> MapNode:
        '''
            Return last node in Path.
        '''
        if len(self.nodes) is 0:
            return None
        else:
            return self.nodes[-1]

    def add_node(self, node : MapNode):
        '''
            Add node to end of Path, and update internal data as necessary.
        '''
        if self.start() is None:
            self.num_nodes = 1
            self.nodes.append(node)
        else:
            if node not in self.end().neighbors:
                print("end: ", self.end())
                print("node: ", node)
                raise NotANeighborException("Can't add this node to path. Input node is not neighbor of end node.")
            self.num_nodes += 1
            self.cost += self.end().neighbors[node]
            self.nodes.append(node)

    def extend(self, new_path : 'Path'):
        '''
            Extend path with nodes from new path.
        '''
        if new_path is self:
            raise SamePathException("Cannot add path to itself.")

        for node in new_path:
                self.add_node(node)


class Mapper():
    '''
        Mapper class
        Node names must be unique.
    '''

    def __init__(self):
        '''
            Initialize Mapper
        '''
        self.nodes = None


    def shortest_path(self,
                        source : MapNode,
                        destination : MapNode,
                        search_method : SearchMethod) -> Path:
        '''
            Find the shortest path between the source and destination nodes.
            Raises exception if nodes do not exist.
        '''
        if source not in self.nodes:
            raise Exception("Source node: \"" + str(source) + "\" not in Mapper.")
        elif destination not in self.nodes:
            raise Exception("Destination node: \"" + str(destination) + "\" not in Mapper.")
        elif source is destination:
            raise SameNodeException("Source node and destination node cannot be the same.")

        if search_method is SearchMethod.DFS:
            return self.DFS(source, destination)
        elif search_method is SearchMethod.BFS_Unweighted:
            return self.BFS(source, destination)
        elif search_method is SearchMethod.BFS_Djikstra:
            return self.djikstra(source, destination)
        else:
            raise TypeException("SearchMethod type not defined.")


    def djikstra(self,
                    source : MapNode,
                    destination : MapNode) -> Path:
    '''
        Get shortest path using Djikstra's graph search method.
    '''


# ---------------------------------- Helpers ----------------------------------- #

def distance(start : MapNode, end : MapNode):
    '''
        Find Euclidean distance between MapNodes.
    '''
    return (((start.x - end.x) ** 2) + ((start.y - end.y) ** 2)) ** 0.5