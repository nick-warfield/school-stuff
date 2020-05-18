def factional_knapsack(items, max_weight):
    items.sort(reverse=True, key=lambda item: (item[1] / item[2]))
    output = []
    for (name, _, weight) in items:
        if max_weight == 0:
            continue
        added = min(weight, max_weight)
        output.append((name, added))
        max_weight -= added
    return output
