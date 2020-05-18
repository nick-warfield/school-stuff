def merge_sort(nums):
    if len(nums) == 1:
        return

    left, right = nums[:len(nums) // 2], nums[len(nums) // 2:]
    merge_sort(left)
    merge_sort(right)

    l = r = 0
    while l < len(left) and r < len(right):
        if left[l] < right[r]:
            nums[l + r], l = left[l], l + 1
        else:
            nums[l + r], r = right[r], r + 1

    while l < len(left):
        nums[l + r], l = left[l], l + 1

    while r < len(right):
        nums[l + r], r = right[r], r + 1

    return nums
