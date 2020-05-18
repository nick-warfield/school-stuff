import copy
import random
import unittest
import TreeOperations
import Node

# ----------automated test case generator---------- #
def gen_tree(max_depth):
    num_of_nodes = 2**(max_depth + 1) - 1
    nums = []
    for _ in range(0, num_of_nodes):
        nums.append(random.randint(-99, 99))
    clone = copy.deepcopy(nums)
    tree = __gen_tree(max_depth, clone)
    nums = nums[len(clone)::]
    nums.reverse()
    return tree, nums

def __gen_tree(max_depth, num):
    if max_depth < 0 or (random.random() > 0.8 and random.random() > 0.8):
        return None
    else:
        return Node.Node(num.pop(), __gen_tree(max_depth - 1, num), __gen_tree(max_depth - 1, num))

class TreeOperationsTest(unittest.TestCase):
    # ----------breadth_first_search tests---------- #
    def test_bfs_empty(self):
        self.assertEqual(
                TreeOperations.breadth_first_search(None),
                [])

    def test_bfs_root(self):
        tree = Node.Node(5, None, None)
        self.assertEqual(
                TreeOperations.breadth_first_search(tree),
                [5])

    def test_bfs_left(self):
        tree = Node.Node(5, 
                Node.Node(4, None, None),
                None)
        self.assertEqual(
                TreeOperations.breadth_first_search(tree),
                [5, 4])

    def test_bfs_right(self):
        tree = Node.Node(5, 
                None,
                Node.Node(3, None, None))
        self.assertEqual(
                TreeOperations.breadth_first_search(tree),
                [5, 3])

    def test_bfs_both(self):
        tree = Node.Node(5, 
                Node.Node(4, None, None),
                Node.Node(3, None, None))
        self.assertEqual(
                TreeOperations.breadth_first_search(tree),
                [5, 4, 3])

    def test_bfs_large(self):
        tree = Node.Node(1,
                Node.Node(2,
                    None,
                    Node.Node(4,
                        Node.Node(7, None, None),
                        None)),
                Node.Node(3,
                    Node.Node(5, None, None),
                    Node.Node(6,
                        None,
                        Node.Node(8, Node.Node(9, None, None), None))))
        self.assertEqual(
                TreeOperations.breadth_first_search(tree),
                [1,2,3,4,5,6,7,8,9])

    # ----------preorder_traversal tests---------- #
    def test_preorder_automatically(self):
        for _ in range(0, 1000):
            t, l = gen_tree(7)
            self.assertEqual(TreeOperations.pre_order(t), l)

    def test_preorder_empty(self):
        self.assertEqual(
                TreeOperations.pre_order(None),
                [])

    def test_preorder_root(self):
        tree = Node.Node(5, None, None)
        self.assertEqual(
                TreeOperations.pre_order(tree),
                [5])

    def test_preorder_left(self):
        tree = Node.Node(5, 
                Node.Node(4, None, None),
                None)
        self.assertEqual(
                TreeOperations.pre_order(tree),
                [5, 4])

    def test_preorder_right(self):
        tree = Node.Node(5, 
                None,
                Node.Node(3, None, None))
        self.assertEqual(
                TreeOperations.pre_order(tree),
                [5, 3])

    def test_preorder_both(self):
        tree = Node.Node(5, 
                Node.Node(4, None, None),
                Node.Node(3, None, None))
        self.assertEqual(
                TreeOperations.pre_order(tree),
                [5, 4, 3])

    # ----------maximum_depth tests---------- #
    def test_max_depth_empty(self):
        self.assertEqual(
                0,
                TreeOperations.maximum_depth(None))

    def test_max_depth_1(self):
        tree = Node.Node(5, None, None)
        self.assertEqual(
                1,
                TreeOperations.maximum_depth(tree))

    def test_max_depth_2_left(self):
        tree = Node.Node(5,
                Node.Node(4, None, None),
                None)
        self.assertEqual(
                2,
                TreeOperations.maximum_depth(tree))

    def test_max_depth_2_right(self):
        tree = Node.Node(5,
                None,
                Node.Node(3, None, None))
        self.assertEqual(
                2,
                TreeOperations.maximum_depth(tree))

    def test_max_depth_2_both(self):
        tree = Node.Node(5,
                Node.Node(4, None, None),
                Node.Node(3, None, None))
        self.assertEqual(
                2,
                TreeOperations.maximum_depth(tree))
