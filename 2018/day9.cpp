#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class Marble {
public:
    Marble(int v) :
        value(v) {};

    Marble* previous;
    Marble* next;

    Marble* reverse(int steps) 
    {
        if (steps == 0) {
            return this;
        }
        else {
            return previous->reverse(steps - 1);
        }
    }

    Marble* insert(int value) 
    {
        Marble* newMarble = new Marble(value);
        newMarble->next = next;
        newMarble->previous = this;
        next->previous = newMarble;
        next = newMarble;

        return newMarble;
    }

    void erase() 
    {
        previous->next = next;
        next->previous = previous;
        delete(this);
    }

    int value;
};

long topScore(int players, int marbleCount)
{
    vector<long> scores;
    scores.resize(players, 0);

    Marble* marble = new Marble(0);
    marble->previous = marble;
    marble->next = marble;

    for (int i = 1; i < marbleCount; i++) 
    {
        if (i % 23 == 0) {
            int currentPlayer = (i - 1) % players;
            scores[currentPlayer] += i;
            
            marble = marble->reverse(7);
            scores[currentPlayer] += marble->value;
            Marble* nextMarble = marble->next;
            marble->erase();
            marble = nextMarble;
        }
        else {
            marble = marble->next->insert(i);
        }
    }

    long maxScore = 0;
    for (long score : scores) 
    {
        if (score > maxScore) 
            maxScore = score;
    }
    return maxScore;
}

int main()
{
    fstream ifs("day9.in", fstream::in);
    int players, marbles;
    string s;
    getline(ifs, s, '\n');
    sscanf(s.c_str(), "%d players; last marble is worth %d points", &players, &marbles);

    cout << topScore(players, marbles) << endl;
    cout << topScore(players, marbles * 100) << endl;

    return 0;
}