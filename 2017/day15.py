def result():
    factorA = 16807
    factorB = 48271
    divider = 2147483647

    valueA = 618
    valueB = 814

    score = 0

    valuesA = []
    valuesB = []

    count = 0
    while count < 5000000:
        valueA = valueA * factorA % divider
        if valueA % 4 == 0:
            valuesA.append(valueA)
            count += 1

        if count % 100000 == 0:
            print count

    count = 0
    while count < 5000000:
        valueB = valueB * factorB % divider
        if valueB % 8 == 0:
            valuesB.append(valueB)
            count += 1

        if count % 100000 == 0:
            print count

    count = 0
    for a, b in zip(valuesA, valuesB):
        if (format(a, '016b')[-16:] == format(b, '016b')[-16:]):
            score += 1

        count += 1
        if count % 100000 == 0:
            print count

    return score

if __name__ == "__main__":
    print(result())
