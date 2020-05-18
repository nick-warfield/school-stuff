# There is a sorting algorithm, “Stooge-sort,” which is named after the comedy
# team, “The Three Stooges.” if the input size, n, is 1 or 2, then the algorithm sorts
# the input immediately. Otherwise, it recursively sorts the first 2n/3 elements,
# then the last 2n/3 elements, and then the first 2n/3 elements again. The details
# are shown in Algorithm 11.5. Show that Stooge-sort is correct and characterize
# the running time, T(n), for Stooge-sort, using a recurrence equation, and use the
# master theorem to dermine an asymptotic bound for T(n).

# Algorithm StoogeSort(A, i, j):
# Input: An array, A, and two indices, i and j, such that 1 ≤ i ≤ j ≤ n
# Output: Subarray, A[i..j], sorted in nondecreasing order
#     n ← j − i + 1 // The size of the subarray we are sorting
#     if n = 2 then
#         if A[i] > A[j] then
#             Swap A[i] and A[j]
#     else if n > 2 then
#         m ← ⌊n/3⌋
#         StoogeSort(A, i, j − m) // Sort the first part
#         StoogeSort(A, i + m, j) // Sort the last part
#         StoogeSort(A, i, j − m) // Sort the first part again
#     return A
