
def result():
    step = 335
    position = 0
    buff = [0]

    for k in range(1, 20):
        position = (position + step) % len(buff)
        buff.insert(position + 1, k)
        position += 1

    return buff[position - 1], buff[position], buff[position + 1]

def result2():
    step = 335
    position = 0
    buffSize = 1
    zeroPos = 0
    nextValue = 0

    for k in range(1, 50000000):
        position = (position + step) % buffSize
        if position == zeroPos:
            nextValue = k
        if position < zeroPos:
            zeroPos += 1
        buffSize += 1
        position += 1

    return nextValue

if __name__ == "__main__":
    print(result2())
