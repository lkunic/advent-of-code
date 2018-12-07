#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>

using namespace std;

string star1()
{
    ifstream ifs("day7.in", fstream::in);

    vector<int> requirements;
    requirements.resize(26, 0);

    string s;
    while (getline(ifs, s, '\n'))
    {
        char step, requiredStep;
        sscanf(s.c_str(), "Step %c must be finished before step %c can begin.", &requiredStep, &step);

        int stepId = step - 'A';
        int requiredStepId = requiredStep - 'A';
        requirements[stepId] |= 1 << requiredStepId;
    }

    int completed = -1;
    bool done = false;
    stringstream ss;

    while (!done)
    {
        done = true;
        for (int i = 0; i < requirements.size(); i++)
        {
            if (requirements[i] != -1 && (requirements[i] & completed) == 0)
            {
                completed &= ~(1 << i);
                ss << (char)('A' + i);
                requirements[i] = -1;
                done = false;
                break;
            }
        }
    }

    return ss.str();
}

string star2()
{
    return "0";
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}
