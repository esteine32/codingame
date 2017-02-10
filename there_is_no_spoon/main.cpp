#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    bool cells [width][height];
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        
        for(int j=0; j<width; ++j)
        {
            cells[j][i] = line[j] == '0';
        }
    }
    
    for(int i=0; i<height; i++) 
    {
        for(int j=0; j<width; j++)
        {
            if(cells[j][i])
            {

                int x1, y1, x2, y2;
                x1 = y1 = x2 = y2= -1;
                
                for(int k = j+1; k<width; k++)
                {
                    if(cells[k][i])
                    {
                        x1 = k;
                        y1 = i;
                        break;
                    }
                }
                
                for(int k = i+1; k<height; k++)
                {
                    if(cells[j][k])
                    {
                        x2 = j;
                        y2 = k;
                        break;
                    }
                }


                cout << j << " " << i << " " << x1 << " "  << y1 << " " << x2 << " "  << y2 << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor
            }
        }    
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
}