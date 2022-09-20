class GraphException(Exception):
    pass


class Graph:
    def __init__(self, n):
        """
        Constructor for the Graph class
        Creates an empty graph with n vertices
        Precondition: n must be a positive integer
        :param n: Number of vertices to have as default
        raises GraphException if n is not a positive number or 0 (n>0)
        """
        if n < 0:
            raise GraphException("Invalid number of vertices")

        self._dictEdges = {}
        self._dictCost = {}

        for i in range(0, n):
            self._dictEdges[i] = []

    def get_number_of_vertices(self):
        """
        Gets the number of vertices
        :return: the number of vertices
        """
        return len(self._dictEdges.keys())

    def parse_vertices(self):
        """
        Returns an iterator for the vertices
        :return: an iterator for the vertices
        """
        return iter(self._dictEdges.keys())

    def edge_exists(self, x, y):
        """
        Checks if an edge exists
        Precondition: x and y need to be valid vertices
        :param x: The source
        :param y: The target
        :return: True if it exists, false otherwise
        raises GraphException if x or y is an invalid vertex
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Invalid vertex")

        if y in self._dictEdges[x]:
            return True
        else:
            return False

    def get_in_degree(self, x):
        """
        Gets the in degree of vertex x
        Precondition: x must be a valid vertex
        :param x: The vertex
        :return: An integer representing the in degree of the vertex
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Invalid vertex")

        return len(self._dictEdges[x])

    def get_out_degree(self, x):
        """
        Gets the out degree of vertex x
        Precondition: x must be a valid vertex
        :param x: The vertex
        :return: An integer representing the out degree of the vertex
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Invalid vertex")

        return len(self._dictEdges[x])

    def parse_outbound_edges(self, x):
        """
        Creates an iterator that goes trough the targets of the outbound edges having the source x
        Precondition: x must be a valid vertex
        :param x: The x vertex
        :return: An iterator for the outbound edges with x as a source
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Invalid vertex")

        return iter(self._dictEdges[x])

    def parse_inbound_edges(self, x):
        """
        Creates an iterator that goes trough the sources of the inbound edges having the target x
        Precondition: x must be a valid vertex
        :param x: The x vertex
        :return: An iterator for the inbound edges with x as a target
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Invalid vertex")

        return iter(self._dictEdges[x])

    def get_cost_of_edge(self, x, y):
        """
        Gets the cost of an edge
        Precondition: x and y must be valid vertices and (x, y) a valid edge
        :param x: Source
        :param y: Target
        :return: An integer representing the cost of an edge
        raises GraphException for x, y no valid vertices or (x, y) not a valid edge
        """
        raise GraphException("There are no costs in this undirected graph")

    def modify_cost_of_edge(self, x, y):
        """
        Modifies the cost of an edge
        Precondition: x and y must be valid vertices and (x, y) a valid edge
        :param x: Source
        :param y: Target
        :param c: New cost
        :return: -
        raises GraphException for x, y no valid vertices or (x, y) not a valid edge
        """
        raise GraphException("There are no costs in this undirected graph")

    def add_edge(self, x, y):
        """
        Adds a new edge
        Precondition: valid x, y vertices and the edge shouldn't exist already
        :param x: Source
        :param y: Target
        :return: -
        raises GraphException if the vertices are invalid or the edge already exists
        """
        if y in self._dictEdges[x]:
            raise GraphException("Edge already exists!")

        if x not in self._dictEdges.keys() or y not in self._dictEdges.keys():
            raise GraphException("Invalid vertices!")

        self._dictEdges[x].append(y)
        self._dictEdges[y].append(x)

    def remove_edge(self, x, y):
        """
        Removes an edge
        Precondition: valid x, y vertices and the edge should exist
        :param x: Source
        :param y: Target
        :return: -
        raises GraphException if the vertices are incorrect or the edge doesnt exist
        """
        if x not in self._dictEdges.keys() or y not in self._dictEdges.keys():
            raise GraphException("Invalid vertices!")

        if y not in self._dictEdges[x]:
            raise GraphException("Edge doesnt exist!")

        self._dictEdges[x].remove(y)
        self._dictEdges[y].remove(x)

    def add_vertex(self, x):
        """
        Adds a new vertex
        Precondition: the vertex shouldn't already exist
        :param x: The vertex to be added
        :return: -
        raises GraphException if the vertex already exists or if it s a negative one
        """
        if x in self._dictEdges.keys():
            raise GraphException("Vertex already exists!")

        if x < 0:
            raise GraphException("The vertex shouldn't be a negative number")

        self._dictEdges[x] = []

    def remove_vertex(self, x):
        """
        Removes the vertex x
        Precondition: x must be a valid vertex
        :param x: A vertex
        :return: -
        raises GraphException if the vertex doesn't exist
        """
        if x not in self._dictEdges.keys():
            raise GraphException("Vertex doesn't exist")

        for v in self._dictEdges[x]:
            self._dictEdges[v].remove(x)

        del self._dictEdges[x]

    def hamil_recursive(self, path, pos):

        # checking if we have a solution
        if pos == self.get_number_of_vertices():
            if self.edge_exists(path[pos - 1], path[0]):
                return True
            else:
                return False

        # going through all the vertices that have an edge with the previous vertex
        # seeing which vertex can be put on the current pos and going forward with it
        for ver in self.parse_outbound_edges(path[pos - 1]):
            if self.is_okay(path, pos, ver):
                path[pos] = ver

                if self.hamil_recursive(path, pos + 1):
                    return True

                path[pos] = -1
        return False

    def to_string(self):
        """
        Constructs and returns the string representation of the graph
        :return: string representation of the graph
        """
        return "Edges: " + str(self._dictEdges) + "\n"

    def is_okay(self, path, pos, v):
        # checks if the vertex v can be put on the position pos in the given path
        # check that there s a path between the last vertex and the given vertex
        if not self.edge_exists(path[pos - 1], v):
            return False

        # check that the vertex doesn't already exist in the path
        for ver in path:
            if v == ver:
                return False

        return True

    def check_hamiltonian(self):
        path = [-1] * (self.get_number_of_vertices() + 1)

        path[0] = list(self._dictEdges.keys())[0]
        path[self.get_number_of_vertices()] = list(self._dictEdges.keys())[0]

        if not self.hamil_recursive(path, 1):
            raise GraphException("There is no hamiltonian cycle in the graph.")

        return path
