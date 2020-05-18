class Node:
    def __init__(self, value, left, right):
        self.value = value
        self.left = left
        self.right = right

def make_tree(max_depth):
    if max_depth <= 0:
        return None

    if is_leaf():
        return None
    else:
        return Node.Node(random_int(),
                make_tree(max_depth - 1),
                make_tree(max_depth - 1))
