#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int star1()
{
    ifstream ifs("day2.in", std::ifstream::in);

    string s;
    map<char, int> counts;
    int twos = 0;
    int threes = 0;
    while (ifs >> s)
    {
        bool hasTwo = false;
        bool hasThree = false;

        counts.clear();

        for (char c : s) 
        {
            counts[c] = counts.count(c) == 0 ? 1 : counts[c] + 1;
        }       
        
        for (auto it = counts.begin(); it != counts.end(); ++it) 
        {
            if (it->second == 2) {
                hasTwo = true;
            }
            else if (it->second == 3) {
                hasThree = true;
            }
        }

        if (hasTwo) twos++;
        if (hasThree) threes++;
    }

    return twos * threes;
}

string star2()
{
    ifstream ifs("day2.in", std::ifstream::in);

    string s;
    vector<string> words;
    while (ifs >> s)
    {
       words.push_back(s);
    }

    int wordSize = words[0].size();
    for (int i = 0, n = words.size(); i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            int diffLocation = 0;
            for (int c = 0; c < wordSize; c++) 
            {
                if (words[i][c] != words[j][c]) {
                    if (diffLocation > 0) {
                        diffLocation = -1;
                        break;
                    }
                    diffLocation = c;
                }
            }
            
            if (diffLocation != -1)
            {
                return words[i].substr(0, diffLocation) + words[i].substr(diffLocation + 1);
            }
        }
    }

    return "";
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}