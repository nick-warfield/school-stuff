import unittest
import LinkedList

class LinkedListTest(unittest.TestCase):
    def test_add_front_1(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(1)
        self.assertEqual([1], linked_list.to_array())

    def test_add_front_2(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(1)
        linked_list.add_front(7)
        self.assertEqual([7, 1], linked_list.to_array())

    def test_add_back_1(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_back(1)
        self.assertEqual([1], linked_list.to_array())

    def test_add_back_2(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_back(1)
        linked_list.add_back(7)
        self.assertEqual([1, 7], linked_list.to_array())

    def test_get_element_at_empty(self):
        linked_list = LinkedList.LinkedList()
        self.assertEqual(None, linked_list.get_element_at(0))

    def test_get_element_at_front(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(4)
        linked_list.add_front(3)
        linked_list.add_front(2)
        linked_list.add_front(1)
        linked_list.add_front(0)
        self.assertEqual(0, linked_list.get_element_at(0))

    def test_get_element_at_back(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(4)
        linked_list.add_front(3)
        linked_list.add_front(2)
        linked_list.add_front(1)
        linked_list.add_front(0)
        self.assertEqual(4, linked_list.get_element_at(4))

    def test_get_element_at_middle(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(4)
        linked_list.add_front(3)
        linked_list.add_front(2)
        linked_list.add_front(1)
        linked_list.add_front(0)
        self.assertEqual(2, linked_list.get_element_at(2))

    def test_length_empty(self):
        linked_list = LinkedList.LinkedList()
        self.assertEqual(0, linked_list.length())

    def test_length_1(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(0)
        self.assertEqual(1, linked_list.length())

    def test_length_long(self):
        linked_list = LinkedList.LinkedList()
        for _ in range(0, 10000):
            linked_list.add_front(0)
        self.assertEqual(10000, linked_list.length())

    def test_to_array_empty(self):
        linked_list = LinkedList.LinkedList()
        self.assertEqual([], linked_list.to_array())
    
    def test_to_array_1(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(0)
        self.assertEqual([0], linked_list.to_array())
    
    def test_to_array_long(self):
        linked_list = LinkedList.LinkedList()
        arr = []
        for x in range(0, 10000):
            arr.append(9999 - x)
            linked_list.add_front(x)
        self.assertEqual(arr, linked_list.to_array())
    
    def test_mystery_length_0(self):
        linked_list = LinkedList.LinkedList()
        linked_list.mystery_operation()
        self.assertEqual([0], linked_list.to_array())

    def test_mystery_length_1(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(1)
        linked_list.mystery_operation()
        self.assertEqual([1], linked_list.to_array())

    def test_mystery_length_2(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(2)
        linked_list.add_front(1)
        linked_list.mystery_operation()
        self.assertEqual([2, 1], linked_list.to_array())

    def test_mystery_length_3(self):
        linked_list = LinkedList.LinkedList()
        linked_list.add_front(3)
        linked_list.add_front(2)
        linked_list.add_front(1)
        linked_list.mystery_operation()
        self.assertEqual([3, 2, 1], linked_list.to_array())

unittest.main()
