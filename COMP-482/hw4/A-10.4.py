# Whenever a word processor or web browser displays a long passage of text, it
# must be broken up into lines of text that are displayed one on top of the other.
# Determining where to make these breaks is known as the line breaking problem.
# The most natural place to make such breaks are between words. So, suppose you
# are given a sequence, W, of n words, W = (w1, w2, . . . , wn), where each word,
# wi in W, has a given length, li. Also, for the sake of simplicity, let us ignore
# any spaces or punctuation that might come before or after any of these words.
# Suppose further that you are given a line length, L, that is an upper bound on
# the sum of the lengths of words that can fit on a single line. We specify how
# to break W into lines, by a sequence of indices, (i1, i2, . . . , ik), where i1 = 1,
# ik = n, to indicate that we should break W into the lines, wij . . . wij+1−1), for
# j = 1, 2, . . . , k − 1, subject to the constraints that ij < ij+1 and
# 
# In addition, define the penalty for such a set of line breaks to be
# the sum of line_length - row_length
# 
# Describe an efficient greedy algorithm for breaking a sequence of words, W, into
# lines and prove that your method minimizes this penalty. What is the running
# time of your method?

# there isn't an efficient greedy algorithm for this problem unless O(2^n) counts

# Knuth and Pass Line Breaking Algorithm is gucci but not greedy
# list[words] -> list[lines]
def line_breaking(words, line_length):
    lines = []
    return lines

def penalty(lines, line_length):
    penalty = 0
    for line in lines:
        length = 0
        for word in lines:
            length += len(word)
        penalty += (line_length - length) ** 2
    return penalty
