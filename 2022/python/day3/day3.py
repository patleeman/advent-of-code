
def part1(backpacks):
    total = 0
    for backpack in backpacks:
        midway = int(len(backpack) / 2)
        comp1 = backpack[0:midway]
        comp2 = backpack[midway:]

        common_items = set() 
        for item in comp1:
            if item in comp2:
                common_items.add(item)

        priorities = [get_priority(item) for item in common_items]
        total += sum(priorities)
    
    return total

def part2(backpacks):
    total = 0
    temp_groups = []
    for backpack in backpacks:     
        temp_groups.append(backpack)

        if len(temp_groups) == 3:
            for item in temp_groups[0]:
                if item in temp_groups[1] and item in temp_groups[2]:
                    priority = get_priority(item)
                    print("badge found: ", item, priority)
                    total += priority
                    break

            temp_groups = []

    return total 


lookup = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
def get_priority(char):
    if len(char) > 1:
        return None
    return lookup.index(char) + 1 



if __name__ == "__main__":
    with open("data.txt", "r") as f:
        data = f.read()
    data = data.split("\n")

    test_data = ["abcabc"]
    test = part1(test_data)
    assert test == 6
    print(test_data, test)

    print(part1(data))
    print(part2(data))
