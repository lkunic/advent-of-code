#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <climits>

using namespace std;

class Point
{
public:
    int x = 0;
    int y = 0;
    int vx = 0;
    int vy = 0;

    void move()
    {
        x += vx;
        y += vy;
    }

    bool isNeighbor(const Point* other)
    {
        return sqrt(pow(x - other->x, 2) + pow(y - other->y, 2)) < 1.5;
    }
};

void printPoints(const vector<Point*>& points)
{
    int minX = INT_MAX;
    int maxX = INT_MIN;
    int minY = INT_MAX;
    int maxY = INT_MIN;

    for (Point* p : points) {
        if (p->x < minX) minX = p->x;
        if (p->y < minY) minY = p->y;
        if (p->x > maxX) maxX = p->x;
        if (p->y > maxY) maxY = p->y;
    }

    int sizeX = maxX - minX + 2;
    int sizeY = maxY - minY + 2;
    char grid[sizeY][sizeX];
    memset(grid, ' ', sizeof(grid));

    for (Point* p : points) {
        grid[p->y - minY + 1][p->x - minX + 1] = '#';
    }

    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            cout << grid[i][j];
        }

        cout << endl;
    }
}

bool arePointsTogether(const vector<Point*>& points)
{
    bool hasNeighbors;
    for (int i = 0; i < points.size(); i++)
    {
        hasNeighbors = false;
        for (int j = 0; j < points.size(); j++)
        {
            if (i == j) {
                continue;
            }
            if (points[i]->isNeighbor(points[j])) {
                hasNeighbors = true;
                break;
            }
        }

        if (!hasNeighbors) {
            return false;
        }
    }

    return true;
}

int main()
{
    ifstream ifs("day10.in", fstream::in);
    
    vector<Point*> points;
    string s;
    while (getline(ifs, s, '\n'))
    {
        Point* p = new Point();
        sscanf(s.c_str(), "position=<%d,%d> velocity=<%d,%d>", &(p->x), &(p->y), &(p->vx), &(p->vy));
        points.push_back(p);
    }

    int count = 0;
    do { 
        for (Point* p : points) 
        { 
            p->move(); 
        } 
        count++;
    } while (!arePointsTogether(points));

    printPoints(points);
    cout << count << " seconds" << endl;

}