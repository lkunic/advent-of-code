import parse
import sys

class particle:
    def __init__(self, position, velocity, acceleration):
        self.p = [int(p) for p in position]
        self.v = [int(v) for v in velocity]
        self.a = [int(a) for a in acceleration]

def result():
    particles = []
    with open('in20.txt', 'r') as f:
        line = f.readline().strip()
        while line:
            parsed = parse.parse('p=<{}>, v=<{}>, a=<{}>', line)
            particles.append(particle(parsed[0].split(','), parsed[1].split(','), parsed[2].split(',')))
            line = f.readline().strip()

    t = 1000
    bestdist = sys.maxint
    best = 0
    for i in range(len(particles)):
        p = particles[i]
        x = p.p[0] + t * p.v[0] + t * t * p.a[0]
        y = p.p[1] + t * p.v[1] + t * t * p.a[1]
        z = p.p[2] + t * p.v[2] + t * t * p.a[2]
        dist = abs(x) + abs(y) + abs(z)

        if dist < bestdist:
            bestdist = dist
            best = i

    return best, bestdist

if __name__ == '__main__':
    print(result())
