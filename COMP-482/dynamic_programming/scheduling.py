# (start_time, end_time, value) = time_slot
def schedule(time_slots):
    time_slots.sort(key=lambda slot: slot[0], reverse=True)
    time_slots.sort(key=lambda slot: slot[1])
    schedule = []
    for (start, end, value) in time_slots:
        if len(schedule) == 0 or start >= schedule[-1][1]:
            schedule.append((start, end, value))
            continue
        benefit = 0
        for index, (s, e, v) in enumerate(reversed(schedule)):
            benefit += v
            if start >= s:
                if value >= benefit:
                    schedule = schedule[:index - 1]
                    schedule.append((start, end, value))
                break
    return schedule
