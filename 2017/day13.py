import parse
import math

def result():
    scanners = []
    with open('in13.txt', 'r') as file:
        line = file.readline()
        while (line):
            parsed = parse.parse("{}: {}", line.strip())
            scanners.append([int(parsed[0]), int(parsed[1])])
            line = file.readline()

    delay = 0
    depth = 0
    while True:
        error = 0
        for scan in scanners:
            depth = scan[0]
            size = scan[1]
            wallposition = 0
            distance = depth + delay
            iterations = math.floor(distance / (size - 1))
            if iterations % 2 == 0:
                wallposition = distance % (size - 1)
            else:
                wallposition = size - distance % (size - 1)

            if wallposition == 0:
                error += depth * size
                break

        if error == 0 and depth != 0:
            return delay

        if delay % 10000 == 0:
            print delay
        delay += 1

if __name__ == "__main__":
    print(result())
