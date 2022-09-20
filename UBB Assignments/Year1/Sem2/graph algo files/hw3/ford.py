from graph import Graph
import sys


class FordException(Exception):
    pass


def ford_min_cost_walk(graph, vertex1, vertex2):
    if not graph.check_if_vertex(vertex1) or not graph.check_if_vertex(vertex2):
        raise FordException("Invalid input!")

    distance = {}
    predecessor = {}

    if vertex1 == vertex2:
        return 0, [vertex1]

    # initialization for the distance and predecessor dictionaries
    for vertex in graph.get_vertices():
        if vertex == vertex1:
            distance[vertex] = 0
        else:
            distance[vertex] = sys.maxsize
        predecessor[vertex] = -1

    # we relax the edges vertices_number - 1 times
    changed = True
    iteration = 1
    while changed and iteration < graph.get_vertices_number():
        changed = False  # if the distances array doesn't change for the next iteration, it means we have reached the end
        # we parse through the edges and update the distances array
        for edge in graph.get_costs().keys():
            # if the newly calculated distance is smaller than the existing one, we update it
            if distance[edge[1]] > distance[edge[0]] + graph.get_costs()[edge]:
                distance[edge[1]] = distance[edge[0]] + graph.get_costs()[edge]
                predecessor[edge[1]] = edge[0]  # we need to retain for each vertex the 'best' predecessor
                changed = True
        iteration += 1

    # then, we check for negative cost cycle
    # if the iteration number is smaller than the number of vertices then there can't be a negative cost cycle
    # otherwise we will do one more iteration over the edges and if we have a change then it means that there is a
    # negative cost cycle
    if iteration == graph.get_vertices_number():
        changed = False
        for edge in graph.get_costs().keys():
            if distance[edge[1]] > distance[edge[0]] + graph.get_costs()[edge]:
                distance[edge[1]] = distance[edge[0]] + graph.get_costs()[edge]
                predecessor[edge[1]] = edge[0]
                changed = True
        if changed is True:
            return None, []

    # if there is no path between source_vertex and end_vertex
    if distance[vertex2] == sys.maxsize:
        return 0, []

    # we construct the minimum cost reversed_path from source_vertex to destination_vertex
    reversed_path = []
    vertex = vertex2
    reversed_path.append(vertex2)
    while vertex != vertex1:
        reversed_path.append(predecessor[vertex])
        vertex = predecessor[vertex]

    return distance[vertex2], reversed_path[::-1]

