import random

def quick_sort(nums):
    if len(nums) <= 1:
        return

    pivot = random.choice(nums)
    small, big, same = [], [], []

    for x in nums:
        if x < pivot:
            small.append(x)
        elif x > pivot:
            big.append(x)
        else:
            same.append(x)

    quick_sort(small)
    quick_sort(big)
    return small + same + big
