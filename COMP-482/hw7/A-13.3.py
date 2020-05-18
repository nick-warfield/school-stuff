# write an algorithm to find the maximal independent set of a graph
# that is a subset of a graph with no edges, and in which adding another verticy would add an edge

# start by picking the verticy with the fewest edges, then remove all verticies it connects to, repeat
# O(v + e)

def maximal_independent_set(graph):
    return graph
