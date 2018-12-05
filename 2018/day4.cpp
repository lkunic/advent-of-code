#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;

#define kActionShift 0
#define kActionSleep 1
#define kActionAwake 2

class Entry {
public:
    time_t timestamp;
    int guardId = 0;
    int action;
    int minute;

    Entry(int y, int mo, int d, int h, int m, char* act)
    {
        tm t = {0};
        t.tm_year = y;
        t.tm_mon = mo - 1;
        t.tm_mday = d;
        t.tm_hour = h;
        t.tm_min = m;
        minute = m;
        timestamp = mktime(&t);

        if (strcmp(act, "falls asleep") == 0) {
            action = kActionSleep;
        }
        else if (strcmp(act, "wakes up") == 0) {
            action = kActionAwake;
        }
        else {
            sscanf(act, "Guard #%d begins shift", &guardId);
            action = kActionShift;
        }
    }

    bool operator <(const Entry& rhs) {
        return timestamp < rhs.timestamp;
    }
};

class Guard {
public:
    vector<int> minutes;
    int totalMinutes;
    int id;
    int maxMinutes;
    int topMinute;

    Guard(int id)
    {
        minutes.resize(60);
        std::fill(minutes.begin(), minutes.end(), 0);
        totalMinutes = 0;
        maxMinutes = 0;
        topMinute = 0;
        this->id = id;
    }

    void incrementMinute(int i)
    {
        minutes[i] += 1;
        if (minutes[i] > maxMinutes)
        {
            maxMinutes = minutes[i];
            topMinute = i;
        }
    }
};

int main()
{
    ifstream ifs("day4.in", ifstream::in);

    vector<Entry> entries;

    string s;
    int y = 0, mo = 0, d = 0, h = 0, m = 0;
    char* action = (char*)malloc(50 * sizeof(char));
    while(getline(ifs, s, '\n'))
    {
        sscanf(s.c_str(), "[%d-%d-%d %d:%d] %[^\t\n]", &y, &mo, &d, &h, &m, action);
        Entry entry(y, mo, d, h, m, action);
        entries.push_back(entry);
    }

    sort(entries.begin(), entries.end());

    int currentId = 0;
    int sleepStart = 0;
    map<int, Guard*> guards;

    int maxMinutes = 0;
    int topGuard = 0;

    for (auto it = entries.begin(); it != entries.end(); ++it)
    {
        if (it->action == kActionShift) {
            if (guards.count(it->guardId) == 0)
            {
                Guard* guard = new Guard(it->guardId);
                guards[it->guardId] = guard;
            }

            currentId = it->guardId;
        }
        else if (it->action == kActionSleep) {
            sleepStart = it->minute;
        }
        else if (it->action == kActionAwake && sleepStart != 0) {
            guards[currentId]->totalMinutes += it->minute - sleepStart;
            if (guards[currentId]->totalMinutes > maxMinutes)
            {
                maxMinutes = guards[currentId]->totalMinutes;
                topGuard = currentId;
            }
            for (int i = sleepStart, n = it->minute; i < n; i++)
            {
                guards[currentId]->incrementMinute(i);
            }
        }
    }

    Guard* sleeper = guards[topGuard];
    int mostSleeps = 0;
    int topMinute = 0;

    for (int i = 0; i < 60; i++)
    {
        if (sleeper->minutes[i] > mostSleeps)
        {
            topMinute = i;
            mostSleeps = sleeper->minutes[i];
        }
    }

    cout << "star 1: " << topGuard * (topMinute) << endl;

    mostSleeps = 0;
    topMinute = 0;
    topGuard = 0;
    for (auto it = guards.begin(); it != guards.end(); ++it) 
    {
        if (it->second->maxMinutes > mostSleeps)
        {
            topMinute = it->second->topMinute;
            topGuard = it->second->id;
            mostSleeps = it->second->maxMinutes;
        }
    }
    
    cout << "star 2: " << topGuard * topMinute << endl;
}