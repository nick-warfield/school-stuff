# In the art gallery guarding problem we are given a line L that represents a long
# hallway in an art gallery. We are also given a set X = {x0, x1, . . . , xn−1} of
# real numbers that specify the positions of paintings in this hallway. Suppose that
# a single guard can protect all the paintings within distance at most 1 of his or her
# position (on both sides). Design an algorithm for finding a placement of guards
# that uses the minimum number of guards to guard all the paintings with positions
# in X.

# scan through the line left to right,
# everytime an unguarded painting is found, place a guard to its right

def guard_paintings(hall):
    guards = []
    for x, painting in enumerate(hall):
        if guards == []:
            guards.append(x + 1)
        elif guards[-1] != x - 1 and guards[-1] != x:
            guards.append(x + 1)
    return guards
