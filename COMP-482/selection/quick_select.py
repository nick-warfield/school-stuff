import random

def quick_select(nums, term):
    if len(nums) <= 1:
        return -1

    pivot = random.choice(nums)
    small, big, same = [], [], []

    for x in nums:
        if x < pivot:
            small.append(x)
        elif x > pivot:
            big.append(x)
        else:
            same.append(x)

    print(term, pivot)
    result = quick_select(small, term)
    print(term, pivot, result)
    print()

    if term != 1:
        term -= 1
        return -1
    else:
        return pivot 
    return result
