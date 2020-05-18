# When data is transmitted across a noisy channel, information can be lost during
# the transmission. For example, a message that is sent through a noisy channel as
#
# “WHO PARKED ON HARRY POTTER’S SPOT?′′
#
# could be received as the message,
#
# “HOP ON POP′′
#
# That is, some characters could be lost during the transmission, so that only a
# selected portion of the original message is received. We can model this phe-
# nomenon using character strings, where, given a string X = x1x2 . . . xn, we say
# that a string Y = y1y2 . . . ym is a subsequence of X if there are a set of indices
# {i1, i2, . . . , ik}, such that y1 = xi1, y2 = xi2, . . ., yk = xik, and ij < ij+1, for
# j = 1, 2, . . . , k − 1. In a case of transmission along a noisy channel, it could be
# useful to know if our transcription of a received message is indeed a subsequence
# of the message sent. Therefore, describe an O(n + m)-time method for deter-
# mining if a given string, Y , of length m is a subsequence of a given string, X, of
# length n.

def is_substring(string, sub_string):
    i = 0
    for c in sub_string:
        while True:
            i += 1
            if string[i - 1] == c:
                continue
            elif i == len(string):
                return False
    return True
