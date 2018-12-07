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

typedef struct Elf {
    int time = -1;
    int stepId = -1;
} Elf;

int star2()
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

    Elf elves[5];
    int elapsedTime = 0;
    int remainingTime = 1;
    int inProgress = 0;
    int completed = -1;
    bool changed = true;

    while(remainingTime > 0) 
    {
        remainingTime--;
        for (int i = 0; i < 5; i++)
        {
            elves[i].time--;
            if (elves[i].time == 0) {
                if (elves[i].stepId != -1) {
                    inProgress &= ~(1 << elves[i].stepId);
                    completed &= ~(1 << elves[i].stepId);
                    requirements[elves[i].stepId] = -1;
                    elves[i].stepId = -1;
                    changed = true;
                }
            }
        }
        if (changed) 
        {
            for (int i = 0; i < 5; i++)
            {
                if (elves[i].time <= 0) {
                    for (int j = 0; j < requirements.size(); j++)
                    {
                        if (requirements[j] != -1 && (requirements[j] & completed) == 0 && (inProgress & 1 << j) == 0) {
                            inProgress |= 1 << j;
                            elves[i].time = 61 + j;
                            elves[i].stepId = j;
                            remainingTime = max(remainingTime, elves[i].time);
                            break;
                        }
                    }   
                }
            }
        }
        
        changed = false;
        elapsedTime++;
    }
    
    return elapsedTime - 1;
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}
