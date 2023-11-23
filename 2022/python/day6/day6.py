from collections import Counter


def part1(data):
    counter = Counter()

    for i in range(len(data)):
        # print(i, data[i], counter)
        counter[data[i]] += 1

        if counter.total() > 4:
            remove_char = data[i-4]
            counter[remove_char] -= 1

        if counter.total() == 4 and len(set(counter.elements())) == 4:
            # print('final: ', i+1, ' keys: ',
            #       counter.keys(), counter, data[:i+1], set(counter.elements()))
            return i + 1


def test_part1():
    assert part1("asdafdsdf") == 5
    assert part1("thequickbrownfox") == 4
    assert part1('aaaaaaaaaabcd') == 13
    assert part1('bvwbjplbgvbhsrlpgdmjqwftvncz') == 5
    assert part1('nppdvjthqldpwncqszvftbrmjlhg') == 6
    assert part1('nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg') == 10
    assert part1('zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw') == 11


def part2(data):
    counter = Counter()

    for i in range(len(data)):
        # print(i, data[i], counter)
        counter[data[i]] += 1

        if counter.total() > 14:
            remove_char = data[i-14]
            counter[remove_char] -= 1

        if counter.total() == 14 and len(set(counter.elements())) == 14:
            # print('final: ', i+1, ' keys: ',
            #       counter.keys(), counter, data[:i+1], set(counter.elements()))
            return i + 1


def test_part2():
    assert part2('mjqjpqmgbljsphdztnvjfqwrcgsmlb') == 19
    assert part2('bvwbjplbgvbhsrlpgdmjqwftvncz') == 23
    assert part2('nppdvjthqldpwncqszvftbrmjlhg') == 23
    assert part2('nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg') == 29
    assert part2('zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw') == 26


def get_data():
    with open("data.txt", "r") as f:
        data = f.read()
    return data


if __name__ == "__main__":
    data = get_data()

    # test_part1()
    test_part2()

    # print(part1(data))
    print(part2(data))
