import parse

class Node:
    def __init__(self, name, weight, children):
        self.name = name
        self.parent = None
        self.weight = weight
        self.children = children

def getRoot(nodes, node):
    if node.parent is None:
        return node.name

    return getRoot(nodes, node.parent)

def findImbalance(nodes, node):
    childWeights = []
    weights = []
    for child in node.children:
        childWeights.append(nodes[child].weight)
        result = findImbalance(nodes, nodes[child])
        if (result):
            return result
        weights.append(nodes[child].weight)
        node.weight += nodes[child].weight

    if (len(set(weights)) > 1):
        a = []
        wset = list(set(weights))
        for weight in wset:
            a.append(sum([1 for i in weights if i == weight]))

        diff = [wset[i] for i in range(len(a)) if a[i] != 1][0] - [wset[i] for i in range(len(a)) if a[i] == 1][0]
        offWeight = [wset[i] for i in range(len(a)) if a[i] == 1][0]
        index = [w for w in range(len(weights)) if weights[w] == offWeight][0]

        return childWeights[index] + diff

def result():
    nodes = {}
    
    with open('in7.txt', 'r') as file:
        line = file.readline()
        while (line):
            parsed = parse.parse("{} ({}) -> {}", line.strip())
            if (not parsed):
                parsed = parse.parse("{} ({})", line.strip())
                nodes[parsed[0]] = Node(parsed[0], int(parsed[1]), [])
            else:
                nodes[parsed[0]] = Node(parsed[0], int(parsed[1]), parsed[2].split(', '))
            line = file.readline()
    print(len(nodes))
    
    for node in nodes.values():
        for child in node.children:
            nodes[child].parent = node

    root = getRoot(nodes, nodes.values()[0])

    return findImbalance(nodes, nodes[root])

if __name__ == "__main__":
    print(result())
