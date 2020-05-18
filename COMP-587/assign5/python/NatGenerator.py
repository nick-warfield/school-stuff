import NaturalNumber
import random

zero = NaturalNumber.Zero
succ = NaturalNumber.Successor

class NatGenerator:
    def __init__(self, minimum, maximum):
        self.min = max(0, minimum)
        self.max = max(self.min, maximum)

    def next(self):
        size = random.randint(self.min, self.max)
        output = zero()
        for _ in range(0, size):
            output = succ(output)
        return output
