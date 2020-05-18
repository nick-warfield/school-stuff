def counting_sort(nums):
    counts, output = [], []
    for x in nums:
        while len(counts) <= x:
            counts.append(0)
        counts[x] += 1

    for i in range(0, len(counts)):
        while counts[i] > 0:
            output.append(i)
            counts[i] -= 1

    return output
