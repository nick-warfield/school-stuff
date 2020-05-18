def longest_common_subsequence(seq1: str, seq2: str) -> str:
    sub_seq = {}
    for i, letter1 in enumerate(seq1):
        for j, letter2 in enumerate(seq2):
            if letter1 == letter2:
                sub_seq[(i, j)] = sub_seq.get((i - 1, j - 1), "") + letter1
            else:
                sub_seq[(i, j)] = max(
                        sub_seq.get((i - 1, j), ""),
                        sub_seq.get((i, j - 1), ""),
                        key=lambda seq: len(seq))

    return max(sub_seq.items(), key=lambda key_value: len(key_value[1]))[1]
