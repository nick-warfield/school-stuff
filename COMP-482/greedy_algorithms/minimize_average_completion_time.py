# times (int: start time, int: end time)
# tasks (int: processing time)
# all tasks must be scheduled non-premptively
#   (task must be completed once started)
# one machine
# minimize average completion time

# sort tasks by processing time, shortest to smallest
# calculate task scheduling
# then return sorted list

from typing import List

# List[processing_times] -> List[(start_time, end_time)]
def min_complete_time(tasks: List[int]):
    t = sorted(tasks)
    next_start, times = 0, []
    for processing_time in t:
        times.append((next_start, next_start + processing_time))
        next_start += processing_time

    return times
