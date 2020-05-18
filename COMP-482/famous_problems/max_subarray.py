def maximum_subarray(nums):
    sums = []
    for x in nums:
        if len(sums) == 0:
            sums.append(x)
        elif x + sums[-1] >= 0:
            sums.append(sums[-1] + x)
        else:
            sums.append(0)

    prev, end = 0, 0
    for index, s in enumerate(sums):
        if s >= prev:
            end = index
        prev = s

    start = end
    while start > 0 and sums[start] > 0:
        start -= 1

    return nums[start:end + 1]
