from queue import Queue

def knot(key):
    lengths = []
    for c in key:
        lengths.append(ord(c))
    lengths.extend([17, 31, 73, 47, 23])
    current = 0
    skip = 0

    arr = list(range(256))

    for i in range(64):
        for length in lengths:
            sub = []
            for a in range(current, current+length):
                sub.append(arr[a % len(arr)])

            sub.reverse()

            for a in range(current, current+length):
                arr[a % len(arr)] = sub[a - current]

            current = (current + length + skip) % len(arr)
            skip += 1

    result = ''
    for i in range(16):
        a = arr[i * 16]
        for k in range(1,16):
            a = a ^ arr[i * 16 + k]

        result += format(a, '08b')
    return result

def bfs(table, start):
    q = Queue()
    q.put(start)
    while not q.empty():
        pos = q.get()
        table[pos[0]][pos[1]] = '2'
        for a, b in zip([-1, 1, 0, 0], [0, 0, -1, 1]):
            i = pos[0] + a
            j = pos[1] + b
            if i >= 0 and j >= 0 and i < len(table) and j < len(table[i]) and table[i][j] == '1':
                q.put((i, j))

def result():
    table = []
    for i in range(128):
        table.append([c for c in knot('jxqlasbh-%d' % i)])

    count = 0
    for i in range(128):
        for j in range(128):
            if table[i][j] == '0' or table[i][j] == '2':
                continue
            bfs(table, (i,j))
            count += 1

    return count

if __name__ == '__main__':
    print(result())
