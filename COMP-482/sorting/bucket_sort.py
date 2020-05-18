import insertion_sort;

# idk, this one bad
def bucket_sort(nums, buckets):
    items = make_buckets(buckets)
    maximum = max(nums)
    for i in range(0, buckets):
        top = (maximum // buckets) * (i + 1)
        bottom = (maximum // buckets) * i
        for num in nums:
            if num >= bottom and num < top:
                items[i].append(num)
        items[i] = insertion_sort.insertion_sort(items[i])
    return [num for sublist in items for num in sublist]


def make_buckets(buckets):
    output = []
    for x in range(0, buckets):
        output.append([])
    return output
