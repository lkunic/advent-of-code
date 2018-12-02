#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int star1()
{
    ifstream ifs("day1.in", std::ifstream::in);

    int sum = 0;
    string s;
    while (ifs >> s)
    {
        if (s[0] == '+') {
            s = s.substr(1);
        }
        sum += stoi(s);
    }

    return sum;
}

int star2()
{
    ifstream ifs("day1.in", std::ifstream::in);

    set<int> previousSums;
    vector<int> inputs;

    string s;
    while (ifs >> s)
    {
        if (s[0] == '+') {
            s = s.substr(1);
        }
               
        int value = stoi(s);
        inputs.push_back(value);
    }

    int sum = 0;
    int i = 0;
    int n = inputs.size();
    while (true)
    {
        sum += inputs[i++ % n];
        if (previousSums.count(sum) == 0) {
            previousSums.insert(sum);
        }
        else {
            break; 
        }
    }

    return sum;
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}