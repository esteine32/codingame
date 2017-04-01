#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Direction.h"
#include "Player.h"
#include "Wall.h"
#include "Node.h"
#include "Position.h"
#include "AStar.h"


using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



vector<PlayerPtr> listPlayers(int playerCount)
{
    vector<PlayerPtr> players;
    for (int i = 0; i < playerCount; i++) {
        int x; // x-coordinate of the player
        int y; // y-coordinate of the player
        int wallsLeft; // number of walls available for the player
        cin >> x >> y >> wallsLeft; cin.ignore();

        PlayerPtr p(new Player(i, x, y, wallsLeft));
        players.push_back(p);
    }

    return players;
};

PlayerPtr getOwnPlayer(const vector<PlayerPtr>& players, int myId){
	for(int i = 0; i<players.size(); ++i){
		PlayerPtr player = players[i];
		if(player->getId() == myId){
			return player;
		}
	}
	return nullptr;
}

vector<PlayerPtr> getOpponents(const vector<PlayerPtr>& players, int myId){
    vector<PlayerPtr> opponents;

	for(PlayerPtr player : players){
		if(player->getId() != myId){
			opponents.push_back(player);
		}
	}

	return opponents;
}

vector<WallPtr> getWalls()
{
    int wallCount; // number of walls on the board
    cin >> wallCount; cin.ignore();

    vector<WallPtr> walls;
    for (int i = 0; i < wallCount; i++) {
        int wallX; // x-coordinate of the wall
        int wallY; // y-coordinate of the wall
        string wallOrientation; // wall orientation ('H' or 'V')
        cin >> wallX >> wallY >> wallOrientation; cin.ignore();
        walls.push_back(WallPtr(new Wall(wallX, wallY, wallOrientation)));
        

    }

    return walls;
}

string getMoveStr(Direction d)
{
    switch(d)
    {
        case Direction::Right:
            return "RIGHT";
            break;
        case Direction::Left:
            return "LEFT";
            break;
        case Direction::Up:
            return "UP";
            break;
        case Direction::Down:
            return "DOWN";
            break;
    }
    
    return "FAIL";
}

string getWallStr(WallPtr w)
{
    return to_string(w->getX()) + " " + to_string(w->getY()) + " " + w->getOrientation();
}

int myWallCount;

string shortestDirection(const PlayerPtr ownPlayer, const vector<PlayerPtr>& opponents, vector<WallPtr> walls, int w, int h)
{
    AStarPtr ownMove(new AStar(ownPlayer, walls, w, h));

    WallPtr wallToPlace = nullptr;
    
    //check whether wall should be placed
    if(myWallCount > 0)
    {
        vector<AStarPtr> moves;
        
        for(PlayerPtr opponent : opponents){
        	moves.push_back(AStarPtr(new AStar(opponent, walls, w, h)));
        }

        int bestDecreaseDiffLength = 0;
        for(int i = 0; i < opponents.size(); ++i){
        	PlayerPtr opponent = opponents[i];
        	AStarPtr opponentMove = moves[i];

        	if(opponentMove->getLength() < ownMove->getLength()){
            	int diffLength = ownMove->getLength() - opponentMove->getLength();

            	vector<WallPtr> newWalls = Wall::getWallsInDirection(opponent->getX(), opponent->getY(), opponentMove->getDirection());

            	for(WallPtr newWall : newWalls){
            		if(newWall->hasValidCoords() && !newWall->isPlacingOnOtherWall(walls)){
                        walls.push_back(newWall);

                        AStarPtr ownNewMove(new AStar(ownPlayer, walls, w, h));
                        AStarPtr opponentNewMove(new AStar(opponent, walls, w, h));

                        if(ownNewMove->getDirection() != Direction::None && opponentNewMove->getDirection() != Direction::None){
                            int newDiffLength = ownNewMove->getLength() - opponentNewMove->getLength();
                            int decreaseDiffLength = diffLength - newDiffLength;

                            if(decreaseDiffLength > bestDecreaseDiffLength)
                            {
                            	bestDecreaseDiffLength = decreaseDiffLength;
                            	wallToPlace = newWall;
                            }
                        }
                        walls.pop_back();
            		}
            	}
        	}
        }
    }

    string resultStr = "";
    if(wallToPlace == nullptr)
    {
        resultStr = getMoveStr(ownMove->getDirection());
    }
    else{
        resultStr = getWallStr(wallToPlace);
        myWallCount--;
    }
    
    return resultStr;
}


int main()
{
    int w; // width of the board
    int h; // height of the board
    int playerCount; // number of players (2 or 3)
    int myId; // id of my player (0 = 1st player, 1 = 2nd player, ...)
    cin >> w >> h >> playerCount >> myId; cin.ignore();
    
    myWallCount = playerCount == 2 ? 10 : 6;

    // game loop
    while (1) {

        vector<PlayerPtr> players  = listPlayers(playerCount);;
        PlayerPtr ownPlayer = getOwnPlayer(players, myId);
        if(ownPlayer == nullptr){
        	cerr << "Own player could not be found" << endl;
        	return -1;
        }
        vector<PlayerPtr> opponents = getOpponents(players, myId);

        vector<WallPtr> walls = getWalls();

        string resultStr = shortestDirection(ownPlayer, opponents, walls, w, h);

        cout << resultStr << endl; // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
    }
}

