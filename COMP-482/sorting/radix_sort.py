def radix_sort(nums, digits):
    for i in range(0, digits):
        items = [[], [], [], [], [], [], [], [], [], []]
        for x in nums:
            items[(x // 10**i) % 10].append(x) 
        nums = [num for sublist in items for num in sublist]

    return nums
