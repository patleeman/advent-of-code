
def calculate_max_calories(data):
    calories = data.split('\n')
    elf_totals = []
    elf_tally = 0
    for calorie in calories:
        if calorie == "":
            elf_totals.append(elf_tally)
            elf_tally = 0
            continue

        elf_tally += int(calorie)

    return sum(sorted(elf_totals)[-3:])

if __name__ == "__main__":
    with open('data.txt', 'r') as f:
        data = f.read()

    print(calculate_max_calories(data))
