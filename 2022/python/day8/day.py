

def part1(rows):
    seen = []
    for row_idx in range(len(rows)):
        for col_idx in range(len(rows[row_idx])):
            point = (row_idx, col_idx, rows[row_idx][col_idx])
            if point in seen:
                continue

            # Edge Node
            if row_idx == 0 or row_idx == len(rows)-1 or col_idx == 0 or col_idx == len(rows[row_idx])-1:
                seen.append(point)
                continue

            # Get maximum tree size between our point and the edges
            size = rows[row_idx][col_idx]
            max_l = max(rows[row_idx][0:col_idx])
            max_r = max(rows[row_idx][col_idx+1:len(rows[row_idx])])
            vert_slice = [r[col_idx] for r in rows]
            max_t = max(vert_slice[0:row_idx])
            max_b = max(vert_slice[row_idx+1:len(vert_slice)])

            visible = False
            for val in [max_l, max_r, max_t, max_b]:
                if val < size:
                    visible = True

            if visible:
                seen.append(point)

    return len(seen)


def test_part1():
    data = """30373
25512
65332
33549
35390"""
    rows = data.split("\n")
    assert part1(rows) == 21


def part2(rows):
    max_point = (0, 0, 0)
    for row_idx in range(len(rows)):
        for col_idx in range(len(rows[row_idx])):
            size = rows[row_idx][col_idx]

            l_count = 0
            for left_col_idx in range(col_idx - 1, -1, -1):
                l_count += 1
                if rows[row_idx][left_col_idx] >= size:
                    break

            r_count = 0
            for right_col_idx in range(col_idx + 1, len(rows[row_idx])):
                r_count += 1
                if rows[row_idx][right_col_idx] >= size:
                    break

            vert_slice = [r[col_idx] for r in rows]
            t_count = 0
            for top_row_idx in range(row_idx - 1, -1, -1):
                t_count += 1
                if vert_slice[top_row_idx] >= size:
                    break

            b_count = 0
            for bot_row_idx in range(row_idx + 1, len(vert_slice)):
                b_count += 1
                if vert_slice[bot_row_idx] >= size:
                    break

            total_score = l_count * r_count * t_count * b_count
            print('Point: ', row_idx, col_idx, "size: ", size, "Score",
                  l_count, r_count, t_count, b_count, "=", total_score,)

            if total_score > max_point[2]:
                max_point = (row_idx, col_idx, total_score)

    return max_point[2]


def test_part2():
    data = """30373
25512
65332
33549
35390"""
    rows = data.split("\n")
    output = []
    for row in rows:
        output.append([int(c) for c in row])

    assert part2(output) == 8


def get_data():
    with open("data.txt", "r") as f:
        data = f.read()
    rows = data.split("\n")
    del rows[-1]

    output = []
    for row in rows:
        output.append([int(c) for c in row])
    return output


if __name__ == "__main__":
    data = get_data()

    test_part1()
    test_part2()

    print(part1(data))
    print(part2(data))
