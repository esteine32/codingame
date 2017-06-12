#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping Y0ou parse
 * the standard input according to the problem statement.
 **/
 

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore(); //Starting position of Batman

    int minY = 0;
    int maxY = H-1;
    int minX = 0;
    int maxX = W-1;

    // game loop
    while (1) {
        string BOMB_DIR; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> BOMB_DIR; cin.ignore();

        // binary search
        if(BOMB_DIR.find("U") != string::npos)
        {
        	maxY = Y0;
            Y0 = minY + floor((maxY-minY)/2.0);
        }
        if(BOMB_DIR.find("D") != string::npos) {
        	minY = Y0;
            Y0 = minY + ceil((maxY-minY)/2.0);
        }
        if(BOMB_DIR.find("L") != string::npos) {
        	maxX = X0;
            X0 = minX + floor((maxX-minX)/2.0);
        }
        if(BOMB_DIR.find("R") != string::npos) {
        	minX = X0;
            X0 = minX + ceil((maxX-minX)/2.0);
        }
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        

        cout << X0 << " " << Y0 << endl; // the location of the next window Batman should jump to.
    }
}
