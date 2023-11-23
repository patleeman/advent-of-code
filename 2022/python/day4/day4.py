def part1(assignments):
    fully_covered = 0
    for assignment in assignments:
        elf_a, elf_b = [a.split('-') for a in assignment.split(',')]
        ea0 = int(elf_a[0])
        ea1 = int(elf_a[1])
        eb0 = int(elf_b[0])
        eb1 = int(elf_b[1])
        # a fully covers b
        if ea0 <= eb0 and ea1 >= eb1:
            fully_covered += 1
        elif eb0 <= ea0 and eb1 >= ea1:
            fully_covered += 1

    return fully_covered


def part2(assignments):
    no_overlap = 0
    for assignment in assignments:
        elf_a, elf_b = [a.split('-') for a in assignment.split(',')]
        ea0 = int(elf_a[0])
        ea1 = int(elf_a[1])
        eb0 = int(elf_b[0])
        eb1 = int(elf_b[1])
        # a fully covers b
        if ea1 < eb0 or ea0 > eb1:
            no_overlap += 1
    print(no_overlap)
    return len(assignments) - no_overlap


if __name__ == "__main__":
    with open('data.txt', 'r') as f:
        data = f.read()
    data = data.split('\n')
    del data[-1]
    print(part1(data))
    print(part2(data))
