def minimize_machines(times):
    times.sort(key=lambda time: time[0])
    machines = []
    for (start, end) in times:
        for m in machines:
            if start >= m[-1][1]:
                m.append((start, end))
                break
        else:   # no break
            machines.append([(start, end)])
    return len(machines)
