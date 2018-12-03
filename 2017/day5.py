def result():
    result = 0
    arr = []
    
    with open('in.txt', 'r') as file:
        line = file.readline()
        while (line):
            arr.append(int(line.strip()))
            line = file.readline()

    sizeofarr = len(arr)
    current = 0
    count = 0
    while (current >= 0 and current < sizeofarr):
        prev = arr[current]
        arr[current] += (1 if prev < 3 else -1)
        current += prev
        count += 1

    return count

if __name__ == "__main__":
    print(result())

