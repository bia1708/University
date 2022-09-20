from graph import VertexException, random_graph, EdgeException, read_file, write_file, Graph
from bfs import lowest_length_path, BFSException
import os


class Console:
    def __init__(self, graph):
        self.__graph = graph
        self.__graph_copies = []

    @staticmethod
    def menu():
        print("=============================\nOPERATIONS\n"
              "1. Generate random graph\n"
              "2. Add a vertex\n"
              "3. Add an edge\n"
              "4. Remove a vertex\n"
              "5. Remove an edge\n"
              "6. Update the cost of an edge\n"
              "7. Print the cost of an edge\n"
              "8. Print the in degree of a vertex\n"
              "9. Print the out degree of a vertex\n"
              "10. Print the number of vertices\n"
              "11. Print the number of edges\n"
              "12. Check if a vertex belongs to the graph\n"
              "13. Check if an edge belongs to the graph\n"
              "14. Print the list of vertices\n"
              "15. Print the list of outbound neighbours of a vertex\n"
              "16. Print the list of inbound neighbours of a vertex\n"
              "17. Print the list of edges\n"
              "18. Read a graph from a file\n"
              "19. Write the graph to a file\n"
              "20. Revert to empty graph\n"
              "21. Make graph copy.\n"
              "22. Get previous version of the graph.\n"
              "23. Get the shortest path between two vertices.\n"
              "24. Get the shortest path length.\n"
              "Press 'x' to exit.\n")

    # 1
    def ui_generate_random_graph(self):
        try:
            n = int(input("Number of vertices: "))
            m = int(input("Number of edges: "))
            if m > n ** 2:
                print("Cannot generate graph!")
            else:
                self.__graph = random_graph(n, m)
                print("Graph generated successfully!")
        except ValueError:
            print("Invalid input!")

    # 2
    def ui_add_a_vertex(self):
        try:
            vertex = int(input("Vertex: "))
            self.__graph.add_vertex(vertex)
            print("Vertex added successfully!")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 3
    def ui_add_edge(self):
        try:
            vertex1 = int(input("Please enter the first vertex: "))
            vertex2 = int(input("Please enter the second vertex: "))
            cost = input("Please enter the cost: ")
            if cost == "":
                self.__graph.add_edge(vertex1, vertex2)
            else:
                self.__graph.add_edge(vertex1, vertex2, int(cost))
            print("Edge added successfully!")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 4
    def ui_remove_a_vertex(self):
        try:
            vertex = int(input("Vertex: "))
            self.__graph.remove_vertex(vertex)
            print("Vertex deleted successfully!")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 5
    def ui_remove_an_edge(self):
        try:
            vertex1 = int(input("Vertex1: "))
            vertex2 = int(input("Vertex2: "))
            self.__graph.remove_edge(vertex1, vertex2)
            print("Edge deleted successfully!")
        except VertexException as ve:
            print(ve)
        except EdgeException as ee:
            print(ee)
        except ValueError:
            print("Invalid input!")

    # 6
    def ui_update_cost(self):
        try:
            vertex1 = int(input("Vertex1: "))
            vertex2 = int(input("Vertex2: "))
            cost = input("Please enter the cost: ")
            self.__graph.set_edge_cost(vertex1, vertex2, cost)
            print("Cost updated successfully!")
        except EdgeException as ee:
            print(ee)
        except ValueError:
            print("Invalid input!")

    # 7
    def ui_print_edge_cost(self):
        try:
            vertex1 = int(input("Vertex1: "))
            vertex2 = int(input("Vertex2: "))
            print(self.__graph.get_edge_cost(vertex1, vertex2))
        except EdgeException as ee:
            print(ee)
        except ValueError:
            print("Invalid input!")

    # 8
    def ui_deg_in(self):
        try:
            vertex = int(input("Vertex: "))
            print(f"The in degree is: {self.__graph.deg_in(vertex)}.")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 9
    def ui_deg_out(self):
        try:
            vertex = int(input("Vertex: "))
            print(f"The out degree is: {self.__graph.deg_out(vertex)}.")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 10
    def ui_print_vertices_number(self):
        print(f"There are {self.__graph.get_vertices_number()} vertices.")

    # 11
    def ui_print_edges_number(self):
        print(f"There are {self.__graph.get_edges_number()} edges.")

    # 12
    def ui_check_if_vertex(self):
        try:
            vertex = int(input("Vertex: "))
            if self.__graph.check_if_vertex(vertex):
                print("The vertex belongs to the graph!")
            else:
                print("The vertex doesn't belong to the graph!")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 13
    def ui_check_if_edge(self):
        try:
            vertex1 = int(input("Vertex1: "))
            vertex2 = int(input("Vertex2: "))
            if self.__graph.check_if_edge(vertex1, vertex2):
                print("The edge belongs to the graph!")
            else:
                print("The edge doesn't belong to the graph!")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 14
    def print_vertices(self):
        print("The vertices are:")
        for vertex in self.__graph.parse_vertices():
            print(f"{vertex}")

    # 15
    def print_outbound_edges(self):
        try:
            vertex = int(input("Vertex: "))
            print("The outbound edges are:")
            for node in self.__graph.parse_dout(vertex):
                print(f"{vertex} - {node}\n")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 16
    def print_inbound_edges(self):
        try:
            vertex = int(input("Vertex: "))
            print("The inbound edges are:")
            for node in self.__graph.parse_din(vertex):
                print(f"{node} - {vertex}\n")
        except ValueError:
            print("Invalid input!")
        except VertexException as ve:
            print(ve)

    # 17
    def print_edges(self):
        print("The edges are:")
        for edge in self.__graph.parse_edges():
            print(f"{edge}\n")

    # 18
    def read_from_file(self):
        file_path = input("Please enter the file path: ")
        if os.path.exists(file_path):
            self.__graph = read_file(file_path)
            print("Graph imported successfully!")
        else:
            print("There is no such file in your directory!")

    # 19
    def write_to_file(self):
        file_path = input("Please enter the file path: ")
        if os.path.exists(file_path):
            write_file(file_path, self.__graph)
            print("File written successfully!")
        else:
            print("There is no such file in your directory!")

    # 20
    def revert_to_empty_graph(self):
        self.__graph = Graph()
        print("Graph updated!")

    # 21
    def make_graph_copy(self):
        self.__graph_copies.append(self.__graph.copy())
        print("Graph copied successfully!")

    # 22
    def get_last_copy(self):
        if len(self.__graph_copies) > 0:
            self.__graph = self.__graph_copies[-1]
            self.__graph_copies.pop(len(self.__graph_copies) - 1)
            print("Graph updated successfully! Copy flushed.")
        else:
            print("There are no graph copies!")

    # 23
    def shortest_path(self):
        try:
            start = int(input("Starting point: "))
            end = int(input("End point: "))
            shortest_path = lowest_length_path(self.__graph, start, end)
            str = ""
            for vertex in shortest_path:
                str += f"{vertex}" + " -> "
            str = str[:len(str) - 4]
            print(str)
        except ValueError:
            print("Invalid input!")
        except BFSException as be:
            print(be)

    # 24
    def shortest_path_length(self):
        try:
            start = int(input("Starting point: "))
            end = int(input("End point: "))
            shortest_path = lowest_length_path(self.__graph, start, end)
            print(len(shortest_path))
        except ValueError:
            print("Invalid input!")
        except BFSException as be:
            print(be)

    def startup(self):
        commands = {
            "1": self.ui_generate_random_graph,
            "2": self.ui_add_a_vertex,
            "3": self.ui_add_edge,
            "4": self.ui_remove_a_vertex,
            "5": self.ui_remove_an_edge,
            "6": self.ui_update_cost,
            "7": self.ui_print_edge_cost,
            "8": self.ui_deg_in,
            "9": self.ui_deg_out,
            "10": self.ui_print_vertices_number,
            "11": self.ui_print_edges_number,
            "12": self.ui_check_if_vertex,
            "13": self.ui_check_if_edge,
            "14": self.print_vertices,
            "15": self.print_outbound_edges,
            "16": self.print_inbound_edges,
            "17": self.print_edges,
            "18": self.read_from_file,
            "19": self.write_to_file,
            "20": self.revert_to_empty_graph,
            "21": self.make_graph_copy,
            "22": self.get_last_copy,
            "23": self.shortest_path,
            "24": self.shortest_path_length
        }

        while True:
            self.menu()
            cmd = input("Command: ")
            if cmd in commands.keys():
                commands[cmd]()
                print("\n")
            elif cmd == 'x':
                break
            else:
                print("Command does not exist!")
