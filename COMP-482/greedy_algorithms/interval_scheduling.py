def schedule(times):
    # sort by end times
    for i in range(1, len(times)):
        j = i
        while j > 0 and times[j][1] < times[j - 1][1]:
            times[j], times[j - 1], j = times[j -1], times[j], j - 1

    output = []
    prev_end_time = -1
    for (start, end) in times:
        if start >= prev_end_time:
            output.append((start, end))
            prev_end_time = end
    return output
