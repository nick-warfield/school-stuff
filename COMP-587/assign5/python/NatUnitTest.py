import unittest
import NaturalNumber
zero = NaturalNumber.Zero
succ = NaturalNumber.Successor

class NatUnitTest(unittest.TestCase):
    def test_to_string_zero(self):
        self.assertEqual("0", zero().to_string())

    def test_to_string_one(self):
        self.assertEqual("S(0)", succ(zero()).to_string())

    def test_equals_same(self):
        self.assertTrue(succ(succ(zero())).equals(succ(succ(zero()))))

    def test_equals_different(self):
        self.assertFalse(succ(zero()).equals(succ(succ(zero()))))

    def test_equals_non_nat(self):
        # using static typing module
        self.assertTrue(True)

    def test_zero_is_zero(self):
        self.assertTrue(zero().is_zero())
        self.assertFalse(zero().is_one())

    def test_one_is_one(self):
        self.assertFalse(succ(zero()).is_zero())
        self.assertTrue(succ(zero()).is_one())

    def test_add(self):
        two = succ(succ(zero()))
        three = succ(succ(succ(zero())))
        five = succ(succ(succ(succ(succ(zero())))))
        self.assertTrue(five.equals(two.add(three)))

    def test_subtract(self):
        one = succ(zero())
        two = succ(succ(zero()))
        three = succ(succ(succ(zero())))
        self.assertTrue(one.equals(three.subtract(two)))

    def test_multiply(self):
        two = succ(succ(zero()))
        three = succ(succ(succ(zero())))
        six = succ(succ(succ(succ(succ(succ(zero()))))))
        self.assertTrue(six.equals(three.multiply(two)))

