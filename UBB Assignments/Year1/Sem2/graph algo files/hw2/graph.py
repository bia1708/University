from copy import deepcopy
from random import randrange


class VertexException(Exception):
    pass


class EdgeException(Exception):
    pass


class Graph:
    def __init__(self, nr_of_vertices=0, nr_of_edges=0):
        self.__nr_of_edges = nr_of_edges
        self.__nr_of_vertices = nr_of_vertices
        self.__din = {}  # dict in
        self.__dout = {}  # dict out
        self.__vertices = []
        self.__costs = {}  # maps edges to costs

        for i in range(self.__nr_of_vertices):
            self.add_vertex(i)

        # for i in range(self.__nr_of_edges):
        #     vertex1 = randint(0, self.__nr_of_vertices)
        #     vertex2 = randint(0, self.__nr_of_vertices)
        #     while self.check_if_edge(vertex1, vertex2) is True:
        #         vertex1 = randint(0, self.__nr_of_vertices)
        #         vertex2 = randint(0, self.__nr_of_vertices)
        #     self.add_edge(vertex1, vertex2)

    # ============== VERTICES OPERATIONS =============

    def parse_vertices(self):
        for vertex in self.__vertices:
            yield vertex

    def parse_dout(self, vertex):
        """
        Returns an iterator to the set of (outbound) neighbours of a vertex.
        """
        if not self.check_if_vertex(vertex):
            raise VertexException("Invalid vertex.")
        for neighbour in self.__dout[vertex]:
            yield neighbour

    def get_outbound_neighbours(self, vertex):
        return self.__dout[vertex]

    def parse_din(self, vertex):
        """
        Returns an iterator to the set of (inbound) neighbours of a vertex.
        """
        if not self.check_if_vertex(vertex):
            raise VertexException("Invalid vertex.")
        for neighbour in self.__din[vertex]:
            yield neighbour

    def get_vertices_number(self):
        return len(self.__vertices)

    def check_if_vertex(self, vertex):
        if vertex in self.__vertices:
            return True
        return False

    def add_vertex(self, vertex):
        if self.check_if_vertex(vertex) is True:
            raise VertexException("This vertex already exists!")

        self.__vertices.append(vertex)
        self.__din[vertex] = []
        self.__dout[vertex] = []

    def remove_vertex(self, vertex):
        if not self.check_if_vertex(vertex):
            raise VertexException("This vertex doesn't exist!")

        # first we delete all of the outbound edges containing the vertex
        remove_list = []
        for end_node in self.__dout[vertex]:
            remove_list.append(end_node)
        for end_node in remove_list:
            self.remove_edge(vertex, end_node)

        # then we delete aa of the inbound edges containing the vertex
        remove_list = []
        for node in self.__din[vertex]:
            remove_list.append(node)
        for node in remove_list:
            self.remove_edge(node, vertex)

        # now we need to remove the vertex from the din and dout dictionaries and from the list of vertices
        del self.__dout[vertex]
        del self.__din[vertex]
        self.__vertices.remove(vertex)

    def deg_in(self, vertex):
        if self.check_if_vertex(vertex) is False:
            raise VertexException("This vertex doesn't exist!")

        return len(self.__din[vertex])

    def deg_out(self, vertex):
        if self.check_if_vertex(vertex) is False:
            raise VertexException("This vertex doesn't exist!")

        return len(self.__dout[vertex])

    # ===================== EDGES OPERATIONS ========================

    def parse_edges(self):
        """
        Returns an iterator to the set of edges.
        """
        for key, value in self.__costs.items():
            yield key[0], key[1], value

    def get_edges_number(self):
        return self.__nr_of_edges

    def set_edges_number(self, value):
        self.__nr_of_edges = value

    def check_if_edge(self, vertex1, vertex2):
        if self.check_if_vertex(vertex1) is False or self.check_if_vertex(vertex2) is False:
            raise VertexException("Please enter another pair of vertices!")

        if vertex2 in self.__dout[vertex1]:
            return True
        return False

    def add_edge(self, vertex1, vertex2, edge_cost=0):
        if self.check_if_edge(vertex1, vertex2) is True:
            raise EdgeException("This edge already exists")

        if self.check_if_vertex(vertex1) is False or self.check_if_vertex(vertex2) is False:
            raise VertexException("Please enter another pair of vertices!")

        self.__dout[vertex1].append(vertex2)
        self.__din[vertex2].append(vertex1)
        self.__costs[(vertex1, vertex2)] = edge_cost

    def remove_edge(self, vertex1, vertex2):
        """
        Removes an edge from the graph.
        """
        if not self.check_if_edge(vertex1, vertex2):
            raise EdgeException("This edge doesn't exist!")
        del self.__costs[(vertex1, vertex2)]
        self.__dout[vertex1].remove(vertex2)
        self.__din[vertex2].remove(vertex1)

    def get_edge_cost(self, vertex1, vertex2):
        """
        Returns the cost of an edge if it exists.
        """
        if (vertex1, vertex2) not in self.__costs:
            raise EdgeException("This edge doesn't exist!")
        return self.__costs[(vertex1, vertex2)]

    def set_edge_cost(self, vertex1, vertex2, new_cost):
        """
        Sets the cost of an edge in the graph if it exists.
        """
        if (vertex1, vertex2) not in self.__costs:
            raise EdgeException("The specified edge does not exist.")
        self.__costs[(vertex1, vertex2)] = new_cost

    def copy(self):
        """
        Returns a deepcopy of the graph.
        """
        return deepcopy(self)


def read_file(file_path):
    counter = 0
    with open(file_path, "r") as file:
        n, m = file.readline().split()
        graph = Graph(int(n))
        print("Graph generated...")
        counter = 0
        for line in range(int(m)):
            vertex1, vertex2, edge_cost = file.readline().split()
            counter += 1
            if counter % 10000 == 0:
                print(f"{counter} lines processed...\n")
            graph.add_edge(int(vertex1), int(vertex2), int(edge_cost))
    graph.set_edges_number(m)
    file.close()
    return graph


def write_file(file_path, graph):
    with open(file_path, "w") as file:
        file.write(f"{graph.get_vertices_number()} {graph.get_edges_number()}\n")
        for node in graph.parse_vertices():
            for neighbour in graph.parse_dout(node):
                file.write(f"{node} {neighbour} {graph.get_edge_cost(node, neighbour)}\n")
    file.close()


def random_graph(vertices_number, edges_number):
    graph = Graph()
    for i in range(vertices_number):
        graph.add_vertex(i)
    for j in range(edges_number):
        vertex1 = randrange(vertices_number)
        vertex2 = randrange(vertices_number)
        while graph.check_if_edge(vertex1, vertex2):
            try:
                vertex1 = randrange(vertices_number)
                vertex2 = randrange(vertices_number)
            except EdgeException:
                pass
        graph.add_edge(vertex1, vertex2, randrange(0, 100, 10))
    graph.set_edges_number(edges_number)
    return graph

