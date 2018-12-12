#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#define BUFFER_SIZE 1000001

using namespace std;

struct Pattern 
{
    bool pattern[5];
    bool result;

    bool isMatch(bool* in, int position) 
    {
        for (int i = 0; i < 5; i++)
        {
            if (in[position + i - 2] != pattern[i]) {
                return false;
            }
        }

        return true;
    }

    Pattern(const char* s, char res) 
    {
        for (int i = 0; i < 5; i++)
        {
            pattern[i] = s[i] == '#';
        }

        result = res == '#';
    }
};

int generate(bool* pots, const vector<Pattern>& patterns, long numGenerations)
{
    int first = BUFFER_SIZE;
    int last = 0;
    for (int i = 2; i < BUFFER_SIZE - 2; i++)
    {
        if (pots[i]) {
            if (i < first) first = i;
            if (i > last) last = i;
        }
    }

    bool* parents = (bool*)malloc(BUFFER_SIZE * sizeof(bool));
    bool* generation = (bool*)malloc(BUFFER_SIZE * sizeof(bool));

    memcpy(parents, pots, BUFFER_SIZE * sizeof(bool));

    for (int k = 0; k < numGenerations; k++)
    {
        memset(generation, false, BUFFER_SIZE * sizeof(bool));
        for (int i = max(2, first - 2), n = min(BUFFER_SIZE - 2, last + 2); i <= n; i++)
        {
            for (Pattern p : patterns)
            {
                if (p.isMatch(parents, i)) {
                    generation[i] = p.result;

                    if (generation[i])
                    {
                        if (i < first) first = i;
                        if (i > last) last = i;
                    }
                    break;
                }
            }
        }

        memcpy(parents, generation, BUFFER_SIZE * sizeof(bool));
    }

    free(generation);

    int result = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        result += parents[i] ? i - BUFFER_SIZE / 2 : 0;
    }
    
    return result;
}

long part2(bool* pots, const vector<Pattern>& patterns)
{
    int gen, last = 0;
    for (int i = 0; i <= 110; i++)
    {
        gen = generate(pots, patterns, i);
        last = gen;
    }

    // the value increases by 65 after initial 110 generations
    return gen + (50000000000 - 110) * 65;
}

int main()
{
    fstream ifs("day12.in", fstream::in);

    string s;
    getline(ifs, s, '\n');

    bool* pots = (bool*)malloc(BUFFER_SIZE * sizeof(bool));
    memset(pots, false, BUFFER_SIZE * sizeof(bool));

    for (int i = 0; i < s.length(); i++)
    {
        pots[BUFFER_SIZE / 2 + i] = s[i] == '#';
    }
    
    vector<Pattern> patterns;
    char* pattern = (char*)malloc(5 * sizeof(char));
    char* result =  (char*)malloc(sizeof(char));;
    while (getline(ifs, s, '\n'))
    {
        sscanf(s.c_str(), "%s => %s", pattern, result);
        patterns.push_back(Pattern(pattern, result[0]));
    }

    cout << generate(pots, patterns, 20) << endl;
    cout << part2(pots, patterns) << endl;

    return 0;
}