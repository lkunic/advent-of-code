import parse

class Node:
    def __init__(self, index, neighbors):
        self.index = index
        self.neighbors = neighbors
        self.visited = False

def getReachable(nodes, node):
    if node.visited:
        return []

    node.visited = True

    result = [node.index]

    for neighbor in node.neighbors:
        result.extend(getReachable(nodes, nodes[int(neighbor)]))

    return result

def result():
    nodes = {}

    with open('in12.txt', 'r') as file:
        line = file.readline()
        while (line):
            parsed = parse.parse("{} <-> {}", line.strip())
            nodes[int(parsed[0])] = Node(int(parsed[0]), parsed[1].split(', '))
            line = file.readline()

    count = 0
    total = getReachable(nodes, nodes[0])
    while len(total) < len(nodes):
        total = sorted(total)
        for i, node in zip(range(len(total)), total):
            if i != node:
                total.extend(getReachable(nodes, nodes[i]))
                count += 1
                break

    return count

if __name__ == "__main__":
    print(result())
