# Aristos Athens

import sys
import copy
import queue

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
        self.add_neighbors(neighbors)

    def __repr__(self):
        '''
            Generate string representation of MapNode object.
        '''
        return type(self).__name__ + ": " + self.name + " (x: " + str(self.x) + ", y: " + str(self.y) + ")"

    def add_neighbors(self, neighbors : Union[List[Union['MapNode', Tuple['MapNode', float]]], Dict['MapNode', float]]):
        '''
            Add mutliple neighbor nodes. Calls self.add_neighbor().
        '''
        if type(neighbors) is dict:
            for node, cost in neighbors.items():
                self.add_neighbor(node, cost)
        elif type(neighbors) is list:
            for neighbor in neighbors:
                if type(neighbor) is MapNode:
                    self.add_neighbor(neighbor)
                elif type(neighbor) is tuple:
                    self.add_neighbor(neighbor[0], neighbor[1])
        else:
            raise TypeException("Invalid type passed to add_neighbors().")

    def add_neighbor(self, neighbor : 'MapNode', cost : float = None):
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

        self.neighbors[neighbor] = cost

    def update_neighbor_cost(self, neighbor : 'MapNode', cost : float):
        '''
            Update the pathing cost between self and neighbor node, if node exists.
        '''
        if neighbor not in self.neighbors:
            raise MissingNodeException("Cannot update neighbor node's cost. Neighbor not in node.neighbors.")

        self.neighbors[neighbor] = cost

    def closest_neighbor(self, disclude_set : Collection['MapNode'] = []):
        '''
            Return neighbor with lowest cost that is not present in disclude_set.
        '''
        minima = (None, sys.maxsize)
        for key, cost in self.neighbors.items():
            if key in disclude_set:
                continue
            elif cost < minima[1]:
                minima = (key, cost)

        return minima[0]


class Path():
    '''
        Path class
    '''

    def __init__(self, old_path : 'Path' = None, new_node : MapNode = None):
        '''
            Initialize Path
            To use as copy constructor, pass in old_path, with optional new_node. 
        '''
        self.nodes = []
        self.cost = 0
        self.num_nodes = 0
        self.index = 0  # Used for iterating

        if old_path is not None:
            for node in old_path:
                self.add_node(node)
        if new_node is not None:
            self.add_node(new_node)

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
    # Alias this method
    first = start

    def end(self) -> MapNode:
        '''
            Return last node in Path.
        '''
        if len(self.nodes) is 0:
            return None
        else:
            return self.nodes[-1]
    # Alias this method
    last = end

    def add_nodes(self, nodes : List[MapNode]):
        '''
            Add mutliple nodes to end of Path. Calls self.add_node().
            Nodes must be ordered.
        '''
        for node in nodes:
            self.add_node(node)

    def add_node(self, node : MapNode):
        '''
            Add node to end of Path, and update internal data as necessary.
        '''
        if self.start() is None:
            self.num_nodes = 1
            self.nodes.append(node)
        else:
            if not node in self.end().neighbors:
                raise NotANeighborException("Can't add this node to path. Input node is not neighbor of end node.")
            self.num_nodes += 1
            self.cost += self.end().neighbors[node]
            self.nodes.append(node)

    def extend(self, old_path : 'Path'):
        '''
            Extend path with nodes from old_path.
        '''
        if old_path is self:
            raise SamePathException("Cannot add path to itself.")

        for node in old_path:
                self.add_node(node)


class Mapper():
    '''
        Mapper class
        Node names must be unique.
    '''

    def __init__(self, nodes : List[MapNode] = None):
        '''
            Initialize Mapper
        '''
        self.nodes = nodes

    def add_node(self, node : MapNode):
        '''
            Add node to Mapper.
        '''
        if node in self.nodes:
            raise SameNodeException("Attempting to add node that is already present in Mapper object.")
        else:
            self.nodes.append(node)

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
        q = queue.PriorityQueue()
        q.put((0, Path(new_node = source)))
        seen = []

        while not q.empty():
            current_path = q.get()[1]
            current_node = current_path.last()
            if current_node is destination:
                return current_path
            if current_node in seen:
                continue
            seen.append(current_node)

            for next_node in current_node.neighbors:
                if next_node in seen:
                    continue
                new_path = Path(current_path, next_node)
                q.put((1/new_path.cost, new_path, seen))




# ---------------------------------- Helpers ----------------------------------- #

def distance(start : MapNode, end : MapNode) -> float:
    '''
        Find Euclidean distance between MapNodes.
    '''
    return (((start.x - end.x) ** 2) + ((start.y - end.y) ** 2)) ** 0.5