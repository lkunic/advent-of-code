import parse

def result():
    commands = []
    registers = {}

    with open('in18.txt', 'r') as f:
        line = f.readline()
        while line:
            command = list(parse.parse('{} {}', line))
            if command[0] in ['set', 'add', 'mul', 'mod', 'jgz']:
                parsed = parse.parse('{} {}', command[1])
                command[1] = parsed[0]
                command.append(parsed[1])

                if command[1] not in registers:
                    registers[command[1]] = 0

            commands.append(command)
            line = f.readline()

    lastPlayed = ''

    i = 0
    while True:
        if i >= len(commands) or i < 0:
            break

        comm = commands[i]
        if comm[0] == 'set':
            if comm[2].isdigit() or comm[2][0] == '-':
                registers[comm[1]] = int(comm[2])
            else:
                registers[comm[1]] = int(registers[comm[2]])
        if comm[0] == 'add':
            if comm[2].isdigit() or comm[2][0] == '-':
                registers[comm[1]] += int(comm[2])
            else:
                registers[comm[1]] += int(registers[comm[2]])
        if comm[0] == 'mul':
            if comm[2].isdigit() or comm[2][0] == '-':
                registers[comm[1]] *= int(comm[2])
            else:
                registers[comm[1]] *= int(registers[comm[2]])
        if comm[0] == 'mod':
            if comm[2].isdigit() or comm[2][0] == '-':
                registers[comm[1]] %= int(comm[2])
            else:
                registers[comm[1]] %= int(registers[comm[2]])
        if comm[0] == 'jgz':
            if registers[comm[1]] > 0:
                i += int(comm[2])
                continue
        if comm[0] == 'jgz':
            if registers[comm[1]] != 0:
                break
        if comm[0] == 'snd':
            lastPlayed = registers[comm[1]]

        i += 1
    return lastPlayed

if __name__ == "__main__":
    print(result())
