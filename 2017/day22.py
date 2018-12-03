def printsurroundings(arr, x, y):
    print arr[x-1][y-1:y+2]
    print arr[x][y-1:y+2]
    print arr[x+1][y-1:y+2]


def result():
    grid = {}

    with open('in22.txt', 'r') as f:
        line = f.readline().strip()
        i = 0
        while line:
            for j in range(len(line)):
                grid[(i, j)] = line[j]
            line = f.readline().strip()
            i += 1

    x = 12
    y = 12

    result = 0
    direction = 'u'
    right = {'u':'r', 'r':'d', 'd':'l', 'l':'u'}
    left = {'u':'l', 'r':'u', 'd':'r', 'l':'d'}

    forward = {'u':[-1, 0], 'r':[0, 1], 'd':[1, 0], 'l':[0, -1]}

    for i in range(10000000):
        if (x, y) not in grid:
            grid[(x, y)] = '.'
        if grid[(x, y)] == '.':
            grid[(x, y)] = 'w'
            direction = left[direction]
        elif grid[(x, y)] == 'w':
            grid[(x, y)] = '#'
            result += 1
        elif grid[(x, y)] == '#':
            grid[(x, y)] = 'f'
            direction = right[direction]
        elif grid[(x, y)] == 'f':
            grid[(x, y)] = '.'
            direction = right[right[direction]]
        x += forward[direction][0]
        y += forward[direction][1]

    return result



if __name__ == '__main__':
    print (result())
