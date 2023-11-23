

def part1(data):
    pass


def test_part1():
    assert True


def part2(data):
    pass


def test_part2():
    assert True


def get_data():
    with open("data.txt", "r") as f:
        data = f.read()
    data = data.split("\n")
    return data


if __name__ == "__main__":
    data = get_data()

    test_part1()
    test_part2()

    print("Part 1 output: ", part1(data))
    print("Part 1 output: ", part2(data))
