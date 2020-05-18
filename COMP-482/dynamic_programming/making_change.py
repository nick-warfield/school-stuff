import copy
# change to make, set of coins
def make_change(coins, amount):
    change = {}
    for i in range(1, amount + 1):
        for c in coins:
            if i - c < 0: continue
            prev, curr = change.get(i - c, []), change.get(i, [])
            if curr == [] or len(prev) + 1 < len(curr):
                change[i] = copy.deepcopy(prev)
                change[i].append(c)
    return change[amount]

