from typing import List
import queue
import Node

# A breadth-first search over a tree, returning the items in the tree.
def breadth_first_search(tree_root: Node.Node) -> List:
    if tree_root is None:
        return []
    output = []
    q = queue.Queue()
    q.put(tree_root)
    bfs_helper(q, output)
    return output

def bfs_helper(q: queue.Queue, output: List) -> None:
    if q.empty():
        return

    node = q.get()
    output.append(node.item)
    if node.left is not None:
        q.put(node.left)
    if node.right is not None:
        q.put(node.right)
    bfs_helper(q, output)
    while not q.empty():
        output.append(q.get().item)

# A pre-order traversal over a tree, returning the items in the tree.
def pre_order(tree_root: Node.Node) -> List:
    output = []
    pre_order_helper(tree_root, output)
    return output

def pre_order_helper(node: Node.Node, output: List) -> None:
    if node is None:
        return
    output.append(node.item)
    pre_order_helper(node.left, output)
    pre_order_helper(node.right, output)

# A calculation of the maximum depth of a given tree.
def maximum_depth(node: Node.Node) -> int:
    if node is None:
        return 0
    else:
        return 1 + max(
                maximum_depth(node.left),
                maximum_depth(node.right))

