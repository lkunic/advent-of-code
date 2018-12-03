#include <iostream>
#include <fstream>
#include <set>

using namespace std;

#define maxsize 1000

int star1()
{
    int* map = (int*)malloc(sizeof(int) * maxsize * maxsize);
    ifstream ifs("day3.in", std::ifstream::in);

    int counter = 0;

    string s;
    int id = 0, x = 0, y = 0, w = 0, h = 0;
    while (getline(ifs, s, '\n')) 
    {
        sscanf(s.c_str(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &w, &h);
        
        for (int i = x; i < x + w; i++) {
            for (int j = y; j < y + h; j++) {
                map[i * maxsize + j] += 1;
                if (map[i * maxsize + j] == 2)
                {
                    counter++;
                }
            }
        }
    }

    return counter;
}

int star2()
{
    int* map = (int*)malloc(sizeof(int) * maxsize * maxsize);
    ifstream ifs("day3.in", std::ifstream::in);

    set<int> cleanClaims;

    string s;
    int id = 0, x = 0, y = 0, w = 0, h = 0;
    bool isClean;
    while (getline(ifs, s, '\n')) 
    {
        isClean = true;
        sscanf(s.c_str(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &w, &h);
        
        for (int i = x; i < x + w; i++) {
            for (int j = y; j < y + h; j++) {
                int pos = i * maxsize + j;
                if (map[pos] != 0)
                {
                    cleanClaims.erase(map[pos]);
                    isClean = false;
                }
                map[pos] = id;
            }
        }

        if (isClean)
        {
            cleanClaims.insert(id);
        }
    }

    return *(cleanClaims.begin());
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}