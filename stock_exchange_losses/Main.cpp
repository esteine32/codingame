#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n;
    cin >> n; cin.ignore();

    int value, top = 0, loss = 0;
    for (int i = 0; i < n; i++) {
        cin >> value; cin.ignore();

        if(value > top) top = value;

        if(value - top < loss) loss = value - top;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << loss << endl;
}
