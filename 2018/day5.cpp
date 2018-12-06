#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

bool match(char c1, char c2) {
    return c1 != c2 && (toupper(c1) == c2 || tolower(c1) == c2);
}

bool reduce(int current, int& next, const string& in, vector<char>& out)
{
    if (match(in[current], in[next])) {
        next++;
        return false;
    }

    char currentChar = in[current];
    current++;
    next++;
    while (next <= in.size() && !reduce(current, next, in, out))
    {
        if (match(currentChar, in[next])) {
            next++;
            return false;
        }
        current = next;
        next++;
    }

    out.insert(out.begin(), currentChar);
    return true;
}

int star1()
{
    ifstream ifs("day5.in", fstream::in);

    string s;
    ifs >> s;
    vector<char> reduced;
    int current = 0;
    int next = 1;
    reduce(current, next, "|" + s, reduced);
    reduced.erase(reduced.begin(), reduced.begin() + 1);

    return reduced.size();
}

int star2()
{
    ifstream ifs("day5.in", fstream::in);

    string s;
    ifs >> s;
    set<char> units;

    for (int i = 0; i < s.length(); i++)
    {
        units.insert(toupper(s[i]));
    }

    unsigned int minSize = INT_MAX;
    for (auto it : units)
    {
        int current = 0;
        int next = 1;
        vector<char> reduced;
        string modified(s);
        modified.erase(remove(modified.begin(), modified.end(), it), modified.end());
        modified.erase(remove(modified.begin(), modified.end(), tolower(it)), modified.end());
        reduce(current, next, "|" + modified, reduced);

        if (reduced.size() < minSize)
            minSize = reduced.size();
    }

    return minSize - 1;
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}
