import sys


class Graph:
    def __init__(self, n):
        """
        :param n: The number of vertices
        """
        self.__vertices_number = n

        # for the implementation of prim's algorithm, we need a matrix type implementation of the graph
        self.__graph_matrix = [[sys.maxsize for i in range(n)] for j in range(n)]

    def is_edge(self, x, y):
        return y in self.__graph_matrix[x]

    def add_edge(self, x, y, cost):
        if not self.is_edge(x, y):
            self.__graph_matrix[x][y] = cost
            self.__graph_matrix[y][x] = cost

    def prims_algorithm(self, starting_node):
        # we keep an array to know if a vertex was selected or not, in order to avoid cycles
        selected = [False] * self.__vertices_number
        edge_number = 0
        selected[starting_node] = True
        print("  Edge  | Weight")
        while edge_number < self.__vertices_number - 1:
            # the algorithm ends when we reach V - 1 nodes in the tree
            minimum = sys.maxsize
            source_node = 0
            destination_node = 0
            for i in range(len(selected)):
                if selected[i]:
                    for j in range(len(selected)):
                        # if the node hasn't been added to the tree yet and there is an edge with the selected node,
                        # we check to see if the edge has the minimum possible cost
                        if not(selected[j]) and self.__graph_matrix[i][j]:
                            if minimum > self.__graph_matrix[i][j]:
                                minimum = self.__graph_matrix[i][j]
                                source_node = i
                                destination_node = j
            print(str(source_node) + " -  " + str(destination_node) + "  |  " + str(self.__graph_matrix[source_node][destination_node]))
            selected[destination_node] = True
            edge_number += 1


class Console:
    def __init__(self):

        file = open("input2.txt", "r")
        number_of_vertices, number_of_edges = map(int, file.readline().split())
        self.g = Graph(int(number_of_vertices))

        for edge in range(number_of_edges):
            x, y, cost = map(int, file.readline().split())
            self.g.add_edge(x, y, cost)

    def run(self):
        while True:
            x = input("Starting node: ")
            try:
                x = int(x)
                self.g.prims_algorithm(x)
                break
            except ValueError:
                print("Please enter an integer!")
            except IndexError:
                print("Please enter a valid node!")


console = Console()
console.run()