#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Player.h"
#include "Wall.h"
#include "AStarResult.h"
#include "Direction.h"
#include "Node.h"
#include "Position.h"

using namespace std;
typedef shared_ptr<Player> PlayerPtr;
typedef shared_ptr<Wall> WallPtr;
typedef shared_ptr<AStarResult> AStarResultPtr;
typedef shared_ptr<Node> NodePtr;
typedef shared_ptr<Position> PositionPtr;


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

PlayerPtr getMyPlayer(const vector<PlayerPtr>& players, int myId){
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

void listWalls(int wallCount, vector<WallPtr> walls)
{
    walls.reserve(wallCount);
    for (int i = 0; i < wallCount; i++) {
        int wallX; // x-coordinate of the wall
        int wallY; // y-coordinate of the wall
        string wallOrientation; // wall orientation ('H' or 'V')
        cin >> wallX >> wallY >> wallOrientation; cin.ignore();
        walls.push_back(WallPtr(new Wall(wallX, wallY, wallOrientation)));
        

    }
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

bool isRightPossible(NodePtr n, const vector<WallPtr>& walls, int width)
{
    bool possible = n->getX()< width-1;
    
    if(possible)
    {
        for(WallPtr w:walls)
        {
            possible &= (w->getOrientation().compare("V") != 0 || w->getX() != n->getX()+1 || (w->getY() != n->getY() && w->getY() != n->getY()-1));
        }
    }
    
    return possible;
}

bool isLeftPossible(NodePtr n, const vector<WallPtr>& walls, int width)
{
    bool possible = n->getX() > 0;

    if(possible)
    {
        for(WallPtr w:walls)
        {
            possible &= (w->getOrientation().compare("V") != 0 || w->getX() != n->getX() || (w->getY() != n->getY() && w->getY() != n->getY()-1));
        }
    }
    
    return possible;
}

bool isDownPossible(NodePtr n, const vector<WallPtr>& walls, int height)
{
    bool possible = n->getY() < height-1;

    if(possible)
    {
        for(WallPtr w:walls)
        {
            possible &= (w->getOrientation().compare("H") != 0 || w->getY() != n->getY()+1 || (w->getX() != n->getX() && w->getX() != n->getX()-1));
        }
    }
    
    return possible;
}

bool isUpPossible(NodePtr n, const vector<WallPtr>& walls, int height)
{
    bool possible = n->getY() > 0;

    if(possible)
    {
        for(WallPtr w:walls)
        {
            possible &= (w->getOrientation().compare("H") != 0 || w->getY() != n->getY() || (w->getX() != n->getX() && w->getX() != n->getX()-1));
        }
    }
    
    return possible;
}

int estimatedCost(PlayerPtr p, NodePtr n, int width, int height)
{
    switch(p->getId())
    {
        case 0:
            return (width - 1) - n->getX();
        case 1:
            return n->getX();
        case 2:
            return (height - 1) - n->getY();
    }

    return -1;
}

int getIndexOfSmallestNode(const vector<NodePtr>& v)
{
    int index = 0;
    int smallestValue = v[index]->getEstimatedTotalCost();
    for(int i = 1; i<v.size(); ++i)
    {
        if(v[i]->getEstimatedTotalCost() < smallestValue)
        {
            index = i;
            smallestValue = v[index]->getEstimatedTotalCost();
        }
    }
    return index;
}

int getIndexOfNode(const vector<NodePtr>& v, NodePtr n)
{
    for(int i = 0; i<v.size(); ++i)
    {
        if(v[i]->getX() == n->getX() && v[i]->getY() == n->getY())
        {
            return i;
        }
    }
    
    return -1;
}

bool isGoalReached(int id, NodePtr n, int width, int height)
{

    switch(id)
    {
        case 0:
            return n->getX() == width-1;
        case 1:
            return n->getX() == 0;
        case 2:
            return n->getY() == height -1 ;
    }

    return -1;
}


vector<NodePtr> getConnections(NodePtr n, const vector<WallPtr>& walls, int width, int height)
{
    vector<NodePtr> connections;
    
    //right
    if(isRightPossible(n, walls, width))
    {
        connections.push_back(NodePtr(new Node(n->getX()+1, n->getY(), Direction::Left, n->getCostSoFar()+1)));
    }
    
    //left
    if(isLeftPossible(n, walls, width))
    {
        connections.push_back(NodePtr(new Node(n->getX()+1, n->getY(), Direction::Right, n->getCostSoFar()+1)));
    }
    
    //down
    if(isDownPossible(n, walls, height))
    {
        connections.push_back(NodePtr(new Node(n->getX(), n->getY()+1, Direction::Up, n->getCostSoFar()+1)));
    }
    
    //up
    if(isUpPossible(n, walls, height))
    {
        connections.push_back(NodePtr(new Node(n->getX(), n->getY()+1, Direction::Down, n->getCostSoFar()+1)));
    }
    
    return connections;
}

NodePtr getFromNode(const vector<NodePtr>& closed, NodePtr n)
{
    //cerr << getMove(n.connection) << endl;
    int x;
    int y;
    switch(n->getConnection())
    {
        case Direction::Right:
            x = n->getX() + 1;
            y = n->getY();
            break;
        case Direction::Left:
            x = n->getX() - 1;
            y = n->getY();
            break;
        case Direction::Up:
            x = n->getX();
            y = n->getY() - 1;
            break;
        case Direction::Down:
            x = n->getX();
            y = n->getY() + 1;
            break;
    }
    
    for(NodePtr c: closed)
    {
        if(c->getX() == x && c->getY() == y)
            return c;
    }
    
    return n;
}

Direction reverseDirection(Direction d)
{
    switch(d)
    {
        case Direction::Right:
            return Direction::Left;
            break;
        case Direction::Left:
            return Direction::Right;
            break;
        case Direction::Up:
            return Direction:: Down;
            break;
        case Direction::Down:
            return Direction::Up;
            break;
    }
    
    return Direction::None;
}



AStarResultPtr aStar(const PlayerPtr p, const vector<WallPtr>& walls, int width, int height)
{
    vector<NodePtr> open;
    vector<NodePtr> closed;

    NodePtr start(new Node(p->getX(), p->getY(), Direction::None, 0));
    start->setEstimatedTotalCost(estimatedCost(p, start, width, height));

    NodePtr current;
    NodePtr resultNode;
    
    open.push_back(start);
    
    while(open.size() > 0)
    {
        //get smallest
        int currentIndex = getIndexOfSmallestNode(open);
        current = open[currentIndex];
        //cerr << "smallest: x=" << current.x << " y=" << current.y << " val=" << current.estimatedTotalCost << endl; 
        if(isGoalReached(p->getId(), current, width, height))
        {
            //cerr << "GOAL" << endl;;
            break;
        }
        vector<NodePtr> connections = getConnections(current, walls, width, height);
        
        for(NodePtr c:connections)
        {
            //closed node
            int closedIndex = getIndexOfNode(closed, c);
            bool onClosedList = false;
            if(closedIndex > -1)
            {
                onClosedList = true;
                if(closed[closedIndex]->getCostSoFar() <= c->getCostSoFar()) continue;
                
                c->setEstimatedTotalCost(c->getCostSoFar() + (closed[closedIndex]->getEstimatedTotalCost() - closed[closedIndex]->getCostSoFar()));
                
                closed.erase(closed.begin() + closedIndex);
                open.push_back(c);
                
            }
            
            //open list
            bool onOpenList = false;
            if(!onClosedList)
            {
                int openIndex = getIndexOfNode(open, c);
                if(openIndex > -1)
                {
                    onOpenList = true;
                    if(open[openIndex]->getCostSoFar() <= c->getCostSoFar()) continue;
                    
                    open[openIndex ]->setConnection(c->getConnection());
                    open[openIndex ]->setCostSoFar(c->getCostSoFar());
                    open[openIndex ]->setEstimatedTotalCost(c->getCostSoFar() + (open[openIndex ]->getEstimatedTotalCost() - open[openIndex]->getCostSoFar()));
                }
            }
            
            //not seen before
            if(!onClosedList && !onOpenList)
            {
                c->setEstimatedTotalCost(c->getCostSoFar() + estimatedCost(p, c, width, height));
                //cerr << "put in open: x=" << c->x << " y=" << c->y << " val=" << c->estimatedTotalCost << endl;
                open.push_back(c);
            }
        }
        
        open.erase(open.begin() + currentIndex);
        closed.push_back(current);
        string closedStr = "";
        for(int i = 0; i<closed.size(); ++i)
        {
            closedStr += "(" + to_string(closed[i]->getX()) + "," + to_string(closed[i]->getY()) + ")";
        }
        //cerr <<  closedStr << endl;
    }
    
    int length = 0;
    if(!isGoalReached(p->getId(), current, width, height))
    {
        return AStarResultPtr(new AStarResult(Direction::None, 0));
    }
    else
    {

        while(current->getX() != start->getX() || current->getY() !=start->getY())
        {
            //cerr << "find path: x=" << current.x << " y=" << current.y << " val=" << current.estimatedTotalCost << endl; 
            resultNode = current;
            current = getFromNode(closed, current);
            length++;
        }
    }
    
    Direction direction = reverseDirection(resultNode->getConnection());
    return AStarResultPtr(new AStarResult(direction, length));
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
        AStarResultPtr a = aStar(p, walls, width, height);
        if(a->getDirection() == Direction::None)
        {
            //cerr << "NoWay" << endl;
            walls.pop_back();
            return false;
        }
    }
    
    AStarResultPtr a = aStar(me, walls, width, height);
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
WallPtr getWallInMovingDirection(const PlayerPtr p, PositionPtr lastPosition)
{
    int pId = p->getId();
    int pX = p->getX();
    int pY = p->getY();

    int x;
    int y;
    string orientation;
    //up
    if(pX == lastPosition->getX() && pY < lastPosition->getY())
    {
        //cerr << "getWallInMovingDirection: " << "up" << endl;
        orientation = "H";
        if(pId == 0)
        {
            x = pX-1;
            y = pY;
        }
        else
        {
            x = pX;
            y = pY;
        }
        return WallPtr(new Wall(x, y, orientation));
    }
    
    //down
    if(pX == lastPosition->getX() && pY > lastPosition->getY())
    {
        //cerr << "getWallInMovingDirection: " << "down" << endl;
        orientation = "H";
        if(pId == 0)
        {
            x = pX-1;
            y = pY+1;
        }
        else
        {
            x = pX;
            y = pY+1;
        }
        return WallPtr(new Wall(x, y, orientation));
    }
    
    //right
    if(pY == lastPosition->getY() && pX > lastPosition->getX())
    {
        //cerr << "getWallInMovingDirection: " << "right" << endl;
        orientation = "V";
        if(pId == 3)
        {
            x = pX+1;
            y = pY-1;
        }
        else
        {
            x = pX+1;
            y = pY;
        }
        return WallPtr(new Wall(x, y, orientation));
    }
    
    //left
    //cerr << "getWallInMovingDirection: " << "left and other" << endl;
    if(pY == lastPosition->getY() && pX < lastPosition->getX())
    {
        orientation = "V";
        if(pId == 3)
        {
            x = pX;
            y = pY-1;
        }
        else
        {
            x = pX;
            y = pY;
        }
        return WallPtr(new Wall(x, y, orientation));
    }
    
    // not valid wall
    x = 0;
    y = 0;
    orientation = "H";
    return WallPtr(new Wall(x, y, orientation));
    
}

WallPtr getWallInGoalDirection(const PlayerPtr p)
{

    int pX = p->getX();
    int pY = p->getY();

    int x;
    int y;
    string orientation;

    switch(p->getId())
    {
        case 0:
            x = pX+1;
            y = pY;
            orientation = "V";
            break;
        case 1:
            x = pX;
            y = pY;
            orientation = "V";
            break;
        case 2:
            x = pX;
            y = pY+1;
            orientation = "H";
            break;
    }
        
    //cerr << p.id << " " << w.x << " " << w.y << " " << w.orientation << endl;
    return WallPtr(new Wall(x, y, orientation));
}

WallPtr getWallInGoalDirectionAccordingToMove(const PlayerPtr p, PositionPtr lastPosition)
{
    int pX = p->getX();
    int pY = p->getY();

    int x = 0;
    int y = 0;
    string orientation;

    switch(p->getId())
    {
        case 0:
            orientation = "V";
            //up
            if(pX == lastPosition->getX() && pY < lastPosition->getY())
            {
                x = pX+1;
                y = pY-1;
            }//down
            else if(pX == lastPosition->getX() && pY > lastPosition->getY())
            {
                x = pX+1;
                y = pY;
            }
            break;
        case 1:
            orientation = "V";
            //up
            if(pX == lastPosition->getX() && pY < lastPosition->getY())
            {
                x = pX;
                y = pY-1;
            }//down
            else if(pX == lastPosition->getX() && pY > lastPosition->getY())
            {
                x = pX;
                y = pY;
            }
            break;
        case 2:
            orientation = "H";
            //left    
            if(pX < lastPosition->getX() && pY == lastPosition->getY())
            {
                x = pX-1;
                y = pY+1;
            }//right
            else if(pX > lastPosition->getX() && pY == lastPosition->getY())
            {
                x = pX;
                y = pY+1;
            }
            break;
    }
    
    return WallPtr(new Wall(x, y, orientation));
}

WallPtr getWallInDirection(const Direction& d, const PlayerPtr p, const vector<PlayerPtr>& opponents, const PlayerPtr me, vector<WallPtr>& walls, int width, int height)
{

    int pX = p->getX();
    int pY = p->getY();

    string orientation;
    int x;
    int y;

    WallPtr w;


    switch(d)
    {
        case Direction::Up:
            orientation = "H";
            x = pX;
            y = pY;
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
            orientation = "H";
            x = pX-1;
            y = pY;
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



//**********************************************attempts**********************************************//

//CORNER
int myWallCount;
int playerIndex;
int wallDescision;
int numberMoves;
vector<PositionPtr> lastPositions;

void initCorner(int playerCount)
{
    playerIndex = playerCount == 2 ? 1 : 2;
    wallDescision = 1;
    numberMoves = 0;

    for(int i = 0; i<playerCount; i++)
    {
        lastPositions.push_back(PositionPtr(new Position()));
    }
}

string corner(int playerCount, const PlayerPtr me, const vector<PlayerPtr>& opponents, int wallCount, vector<WallPtr> walls, int w, int h)
{
    string resultStr = "";
    
    if(myWallCount > 0 && playerIndex % playerCount < opponents.size())
    {
        int opponentIndex = playerIndex % playerCount;
        PlayerPtr opponent = opponents[opponentIndex];
        PositionPtr lastPosition = lastPositions[opponentIndex];
        if(opponent->getX() != lastPosition->getX() || opponent->getY() != lastPosition->getY())
        {
            cerr << "wallDesicion=" << wallDescision << endl; 
            WallPtr newWall;
            if(wallDescision % 3 == 1)
            {
                newWall = getWallInGoalDirection(opponent);
            }
            else if(wallDescision % 3 == 2)
            {
               newWall = getWallInGoalDirectionAccordingToMove(opponent, lastPosition); 
            }
            else
            {
                newWall = getWallInMovingDirection(opponent, lastPosition);
            }
            wallDescision++;

            if(canPlaceWall(walls, newWall, opponents, me, w, h))
            {
                resultStr = getWallStr(newWall);
                myWallCount--;
                
                if(wallDescision % 3 == 1)
                    playerIndex++;
            } 
        }
    }

    if(resultStr.compare("") == 0)
    {
        AStarResultPtr result = aStar(me, walls, w, h);
        resultStr = getMoveStr(result->getDirection());
        
        if(playerIndex % playerCount == opponents.size())
        {
            numberMoves++;
            if(numberMoves % 4 == 0)
            {
                playerIndex++;
            }
            
        }
            
    }
    

    //string move = moveStr;
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    for(int i = 0; i<playerCount; i++)
    {
    	PlayerPtr p = opponents[i];
        lastPositions[i]->setX(p->getX());
        lastPositions[i]->setY(p->getY());
    }
    
    return resultStr;
}

//SHORTEST DIRECTION
void initShortestDirection()
{
    numberMoves = 0;
}

string shortestDirection(int playerCount, const PlayerPtr me, const vector<PlayerPtr>& opponents, int wallCount, vector<WallPtr> walls, int w, int h)
{
    string resultStr = "";
    
    AStarResultPtr myMove = aStar(me, walls, w, h);
    
    if(myWallCount> 0)
    {
        int leaderIndex = 2;
        int shortestPath = myMove->getLength();
        vector<AStarResultPtr> moves;
        
        for(int i = 0; i<opponents.size(); ++i)
        {
            AStarResultPtr move = aStar(opponents[i], walls, w, h);
            moves.push_back(move);
            
            if(move->getLength() < shortestPath)
            {
                leaderIndex = i;
                shortestPath = move->getLength();
            }
        }
        
        if(leaderIndex != 2)
        {
            WallPtr newWall = getWallInDirection(moves[leaderIndex]->getDirection(), opponents[leaderIndex], opponents, me, walls, w, h);

            if(newWall->getX() != 0 || newWall->getY() != 0)
            {
                walls.push_back(newWall);
                
                AStarResultPtr myNewResult = aStar(me, walls, w, h);
                walls.pop_back();
                
                if(myNewResult->getLength() <= myMove->getLength())
                {
                    resultStr = getWallStr(newWall);
                    myWallCount--;
                }
                

            }
        }
    }
    
    if(resultStr.compare("") == 0)
    {

        resultStr = getMoveStr(myMove->getDirection());
        numberMoves++;

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
    
    
    initShortestDirection();
    
    // game loop
    while (1) {

        vector<PlayerPtr> players  = listPlayers(playerCount);;
        PlayerPtr me= getMyPlayer(players, myId);
        if(me == nullptr){
        	cerr << "Own player could not be found" << endl;
        	return -1;
        }
        vector<PlayerPtr> opponents = getOpponents(players, myId);

        int wallCount; // number of walls on the board
        cin >> wallCount; cin.ignore();

        vector<WallPtr> walls;
        listWalls(wallCount, walls);


        string resultStr = shortestDirection(playerCount, me, opponents, wallCount, walls, w, h); 

        cout << resultStr << endl; // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
    }
}

