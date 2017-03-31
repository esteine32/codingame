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


bool isPlacingOnOtherWall(const vector<WallPtr>& walls, const WallPtr& newWall)
{

    for(WallPtr w: walls)
    {
        bool sameDirectionFail = false;
        bool otherDirectionFail = false;
        if(newWall->getOrientation().compare("H") == 0){
            sameDirectionFail = w->getOrientation().compare("H") == 0 && newWall->getY() == w->getY() && (newWall->getX() == w->getX()-1 || newWall->getX() == w->getX() || newWall->getX() == w->getX() + 1);
            otherDirectionFail =w->getOrientation().compare("V") == 0 && newWall->getY() == w->getY()+1 && newWall->getX() == w->getX()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        else
        {
            sameDirectionFail = w->getOrientation().compare("V") == 0 && newWall->getX() == w->getX() && (newWall->getY() == w->getY()-1 || newWall->getY() == w->getY() || newWall->getY() == w->getY() + 1);
            otherDirectionFail =w->getOrientation().compare("H") == 0 && newWall->getX() == w->getX()+1 && newWall->getY() == w->getY()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        //cerr << "isPlacingOnOtherWall: " << w.x << " " << w.y << " " << w.orientation  << endl;
    }
    return false;
}

bool wallHasValidCoords(const WallPtr& w)
{
    if(w->getOrientation().compare("H") == 0 && w->getX() > -1 && w->getX() < 8 && w->getY() > 0 && w->getY() < 9)
    {
        return true;
    }
    
    if(w->getOrientation().compare("V") == 0 && w->getX() > 0 && w->getX() < 9 && w->getY() > -1 && w->getY() < 8)
    {
        return true;
    }
    
    return false;
}



bool canPlaceWall(vector<WallPtr>& walls, const WallPtr& newWall, const vector<PlayerPtr>& opponents, const PlayerPtr me, int width, int height)
{
    if(!wallHasValidCoords(newWall))
    {
        //cerr << "notValidCoords" << endl;
        return false;    
    }
    
    if(isPlacingOnOtherWall(walls, newWall))
    {
        //cerr << "isPlacingOnOtherWall" << endl;
        return false;
    }

    walls.push_back(newWall);
    for(PlayerPtr p: opponents)
    {
        AStarPtr a(new AStar(p, walls, width, height));
        if(a->getDirection() == Direction::None)
        {
            //cerr << "NoWay" << endl;
            walls.pop_back();
            return false;
        }
    }
    
    AStarPtr a(new AStar(me, walls, width, height));
    if(a->getDirection() == Direction::None)
    {
        //cerr << "NoWay" << endl;
        walls.pop_back();
        return false;
    }   
    
    //cerr << "go with the wall" << endl;
    walls.pop_back();
    return true;
}

string getWallStr(WallPtr w)
{
    return to_string(w->getX()) + " " + to_string(w->getY()) + " " + w->getOrientation();
}

WallPtr getWallInDirection(const Direction& d, const PlayerPtr p, const vector<PlayerPtr>& opponents, const PlayerPtr me, vector<WallPtr>& walls, int width, int height)
{

    int pX = p->getX();
    int pY = p->getY();

    string orientation = "";
    int x;
    int y;

    WallPtr w;

    switch(d)
    {
        case Direction::Up:
            x = pX;
            y = pY;
            orientation = "H";
            break;
        case Direction::Down:
            x = pX;
            y = pY+1;
            orientation = "H";
            break;
        case Direction::Left:
            x = pX;
            y = pY;
            orientation = "V";
            break;
        case Direction::Right:
            x = pX+1;
            y = pY;
            orientation = "V";
            break;
    }
    w = WallPtr(new Wall(x, y, orientation));

    if(canPlaceWall(walls, w, opponents, me, width, height))
        return w;
            
    switch(d)
    {
        case Direction::Up:
            x = pX-1;
            y = pY;
            orientation = "H";
            break;
        case Direction::Down:
            x = pX-1;
            y = pY+1;
            orientation = "H";
            break;
        case Direction::Left:
            x = pX;
            y = pY-1;
            orientation = "V";
            break;
        case Direction::Right:
            x = pX+1;
            y = pY-1;
            orientation = "V";
            break;
    }

    w = WallPtr(new Wall(x, y, orientation));

    if(canPlaceWall(walls, w, opponents, me, width, height))
        return w;
            
    w = WallPtr(new Wall(0, 0, orientation));

    return w;
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

                WallPtr newWall = getWallInDirection(opponentMove->getDirection(), opponent, opponents, ownPlayer, walls, w, h);

                if(newWall->getX() != 0 || newWall->getY() != 0)
                {
                    walls.push_back(newWall);

                    AStarPtr ownNewMove(new AStar(ownPlayer, walls, w, h));
                    AStarPtr opponentNewMove(new AStar(opponent, walls, w, h));

                    int newDiffLength = ownNewMove->getLength() - opponentNewMove->getLength();
                    int decreaseDiffLength = diffLength - newDiffLength;

                    if(decreaseDiffLength > bestDecreaseDiffLength)
                    {
                    	bestDecreaseDiffLength = decreaseDiffLength;
                    	wallToPlace = newWall;
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

