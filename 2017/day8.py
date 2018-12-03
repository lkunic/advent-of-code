import parse

def result():
    with open('in8.txt') as file:
        registers = {}
        line = file.readline()
        max = 0
        while line:
            parsed = parse.parse('{} {} {} if {} {} {}', line)
            reg = parsed[0]
            operation = parsed[1]
            amount = int(parsed[2])
            conditionArg = parsed[3]
            conditionOp = parsed [4]
            conditionValue = int(parsed[5])

            if reg not in registers:
                registers[reg] = 0
            if conditionArg not in registers:
                registers[conditionArg] = 0

            conditionReg = registers[conditionArg]
            if ((conditionOp == '>' and conditionReg > conditionValue) or
                    (conditionOp == '>=' and conditionReg >= conditionValue) or
                    (conditionOp == '<' and conditionReg < conditionValue) or
                    (conditionOp == '<=' and conditionReg <= conditionValue) or
                    (conditionOp == '==' and conditionReg == conditionValue) or
                    (conditionOp == '!=' and conditionReg != conditionValue)):
                if operation == 'inc':
                    registers[reg] += amount
                else:
                    registers[reg] -= amount

                if registers[reg] > max:
                    max = registers[reg]

            line = file.readline()

#        max = 0
#        for key, reg in registers.items():
#            if reg > max:
#                max = reg

        return max

if __name__ == "__main__":
    print(result())
