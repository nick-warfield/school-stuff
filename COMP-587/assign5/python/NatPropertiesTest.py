import unittest
import NaturalNumber
import NatGenerator

gen = NatGenerator.NatGenerator
succ = NaturalNumber.Successor
zero = NaturalNumber.Zero

class NatPropertiesTest(unittest.TestCase):
    # a == a
    def test_number_equals_self(self):
        num = gen(0, 10).next()
        self.assertTrue(num.equals(num))

    # a + b == b + a
    def test_commutative_property(self):
        a, b = gen(0, 10).next(), gen(0, 10).next()
        self.assertTrue(a.add(b).equals(b.add(a)))

    # a + 0 = a
    def test_identity_property_addition(self):
        a = gen(0, 10).next()
        self.assertTrue(a.add(zero()).equals(a))

    # a * 1 = a
    def test_identity_property_multiplication(self):
        a = gen(0, 10).next()
        self.assertTrue(a.multiply(succ(zero())).equals(a))
