from graph import Graph


class BFSException(Exception):
    pass


def lowest_length_path(graph, start, end):
    '''
    find the lowest length path between start and end, in graph, using a forward BFS from the starting current_vertex
    if start or end are not valid vertices in the graph, we raise ValueError
    if there is no path between start and end, we raise ValueError
    :param graph: the given graph
    :param start: the starting current_vertex
    :param end: the ending current_vertex
    :return: returns the path from start to end if it exists, otherwise it raises ValueError
    '''

    # if the start or end are not valid, we raise BFSException
    if not graph.check_if_vertex(start) or not graph.check_if_vertex(end):
        raise BFSException("Invalid input!")

    if start == end:
        return []  # if start = end, the path is empty

    visited = []  # list containing visited nodes
    queue = [[start]]  # list containing all the possible paths in a queue

    # we loop through all the paths in queue
    while queue:
        path = queue.pop(0)
        current_vertex = path[-1]

        # we check to see if the current_vertex has been visited
        if current_vertex not in visited:
            # if it isn't, we get a list of its outbound neighbours
            neighbours = graph.get_outbound_neighbours(current_vertex)

            # we parse through the outbound neighbours of the current_vertex
            for outbound in neighbours:
                # we make a new path for each outbound vertex and add it to the queue
                new_path = list(path)
                new_path.append(outbound)
                queue.append(new_path)

                # if we reached the end vertex we return the current path
                if outbound == end:
                    return new_path
            # we add the current_vertex to the list of visited vertices
            visited.append(current_vertex)

    # if a path hasn't been found, it means there isn't one
    raise BFSException("There isn't a path between the two vertices!")
