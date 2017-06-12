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
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();

    int labyrinth[H][W];
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> labyrinth[i][j];
        }
        cin.ignore();
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();

        int type = labyrinth[YI][XI];

        switch(type){
        case 0:
        	break;
        case 1:
        case 3:
        case 7:
        case 8:
        case 9:
        case 12:
        case 13:
        	++YI;
        	break;
        case 2:
        case 6:
            if(POS == "LEFT") ++XI;
            else if(POS == "RIGHT") --XI;
            break;
        case 4:
            if(POS == "TOP") --XI;
            else if(POS == "RIGHT") ++YI;
            break;
        case 5:
            if(POS == "TOP") ++XI;
            else if(POS == "LEFT") ++YI;
            break;
        case 10:
        	--XI;
        	break;
        case 11:
        	++XI;
        	break;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
        cout << XI << " " << YI << endl;
    }
}
