#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cstring>
#include <map>

using namespace std;

int star1()
{
    fstream ifs("day6.in", fstream::in);

    int grid[500][500];

    vector<pair<int, int>> coords;
    int x, y;
    char fill;
    while (ifs >> x >> fill >> y)
    {
        coords.push_back(pair<int, int>(x, y));
    }

    int n = coords.size();
    int dist, minDist, minK;
    bool equallyFar;
    for (int i = 0; i < 500; i++) 
    {
        for (int j = 0; j < 500; j++) 
        {
            minDist = INT_MAX;
            equallyFar = false;
            for (int k = 0; k < n; k++)
            {
                dist = abs(i - coords[k].first) + abs(j - coords[k].second);
                if (dist < minDist) {
                    minDist = dist;
                    minK = k;
                }
                else if (dist == minDist) {
                    equallyFar = true;
                    break;
                }
            }

            grid[i][j] = equallyFar ? 0 : minK;
        }
    }

    int counts[n + 1];
    memset(counts, 0, sizeof(counts));
    for (int i = 0; i < 500; i++) 
    {
        for (int j = 0; j < 500; j++) 
        {
            counts[grid[i][j]]++;
        }
    }
    for (int i = 0; i < 500; i++)
    {
        counts[grid[0][i]] = 0;
        counts[grid[499][i]] = 0;
        counts[grid[i][0]] = 0;
        counts[grid[i][499]] = 0;
    }

    int max = 0;
    for (int i = 0; i <= n; i++)
    {
        if (counts[i] > max) {
            max = counts[i];
        }
    }

    return max;
}

int star2()
{
    fstream ifs("day6.in", fstream::in);

    int grid[500][500];

    vector<pair<int, int>> coords;
    int x, y;
    char fill;
    while (ifs >> x >> fill >> y)
    {
        coords.push_back(pair<int, int>(x, y));
    }

    int n = coords.size();
    int limit = 10000;
    int distSum;

    for (int i = 0; i < 500; i++) 
    {
        for (int j = 0; j < 500; j++) 
        {
            distSum = 0;
            for (int k = 0; k < n; k++)
            {
                distSum += abs(i - coords[k].first) + abs(j - coords[k].second);
                if (distSum > limit) {
                    break;
                }
            }

            grid[i][j] = distSum < limit ? 1 : 0;
        }
    }

    int count = 0;
    for (int i = 0; i < 500; i++) 
    {
        for (int j = 0; j < 500; j++) 
        {
            count += grid[i][j];
        }
    }

    return count;
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}