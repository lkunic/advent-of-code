def distance(horizontal, vertical):
    horizontal = abs(horizontal)
    vertical = abs(vertical)
    count = 0
    while horizontal > 0:
        horizontal -= 1
        vertical -= 0.5
        count += 1
    
    while vertical > 0:
        vertical -= 1
        count += 1
    
    return count

def result():
    directions = []
    with open('in11.txt', 'r') as file:
        line = file.readline()
        directions = line.strip().split(',')
        
    horizontal = 0
    vertical = 0
    
    max = 0
    
    for dir in directions:
        if dir == 'n':
            vertical += 1
        elif dir == 's':
            vertical -= 1
        elif dir == 'se':
            vertical -= 0.5
            horizontal += 1
        elif dir == 'sw':
            vertical -= 0.5
            horizontal -= 1
        elif dir == 'ne':
            vertical += 0.5
            horizontal += 1
        elif dir == 'nw':
            vertical += 0.5
            horizontal -= 1
        
        a = distance(horizontal, vertical)
        if a > max:
            max = a

    return max

if __name__ == '__main__':
    print(result())
