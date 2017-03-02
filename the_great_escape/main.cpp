#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Player.h"

using namespace std;
typedef shared_ptr<Player> PlayerPtr;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
enum Direction
{
    Right, Left, Up, Down, None
};


struct Wall
{
    int x;
    int y;
    string orientation;
};

struct Node
{
    int x;
    int y;
    Direction connection;
    int costSoFar;
    int estimatedTotalCost;
};

struct AStarResult
{
    Direction direction;
    int length;
};

struct Position
{
    int x;
    int y;
};

enum Action
{
    Walk, PlaceWall    
};

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

void listWalls(int wallCount, vector<Wall>& walls)
{
    walls.reserve(wallCount);
    for (int i = 0; i < wallCount; i++) {
        int wallX; // x-coordinate of the wall
        int wallY; // y-coordinate of the wall
        string wallOrientation; // wall orientation ('H' or 'V')
        cin >> wallX >> wallY >> wallOrientation; cin.ignore();
        Wall w;
        w.x = wallX;
        w.y = wallY;
        w.orientation = wallOrientation;
        walls.push_back(w);
        

    }
}

string getMoveStr(Direction d)
{
    switch(d)
    {
        case Right:
            return "RIGHT";
            break;
        case Left:
            return "LEFT";
            break;
        case Up:
            return "UP";
            break;
        case Down:
            return "DOWN";
            break;
    }
    
    return "FAIL";
}

bool isRightPossible(const Node& n, const vector<Wall>& walls, int width)
{
    bool possible = n.x < width-1;
    
    if(possible)
    {
        for(Wall w:walls)
        {
            possible &= (w.orientation.compare("V") != 0 || w.x != n.x+1 || (w.y != n.y && w.y != n.y-1));
        }
    }
    
    return possible;
}

bool isLeftPossible(const Node& n, const vector<Wall>& walls, int width)
{
    bool possible = n.x > 0;

    if(possible)
    {
        for(Wall w:walls)
        {
            possible &= (w.orientation.compare("V") != 0 || w.x != n.x || (w.y != n.y && w.y != n.y-1));
        }
    }
    
    return possible;
}

bool isDownPossible(const Node& n, const vector<Wall>& walls, int height)
{
    bool possible = n.y < height-1;

    if(possible)
    {
        for(Wall w:walls)
        {
            possible &= (w.orientation.compare("H") != 0 || w.y != n.y+1 || (w.x != n.x && w.x != n.x-1));
        }
    }
    
    return possible;
}

bool isUpPossible(const Node& n, const vector<Wall>& walls, int height)
{
    bool possible = n.y > 0;

    if(possible)
    {
        for(Wall w:walls)
        {
            possible &= (w.orientation.compare("H") != 0 || w.y != n.y || (w.x != n.x && w.x != n.x-1));
        }
    }
    
    return possible;
}

int estimatedCost(PlayerPtr p, const Node& n, int width, int height)
{
    switch(p->getId())
    {
        case 0:
            return (width - 1) - n.x;
        case 1:
            return n.x;
        case 2:
            return (height - 1) - n.y;
    }

    return -1;
}

int getIndexOfSmallestNode(const vector<Node>& v)
{
    int index = 0;
    int smallestValue = v[index].estimatedTotalCost;
    for(int i = 1; i<v.size(); ++i)
    {
        if(v[i].estimatedTotalCost < smallestValue)
        {
            index = i;
            smallestValue = v[index].estimatedTotalCost;
        }
    }
    return index;
}

int getIndexOfNode(const vector<Node>& v, const Node& n)
{
    for(int i = 0; i<v.size(); ++i)
    {
        if(v[i].x == n.x && v[i].y == n.y)
        {
            return i;
        }
    }
    
    return -1;
}

bool isGoalReached(int id, const Node& n, int width, int height)
{

    switch(id)
    {
        case 0:
            return n.x == width-1;
        case 1:
            return n.x == 0;
        case 2:
            return n.y == height -1 ;
    }

    return -1;
}


vector<Node*> getConnections(const Node& n, const vector<Wall>& walls, int width, int height)
{
    vector<Node*> connections;
    
    //right
    if(isRightPossible(n, walls, width))
    {
        Node* nn = new Node();
        nn->x = n.x +1;
        nn->y = n.y;
        nn->connection = Left;
        nn->costSoFar = n.costSoFar + 1;
        connections.push_back(nn);
    }
    
    //left
    if(isLeftPossible(n, walls, width))
    {
        Node* nn = new Node();
        nn->x = n.x - 1;
        nn->y = n.y;
        nn->connection = Right;
        nn->costSoFar = n.costSoFar + 1;
        connections.push_back(nn);
    }
    
    //down
    if(isDownPossible(n, walls, height))
    {
        Node* nn = new Node();
        nn->x = n.x;
        nn->y = n.y + 1;
        nn->connection = Up;
        nn->costSoFar = n.costSoFar + 1;
        connections.push_back(nn);
    }
    
    //up
    if(isUpPossible(n, walls, height))
    {
        Node* nn = new Node();
        nn->x = n.x;
        nn->y = n.y - 1;
        nn->connection = Down;
        nn->costSoFar = n.costSoFar + 1;
        connections.push_back(nn);
    }
    
    return connections;
}

Node getFromNode(const vector<Node> closed, const Node& n)
{
    //cerr << getMove(n.connection) << endl;
    int x;
    int y;
    switch(n.connection)
    {
        case Right:
            x = n.x + 1;
            y = n.y;
            break;
        case Left:
            x = n.x - 1;
            y = n.y;
            break;
        case Up:
            x = n.x;
            y = n.y - 1;
            break;
        case Down:
            x = n.x;
            y = n.y + 1;
            break;
    }
    
    for(Node c: closed)
    {
        if(c.x == x && c.y == y)
            return c;
    }
    
    return n;
}

Direction reverseDirection(Direction d)
{
    switch(d)
    {
        case Right:
            return Left;
            break;
        case Left:
            return Right;
            break;
        case Up:
            return Down;
            break;
        case Down:
            return Up;
            break;
    }
    
    return None;
}



AStarResult aStar(const PlayerPtr p, const vector<Wall>& walls, int width, int height)
{
    vector<Node> open;
    vector<Node> closed;
    
    Node start;
    start.x = p->getX();
    start.y = p->getY();
    start.connection = None;
    start.costSoFar = 0;
    start.estimatedTotalCost = estimatedCost(p, start, width, height);

    Node current;
    Node resultNode;
    
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
        vector<Node*> connections = getConnections(current, walls, width, height);
        
        for(Node *c:connections)
        {
            //closed node
            int closedIndex = getIndexOfNode(closed, *c);
            bool onClosedList = false;
            if(closedIndex > -1)
            {
                onClosedList = true;
                if(closed[closedIndex].costSoFar <= c->costSoFar) continue;
                
                c->estimatedTotalCost = c->costSoFar + (closed[closedIndex].estimatedTotalCost - closed[closedIndex].costSoFar);
                
                closed.erase(closed.begin() + closedIndex);
                open.push_back(*c);
                
            }
            
            //open list
            bool onOpenList = false;
            if(!onClosedList)
            {
                int openIndex = getIndexOfNode(open, *c);
                if(openIndex > -1)
                {
                    onOpenList = true;
                    if(open[openIndex].costSoFar <= c->costSoFar) continue;
                    
                    open[openIndex ].connection = c->connection;
                    open[openIndex ].costSoFar = c->costSoFar;
                    open[openIndex ].estimatedTotalCost = c->costSoFar + (open[openIndex ].estimatedTotalCost - open[openIndex].costSoFar);
                }
            }
            
            //not seen before
            if(!onClosedList && !onOpenList)
            {
                c->estimatedTotalCost = c->costSoFar + estimatedCost(p, *c, width, height);
                //cerr << "put in open: x=" << c->x << " y=" << c->y << " val=" << c->estimatedTotalCost << endl;
                open.push_back(*c);
            }
        }
        
        open.erase(open.begin() + currentIndex);
        closed.push_back(current);
        string closedStr = "";
        for(int i = 0; i<closed.size(); ++i)
        {
            closedStr += "(" + to_string(closed[i].x) + "," + to_string(closed[i].y) + ")";
        }
        //cerr <<  closedStr << endl;
    }
    
    AStarResult result;
    int length = 0;
    if(!isGoalReached(p->getId(), current, width, height))
    {
        result.direction = None;
        result.length = 0;
        return result;
    }
    else
    {

        while(current.x != start.x || current.y!=start.y)
        {
            //cerr << "find path: x=" << current.x << " y=" << current.y << " val=" << current.estimatedTotalCost << endl; 
            resultNode = current;
            current = getFromNode(closed, current);
            length++;
        }
    }
    
    result.direction = reverseDirection(resultNode.connection);
    result.length = length;
    return result;
}

bool isPlacingOnOtherWall(const vector<Wall>& walls, const Wall& newWall)
{

    for(Wall w: walls)
    {
        bool sameDirectionFail = false;
        bool otherDirectionFail = false;
        if(newWall.orientation.compare("H") == 0){
            sameDirectionFail = w.orientation.compare("H") == 0 && newWall.y == w.y && (newWall.x == w.x-1 || newWall.x == w.x || newWall.x == w.x + 1);
            otherDirectionFail =w.orientation.compare("V") == 0 && newWall.y == w.y+1 && newWall.x == w.x-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        else
        {
            sameDirectionFail = w.orientation.compare("V") == 0 && newWall.x == w.x && (newWall.y == w.y-1 || newWall.y == w.y || newWall.y == w.y + 1);
            otherDirectionFail =w.orientation.compare("H") == 0 && newWall.x == w.x+1 && newWall.y == w.y-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        //cerr << "isPlacingOnOtherWall: " << w.x << " " << w.y << " " << w.orientation  << endl;
    }
    return false;
}

bool wallHasValidCoords(const Wall& w)
{
    if(w.orientation.compare("H") == 0 && w.x > -1 && w.x < 8 && w.y > 0 && w.y < 9)
    {
        return true;
    }
    
    if(w.orientation.compare("V") == 0 && w.x > 0 && w.x < 9 && w.y > -1 && w.y < 8)
    {
        return true;
    }
    
    return false;
}



bool canPlaceWall(vector<Wall>& walls, const Wall& newWall, const vector<PlayerPtr>& opponents, const PlayerPtr me, int width, int height)
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
        AStarResult a = aStar(p, walls, width, height);
        if(a.direction == None)
        {
            //cerr << "NoWay" << endl;
            walls.pop_back();
            return false;
        }
    }
    
    AStarResult a = aStar(me, walls, width, height);
    if(a.direction == None)
    {
        //cerr << "NoWay" << endl;
        walls.pop_back();
        return false;
    }   
    
    //cerr << "go with the wall" << endl;
    walls.pop_back();
    return true;
}

string getWallStr(Wall w)
{
    return to_string(w.x) + " " + to_string(w.y) + " " + w.orientation;
}
Wall getWallInMovingDirection(const PlayerPtr p, const Position& lastPosition)
{
    Wall w;

    int pId = p->getId();
    int pX = p->getX();
    int pY = p->getY();
    //up
    if(pX == lastPosition.x && pY < lastPosition.y)
    {
        //cerr << "getWallInMovingDirection: " << "up" << endl;
        w.orientation = "H";
        if(pId == 0)
        {
            w.x = pX-1;
            w.y = pY;
        }
        else
        {
            w.x = pX;
            w.y = pY;
        }
        return w;
    }
    
    //down
    if(pX == lastPosition.x && pY > lastPosition.y)
    {
        //cerr << "getWallInMovingDirection: " << "down" << endl;
        w.orientation = "H";
        if(pId == 0)
        {
            w.x = pX-1;
            w.y = pY+1;
        }
        else
        {
            w.x = pX;
            w.y = pY+1;
        }
        return w;
    }
    
    //right
    if(pY == lastPosition.y && pX > lastPosition.x)
    {
        //cerr << "getWallInMovingDirection: " << "right" << endl;
        w.orientation = "V";
        if(pId == 3)
        {
            w.x = pX+1;
            w.y = pY-1;
        }
        else
        {
            w.x = pX+1;
            w.y = pY;
        }
        return w;
    }
    
    //left
    //cerr << "getWallInMovingDirection: " << "left and other" << endl;
    if(pY == lastPosition.y && pX < lastPosition.x)
    {
        w.orientation = "V";
        if(pId == 3)
        {
            w.x = pX;
            w.y = pY-1;
        }
        else
        {
            w.x = pX;
            w.y = pY;
        }
        return w;
    }
    
    // not valid wall
    w.x = 0;
    w.y = 0;
    w.orientation = "H";
    return w;
    
}

Wall getWallInGoalDirection(const PlayerPtr p)
{
    Wall w;

    int pX = p->getX();
    int pY = p->getY();

    switch(p->getId())
    {
        case 0:
            w.x = pX+1;
            w.y = pY;
            w.orientation = "V";            
            break;
        case 1:
            w.x = pX;
            w.y = pY;
            w.orientation = "V";
            break;
        case 2:
            w.x = pX;
            w.y = pY+1;
            w.orientation = "H";
            break;
    }
        
    //cerr << p.id << " " << w.x << " " << w.y << " " << w.orientation << endl;
    return w;
}

Wall getWallInGoalDirectionAccordingToMove(const PlayerPtr p, const Position& lastPosition)
{
    Wall w;
    w.x = 0;
    w.y = 0;

    int pX = p->getX();
    int pY = p->getY();

    switch(p->getId())
    {
        case 0:
            w.orientation = "V";
            //up
            if(pX == lastPosition.x && pY < lastPosition.y)
            {
                w.x = pX+1;
                w.y = pY-1;
            }//down
            else if(pX == lastPosition.x && pY > lastPosition.y)
            {
                w.x = pX+1;
                w.y = pY;
            }
            break;
        case 1:
            w.orientation = "V";
            //up
            if(pX == lastPosition.x && pY < lastPosition.y)
            {
                w.x = pX;
                w.y = pY-1;
            }//down
            else if(pX == lastPosition.x && pY > lastPosition.y)
            {
                w.x = pX;
                w.y = pY;
            }
            break;
        case 2:
            w.orientation = "H";
            //left    
            if(pX < lastPosition.x && pY == lastPosition.y)
            {
                w.x = pX-1;
                w.y = pY+1;
            }//right
            else if(pX > lastPosition.x && pY == lastPosition.y)
            {
                w.x = pX;
                w.y = pY+1;
            }
            break;
    }
    
    return w;
}

Wall getWallInDirection(const Direction& d, const PlayerPtr p, const vector<PlayerPtr>& opponents, const PlayerPtr me, vector<Wall>& walls, int width, int height)
{
    Wall w;

    int pX = p->getX();
    int pY = p->getY();

    switch(d)
    {
        case Up:
            w.orientation = "H";
            w.x = pX;
            w.y = pY;
            break;
        case Down:
            w.x = pX;
            w.y = pY+1;
            w.orientation = "H";
            break;
        case Left:
            w.x = pX;
            w.y = pY;
            w.orientation = "V";
            break;
        case Right:
            w.x = pX+1;
            w.y = pY;
            w.orientation = "V";
            break;
    }   
    if(canPlaceWall(walls, w, opponents, me, width, height))
        return w;
            
    switch(d)
    {
        case Up:
            w.orientation = "H";
            w.x = pX-1;
            w.y = pY;
            break;
        case Down:
            w.x = pX-1;
            w.y = pY+1;
            w.orientation = "H";
            break;
        case Left:
            w.x = pX;
            w.y = pY-1;
            w.orientation = "V";
            break;
        case Right:
            w.x = pX+1;
            w.y = pY-1;
            w.orientation = "V";
            break;
    }
        
    if(canPlaceWall(walls, w, opponents, me, width, height))
        return w;
            
    w.x = 0;
    w.y = 0;
    return w;
}



//**********************************************attempts**********************************************//

//CORNER
int myWallCount;
int playerIndex;
int wallDescision;
int numberMoves;
vector<Position> lastPositions;

void initCorner(int playerCount)
{
    playerIndex = playerCount == 2 ? 1 : 2;
    wallDescision = 1;
    numberMoves = 0;

    for(int i = 0; i<playerCount; i++)
    {
        Position p;
        lastPositions.push_back(p);
    }
}

string corner(int playerCount, const PlayerPtr me, const vector<PlayerPtr>& opponents, int wallCount, vector<Wall> walls, int w, int h)
{
    string resultStr = "";
    
    if(myWallCount > 0 && playerIndex % playerCount < opponents.size())
    {
        int opponentIndex = playerIndex % playerCount;
        PlayerPtr opponent = opponents[opponentIndex];
        Position lastPosition = lastPositions[opponentIndex];
        if(opponent->getX() != lastPosition.x || opponent->getY() != lastPosition.y)
        {
            cerr << "wallDesicion=" << wallDescision << endl; 
            Wall newWall;
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
        AStarResult result = aStar(me, walls, w, h);
        resultStr = getMoveStr(result.direction);
        
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
        lastPositions[i].x = p->getX();
        lastPositions[i].y = p->getY();
    }
    
    return resultStr;
}

//SHORTEST DIRECTION
void initShortestDirection()
{
    numberMoves = 0;
}

string shortestDirection(int playerCount, const PlayerPtr me, const vector<PlayerPtr>& opponents, int wallCount, vector<Wall> walls, int w, int h)
{
    string resultStr = "";
    
    AStarResult myMove = aStar(me, walls, w, h);
    
    if(myWallCount> 0)
    {
        int leaderIndex = 2;
        int shortestPath = myMove.length;
        vector<AStarResult> moves;
        
        for(int i = 0; i<opponents.size(); ++i)
        {
            AStarResult move = aStar(opponents[i], walls, w, h);
            moves.push_back(move);
            
            if(move.length < shortestPath)
            {
                leaderIndex = i;
                shortestPath = move.length;
            }
        }
        
        if(leaderIndex != 2)
        {
            Wall newWall = getWallInDirection(moves[leaderIndex].direction, opponents[leaderIndex], opponents, me, walls, w, h);

            if(newWall.x != 0 || newWall.y != 0)
            {
                walls.push_back(newWall);
                
                AStarResult myNewResult = aStar(me, walls, w, h);
                walls.pop_back();
                
                if(myNewResult.length <= myMove.length)
                {
                    resultStr = getWallStr(newWall);
                    myWallCount--;
                }
                

            }
        }
    }
    
    if(resultStr.compare("") == 0)
    {

        resultStr = getMoveStr(myMove.direction);
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

        vector<Wall> walls;
        listWalls(wallCount, walls);


        string resultStr = shortestDirection(playerCount, me, opponents, wallCount, walls, w, h); 

        cout << resultStr << endl; // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
    }
}

