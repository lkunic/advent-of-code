#include <iostream>
#include <fstream>

using namespace std;

int star1()
{
    ifstream ifs("./day1.in", ifstream::in);

    int total = 0;
    int number;
    while (ifs >> number)
    { 
        total += number / 3 - 2;
    }

    return total;
}

int star2()
{
    ifstream ifs("./day1.in", ifstream::in);

    int total = 0;
    int number;
    while (ifs >> number)
    { 
        int fuel = number / 3 - 2;
        int totalFuel = 0;
        while (fuel > 0)
        {
            totalFuel += fuel;
            fuel = fuel / 3 - 2;
        }

        total += totalFuel;
    }

    return total;
}

int main()
{
    cout << star1() << endl;
    cout << star2() << endl;
}
