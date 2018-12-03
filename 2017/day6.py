
def result():
    arr = [4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5]
    prevStates = set()
    
    prevStates.add(str(arr))
    
    loop = False

    while(True):
        m = max(arr)
        mi = [i for i in range(len(arr)) if arr[i] == m][0]
        
        arr[mi] = 0
        while (m != 0):
            mi = (mi + 1) % len(arr)
            arr[mi] += 1
            m -= 1

        num = len(prevStates)
        prevStates.add(str(arr))

        if (num == len(prevStates)):
            if (loop):
                return num
            else:
                prevStates = set()
                prevStates.add(str(arr))
                loop = True


if __name__ == "__main__":
    print(result())
