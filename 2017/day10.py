

def result():
    lengthstring = '46,41,212,83,1,255,157,65,139,52,39,254,2,86,0,204'
    lengths = []
    for c in lengthstring:
        lengths.append(ord(c))
    lengths.extend([17, 31, 73, 47, 23])
    print (lengths)
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

        result += str(hex(a))[2:].zfill(2)




    return result

if __name__ == "__main__":
    print(result())
