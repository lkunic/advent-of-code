def result():
    commands = []
    with open('in16.txt', 'r') as file:
        line = file.readline().strip()
        commands = line.split(',')

    names = 'abcdefghijklmnop'
    nIter = range(len(names))

    swapString = [name for name in names]
    for comm in commands:
        if comm[0] == 'p':
            a = comm[1]
            b = comm[3]
            for i in nIter:
                if swapString[i] == a:
                    swapString[i] = b
                elif swapString[i] == b:
                    swapString[i] = a

    permutationString = [name for name in names]
    for comm in commands:
        if comm[0] == 's':
            n = int(comm[1:])
            permutationString = permutationString[-n:] + permutationString[:-n]
        elif comm[0] == 'x':
            indices = comm[1:].split('/')
            a = int(indices[0])
            b = int(indices[1])

            temp = permutationString[a]
            permutationString[a] = permutationString[b]
            permutationString[b] = temp
    permutationString = ''.join(permutationString)

    permutationIndices = []
    for x in names:
        for i in range(len(permutationString)):
            if permutationString[i] == x:
                permutationIndices.append(i)

    dancers = [name for name in names]
    iters = 1000000000
    for k in range(iters % 12):
        newDancers = [''] * len(dancers)
        for i in nIter:
            newDancers[permutationIndices[i]] = dancers[i]
        dancers = newDancers

    for k in range(iters % 16):
        for i in nIter:
            for j in nIter:
                if dancers[i] == names[j]:
                    dancers[i] = swapString[j]
                    break

    return ''.join(dancers)

if __name__ == '__main__':
    print(result())
