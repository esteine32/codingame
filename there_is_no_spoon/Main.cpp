#include <iostream>
#include <vector>

#include "Node.h"

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
    
    //x: current column
    //y: current row
    //frontWidth[y]: observed node there is most to the right for row y
    //frontHeight[x]: observed node there is most to the bottom for column x

    vector<NodePtr> frontWidth(height, nullptr); //frontWidht[y]
    vector<NodePtr> frontHeight(width, nullptr);

    vector<NodePtr> result;
    
    for(int y=0; y<height; ++y){
        string line; // width characters, each either 0 or .
        getline(cin, line);
        for(int x=0; x<width; ++x){
        	if( line[x] == '0'){
            	if(frontWidth[y] != nullptr) frontWidth[y]->setRightNeighbor(x);
            	if(frontHeight[x]  != nullptr) frontHeight[x]->setBottomNeighbor(y);

            	NodePtr observedNode(new Node(x, y));
            	result.push_back(observedNode);

            	frontWidth[y] = observedNode;
            	frontHeight[x] = observedNode;
        	}

        }
    }

    for(NodePtr n : result){
    	int rightNeighborX = n->getRightNeighbor();
    	int rightNeighborY = rightNeighborX != -1 ? n->getY() : -1;

    	int bottomNeighborY = n->getBottomNeighbor();
    	int bottomNeighborX = bottomNeighborY != -1 ? n->getX() : -1;

        cout << n->getX() << " " << n->getY() << " " << rightNeighborX << " "  << rightNeighborY << " " << bottomNeighborX << " "  << bottomNeighborY << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
}
