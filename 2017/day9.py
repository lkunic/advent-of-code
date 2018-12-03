
def result():
    with open('in9.txt', 'r') as file:
        line = file.readline()

        #line = '<{o"i!a,<{i<a>'

        count = 0
        level = 1
        garbage = False
        ignore = False

        for c in line:
            if ignore:
                ignore = False
            elif c == '!':
                ignore = True
            elif garbage:
                if c == '>':
                    garbage = False
                else:
                    count += 1
            elif not garbage:
                if c == '<':
                    garbage = True
                elif c == '{':
                    level += 1
                elif c == '}':
                    level -= 1
                    #count += level

        return count

if __name__ == "__main__":
    print(result())
