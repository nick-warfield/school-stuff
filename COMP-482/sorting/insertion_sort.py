def insertion_sort(nums):
    for i in range(1, len(nums)):
        j = i
        while j > 0 and nums[j] < nums[j - 1]:
            nums[j], nums[j - 1], j = nums[j -1], nums[j], j - 1
    return nums
