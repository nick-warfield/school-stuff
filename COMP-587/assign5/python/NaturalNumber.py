class Nat:
    pass

class Zero(Nat):
    def is_zero(self) -> bool:
        return True
    def is_one(self) -> bool:
        return False

    def add(self, other: Nat) -> Nat:
        return other
    def subtract(self, other: Nat) -> Nat:
        return self
    def multiply(self, other: Nat) -> Nat:
        return self

    def equals(self, other: Nat) -> bool:
        return other.is_zero()
    def less_than(self, other: Nat) -> bool:
        return not other.is_zero()

    def to_string(self) -> str:
        return "0"

class Successor(Nat):
    def __init__(self, pred: Nat):
        self.pred = pred

    def is_zero(self) -> bool:
        return False
    def is_one(self) -> bool:
        return self.pred.is_zero()

    def add(self, other: Nat) -> Nat:
        output, current = other, self
        while not current.is_zero():
            output, current = Successor(output), current.pred
        return output

    def subtract(self, other: Nat) -> Nat:
        if other.is_zero():
            return self
        else:
            return self.pred.subtract(other.pred)

    def multiply(self, other: Nat) -> Nat:
        if other.is_zero():
            return other
        else:
            output, current = self, other
            while not current.is_one():
                output, current = output.add(self), current.pred
            return output

    def equals(self, other: Nat) -> bool:
        current1, current2 = self, other
        while not current1.is_zero() and not current2.is_zero():
            current1, current2 = current1.pred, current2.pred
        return current1.is_zero() and current2.is_zero()

    def less_than(self, other: Nat) -> bool:
        current = self
        while not current.is_zero() and not other.is_zero():
            current, other = current.pred, other.pred
        return current.is_zero() and not other.is_zero()

    def to_string(self) -> str:
        return "S(" + self.pred.to_string() + ")"

