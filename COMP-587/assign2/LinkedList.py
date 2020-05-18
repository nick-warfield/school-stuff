class LinkedList:
    class Node:
        def __init__(self, head, tail):
            self.head = head
            self.tail = tail

    def __init__(self):
        self.root = None

    def add_front(self, element):
        self.root = self.Node(element, self.root)

    def add_back(self, element):
        if self.root is None:
            self.root = self.Node(element, None)
        else:
            current = self.root
            while current.tail is not None:
                current = current.tail
            current.tail = self.Node(element, None)

    def get_element_at(self, index):
        if index < 0:
            return None

        current_pos = 0
        current = self.root
        while current_pos < index and current is not None:
            current, current_pos = current.tail, current_pos + 1

        if current is None:
            return None
        else:
            assert(current_pos == index)
            return current.head

    def length(self):
        size = 0
        current = self.root
        while current is not None:
            size, current = size + 1, current.tail
        return size

    def to_array(self):
        result = []
        current = self.root
        while current is not None:
            result.append(current.head)
            current = current.tail
        return result

    # reverse
    def mystery_operation(self):
        if self.root is None:
            self.root = self.Node(0, None)
            return

        prev = None
        while self.root is not None:
            self.root.tail, self.root, prev = prev, self.root.tail, self.root
        self.root = prev

