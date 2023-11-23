from collections import deque


def part1(root):
    # Traverse tree to find all directories with a total size under 100_000
    directories = []
    target = 100_000
    if root.get_size() <= target:
        directories.append(root)

    q = deque()
    for child in root.children:
        q.append(child)

    while len(q) > 0:
        node = q.popleft()
        if node.is_dir:
            if node.get_size() <= target:
                directories.append(node)

            for child in node.children:
                q.append(child)

    total = 0
    for file in directories:
        total += file.get_size()
    return total


def part2(root):
    total_space = 70_000_000
    needed_space = 30_000_000
    used_space = root.get_size()
    unused_space = total_space - used_space
    shortfall = needed_space - unused_space
    print("Shortfall to make up: ", shortfall)

    min_node = (root, root.get_size() - shortfall)

    q = deque()
    for child in root.children:
        q.append(child)

    while len(q) > 0:
        node = q.popleft()
        if node.is_dir:
            diff = node.get_size() - shortfall
            if diff >= 0 and diff < min_node[1]:
                print(node, node.get_size(), diff)
                min_node = (node, diff)

            for child in node.children:
                q.append(child)

    return min_node[0].get_size()


class File:
    def __init__(self, name, parent, size=0, is_dir=False):
        self.name = name
        self.parent = parent
        self.size = size
        self.is_dir = is_dir

        self.children = []

    def add_child(self, file):
        self.children.append(file)

    def get_child(self, file_name):
        for child in self.children:
            if child.name == file_name:
                return child

        return None

    def get_size(self):
        if not self.is_dir:
            return self.size

        size = 0
        for child in self.children:
            size += child.get_size()
        return size


def build_directory_structure(data):
    root = File(name="/", parent=None, is_dir=True)
    cwd = root
    for command in data:
        parts = command.split(" ")

        if parts[0] == "$" and parts[1] == 'ls':
            continue

        if parts[0] == "$" and parts[1] == 'cd':
            if parts[2] == "..":
                if cwd.parent is None:
                    raise Exception("Already at root, cannot cd ..")
                cwd = cwd.parent
            else:
                if parts[2] == "/":
                    cwd = root
                    continue

                # Check if child has directory name and set it
                child = cwd.get_child(parts[2])
                if child is None:
                    raise Exception("Directory not found")
                cwd = child
            continue

        # We're processing ls output
        if parts[0] == "dir":
            file = File(name=parts[1], parent=cwd, is_dir=True)
        else:
            file = File(name=parts[1], parent=cwd, size=int(parts[0]))

        cwd.add_child(file)

    return root


def test_build_directory_structure():
    data = [
        "$ cd /",
        "$ ls",
        "dir test1",
        "dir test2",
        "dir test3",
        "$ cd test1",
        "$ ls",
        "100 hello.wd",
        "100 yomomma.fat",
        "$ cd ..",
        "$ cd test2",
        "$ ls",
        "$ cd ..",
        "$ cd test3",
        "$ ls",
        "100 hello.md",
    ]
    root = build_directory_structure(data)
    assert root.get_size() == 300


def get_data():
    with open("data.txt", "r") as f:
        data = f.read()
    data = data.split("\n")
    del data[-1]
    return data


if __name__ == "__main__":
    test_build_directory_structure()

    data = get_data()
    tree = build_directory_structure(data)
    print('Total Tree Size: ', tree.get_size())

    print("Part 1: ", part1(tree))
    print("Part 2: ", part2(tree))
