import copy
# items = (name, benefit, weight)
# TODO fix off by one errors
def knapsack(items, max_weight):
    # list of (output_list, benefit) that is indexed by weight
    ben = []
    for _ in range(0, max_weight - 1):
        ben.append(([], 0))
    for (name, benefit, weight) in items:
        for w in reversed(range(weight, max_weight)):
            index = w - weight + 1
            if ben[index][1] + benefit > ben[w][1]:
                output = copy.deepcopy(ben[index][0])
                output.append(name)
                ben[w] = (output, ben[index][1] + benefit)
    ben.sort(key=lambda item: item[1])
    return ben[-1]
