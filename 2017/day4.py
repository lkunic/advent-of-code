def result():
    result = 0
    
    with open('in.txt', 'r') as file:
        line = file.readline()
        while (line):
            pwd = line.strip().split(' ')
            for i in range(len(pwd)):
                pwd[i] = ''.join(sorted(pwd[i]))
            if len(pwd) != 0 and len(pwd) == len(set(pwd)):
                result += 1
            else:
                print(line)
            line = file.readline()

    return result

if __name__ == "__main__":
    print(result())
