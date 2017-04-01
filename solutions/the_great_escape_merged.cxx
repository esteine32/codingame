//This file was created with Single-C-File
//Single-C-File was developed by Adrian Dawid.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/*
 * Direction.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef DIRECTION_H_
#define DIRECTION_H_
enum class Direction
{
    Right, Left, Up, Down, None
};
#endif /* DIRECTION_H_ */
/*
 * Player.h
 *
 *  Created on: 26 Feb 2017
 *      Author: sbl
 */
#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
class Player {
private:
	int id;
	int x;
	int y;
	int noOfwalls;
public:
	Player() : id(-1), x(-1), y(-1), noOfwalls(-1){}
	Player(int id, int x, int y, int noOfwalls) : id(id), x(x), y(y), noOfwalls(noOfwalls){}
	virtual ~Player();
	int getId() const;
	int getX() const;
	int getY() const;
	int getNoOfwalls() const;
};
typedef std::shared_ptr<Player> PlayerPtr;
#endif /* PLAYER_H_ */
/*
 * Wall.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef WALL_H_
#define WALL_H_
class Wall;
typedef std::shared_ptr<Wall> WallPtr;
class Wall {
    int x;
    int y;
    std::string orientation;
public:
	Wall(int x, int y, std::string o) : x(x), y(y), orientation(o){}
	virtual ~Wall();
	std::string getOrientation() const;
	int getX() const;
	int getY() const;
	bool hasValidCoords();
	bool isPlacingOnOtherWall(const std::vector<WallPtr>& walls);
	static std::vector<WallPtr> getWallsInDirection(int x, int y, const Direction& d);
};
#endif /* WALL_H_ */
/*
 * Node.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef NODE_H_
#define NODE_H_
class Node {
    int x;
    int y;
    Direction connection;
    int costSoFar;
    int estimatedTotalCost;
public:
	Node(int x, int y, Direction c, int csf) : x(x), y(y), connection(c), costSoFar(csf), estimatedTotalCost(0) {}
	virtual ~Node();
	int getX() const;
	int getY() const;
	Direction getConnection() const;
	int getCostSoFar() const;
	void setConnection(Direction connection);
	void setCostSoFar(int costSoFar);
	int getEstimatedTotalCost() const;
	void setEstimatedTotalCost(int estimatedTotalCost);
};
typedef std::shared_ptr<Node> NodePtr;
std::ostream& operator<<(std::ostream &strm, const Node &node);
#endif /* NODE_H_ */
/*
 * Position.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef POSITION_H_
#define POSITION_H_
class Position {
    int x;
    int y;
public:
	Position() : x(0), y(0){}
	virtual ~Position();
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};
typedef std::shared_ptr<Position> PositionPtr;
#endif /* POSITION_H_ */
/*
 * AStarResult.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef ASTAR_H_
#define ASTAR_H_
class AStar {
	PlayerPtr player;
	std::vector<WallPtr> walls;
	int width;
	int height;
    Direction direction;
    int length;
	void algorithm();
	int estimatedCost(NodePtr node);
	NodePtr getNodeWithSmallestEstimatedCost(const std::vector<NodePtr>& nodes);
	NodePtr getNodeOnSamePosition(const std::vector<NodePtr>& nodes, NodePtr node);
	bool isGoalReached(NodePtr node);
	std::vector<NodePtr> getConnections(NodePtr node);
	bool isRightPossible(NodePtr node);
	bool isLeftPossible(NodePtr node);
	bool isDownPossible(NodePtr node);
	bool isUpPossible(NodePtr node);
	Direction reverseDirection(Direction direction);
	NodePtr getFromNode(const std::vector<NodePtr>& closed, NodePtr node);
public:
	AStar(const PlayerPtr player, const std::vector<WallPtr>& walls, int width, int height);
	virtual ~AStar();
	Direction getDirection() const;
	int getLength() const;
};
typedef std::shared_ptr<AStar> AStarPtr;
#endif /* ASTAR_H_ */
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
/*
 * Player.cpp
 *
 *  Created on: 26 Feb 2017
 *      Author: sbl
 */
int Player::getId() const {
	return id;
}
int Player::getX() const {
	return x;
}
int Player::getY() const {
	return y;
}
Player::~Player() {
	// TODO Auto-generated destructor stub
}
/*
 * Wall.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
Wall::~Wall() {
	// TODO Auto-generated destructor stub
}
std::string Wall::getOrientation() const {
	return orientation;
}
int Wall::getX() const {
	return x;
}
int Wall::getY() const {
	return y;
}
bool Wall::hasValidCoords()
{
    if(orientation.compare("H") == 0 && x > -1 && x < 8 && y > 0 && y < 9)
    {
        return true;
    }
    if(orientation.compare("V") == 0 && x > 0 && x < 9 && y > -1 && y < 8)
    {
        return true;
    }
    return false;
}
bool Wall::isPlacingOnOtherWall(const std::vector<WallPtr>& walls)
{
    for(WallPtr w: walls)
    {
        bool sameDirectionFail = false;
        bool otherDirectionFail = false;
        if(orientation.compare("H") == 0){
            sameDirectionFail = w->getOrientation().compare("H") == 0 && y == w->getY() && (x == w->getX()-1 || x == w->getX() || x == w->getX() + 1);
            otherDirectionFail =w->getOrientation().compare("V") == 0 && y == w->getY()+1 && x == w->getX()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        else
        {
            sameDirectionFail = w->getOrientation().compare("V") == 0 && x == w->getX() && (y == w->getY()-1 || y == w->getY() || y == w->getY() + 1);
            otherDirectionFail =w->getOrientation().compare("H") == 0 && x == w->getX()+1 && y == w->getY()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        //cerr << "isPlacingOnOtherWall: " << w.x << " " << w.y << " " << w.orientation  << endl;
    }
    return false;
}
std::vector<WallPtr> Wall::getWallsInDirection(int x, int y, const Direction& d){
    std::vector<WallPtr> walls;
    switch(d)
    {
        case Direction::Up:
            walls.push_back(WallPtr(new Wall(x, y, "H")));
            walls.push_back(WallPtr(new Wall(x-1, y, "H")));
            break;
        case Direction::Down:
            walls.push_back(WallPtr(new Wall(x, y+1, "H")));
            walls.push_back(WallPtr(new Wall(x-1, y+1, "H")));
            break;
        case Direction::Left:
            walls.push_back(WallPtr(new Wall(x, y, "V")));
            walls.push_back(WallPtr(new Wall(x, y-1, "V")));
            break;
        case Direction::Right:
            walls.push_back(WallPtr(new Wall(x+1, y, "V")));
            walls.push_back(WallPtr(new Wall(x+1, y-1, "V")));
            break;
    }
    return walls;
}
/*
 * Node.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
Node::~Node() {
	// TODO Auto-generated destructor stub
}
int Node::getX() const {
	return x;
}
int Node::getY() const {
	return y;
}
Direction Node::getConnection() const {
	return connection;
}
void Node::setConnection(Direction connection) {
	this->connection = connection;
}
int Node::getCostSoFar() const {
	return costSoFar;
}
void Node::setCostSoFar(int costSoFar) {
	this->costSoFar = costSoFar;
}
int Node::getEstimatedTotalCost() const {
	return estimatedTotalCost;
}
void Node::setEstimatedTotalCost(int estimatedTotalCost) {
	this->estimatedTotalCost = estimatedTotalCost;
}
std::ostream& operator<<(std::ostream &strm, const Node &node) {
  return strm << "Node[x="<< node.getX() << ", y=" << node.getY() << ", connection=" << static_cast<std::underlying_type<Direction>::type>(node.getConnection()) << ", costSoFar=" << node.getCostSoFar() << ", estimatedTotalCost=" << node.getEstimatedTotalCost() << "]";
}
/*
 * Direction.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
#ifndef DIRECTION_H_
#define DIRECTION_H_
enum class Direction
{
    Right, Left, Up, Down, None
};
#endif /* DIRECTION_H_ */
/*
 * AStarResult.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
using namespace std;
AStar::AStar(const PlayerPtr player, const std::vector<WallPtr>& walls, int width, int height){
	this->player = player;
	this->walls = walls;
	this->width = width;
	this->height = height;
	this->direction = Direction::None;
	this->length = 0;
	algorithm();
}
AStar::~AStar() {
	// TODO Auto-generated destructor stub
}
void AStar::algorithm()
{
    vector<NodePtr> openNodes;
    vector<NodePtr> closedNodes;
    NodePtr currentNode;
    NodePtr resultNode;
    NodePtr start(new Node(player->getX(), player->getY(), Direction::None, 0));
    start->setEstimatedTotalCost(estimatedCost(start));
    openNodes.push_back(start);
    while(openNodes.size() > 0)
    {
        currentNode = getNodeWithSmallestEstimatedCost(openNodes);
        if(isGoalReached(currentNode))
        {
            break;
        }
        vector<NodePtr> connections = getConnections(currentNode);
        for(NodePtr c : connections)
        {
            NodePtr closedNode = getNodeOnSamePosition(closedNodes, c);
            if(closedNode != nullptr) // is in closed vector
            {
                if(closedNode->getCostSoFar() > c->getCostSoFar()){
                    c->setEstimatedTotalCost(c->getCostSoFar() + (closedNode->getEstimatedTotalCost() - closedNode->getCostSoFar()));
                    closedNodes.erase(std::remove(closedNodes.begin(), closedNodes.end(), closedNode), closedNodes.end());
                    openNodes.push_back(c);
                }
            }else{
            	NodePtr openNode = getNodeOnSamePosition(openNodes, c);
            	if(openNode != nullptr){ // is in open vector
					if(openNode->getCostSoFar() > c->getCostSoFar()){
						openNode->setConnection(c->getConnection());
						openNode->setCostSoFar(c->getCostSoFar());
						openNode->setEstimatedTotalCost(c->getCostSoFar() + (openNode->getEstimatedTotalCost() - openNode->getCostSoFar()));
					}
            	}else{ // not visited before
                    c->setEstimatedTotalCost(c->getCostSoFar() + estimatedCost(c));
                    openNodes.push_back(c);
            	}
            }
        }
        openNodes.erase(std::remove(openNodes.begin(), openNodes.end(), currentNode), openNodes.end());
        closedNodes.push_back(currentNode);
    }
    if(isGoalReached(currentNode))
    {
        while(currentNode->getX() != start->getX() || currentNode->getY() !=start->getY())
        {
            resultNode = currentNode;
            currentNode = getFromNode(closedNodes, currentNode);
            this->length++;
        }
    	this->direction = reverseDirection(resultNode->getConnection());
    }
}
int AStar::estimatedCost(NodePtr node)
{
    switch(player->getId())
    {
        case 0:
            return (width - 1) - node->getX();
        case 1:
            return node->getX();
        case 2:
            return (height - 1) - node->getY();
    }
    return -1;
}
NodePtr AStar::getNodeWithSmallestEstimatedCost(const vector<NodePtr>& nodes)
{
    NodePtr smallestNode = nodes[0];
    int smallestCost = smallestNode->getEstimatedTotalCost();
    for(NodePtr node : nodes){
    	if(node->getEstimatedTotalCost() < smallestCost){
    		smallestNode = node;
    		smallestCost = smallestNode->getEstimatedTotalCost();
    	}
    }
    return smallestNode;
}
NodePtr AStar::getNodeOnSamePosition(const vector<NodePtr>& nodes, NodePtr node)
{
    for(NodePtr n : nodes){
    	if(n->getX() == node->getX() && n->getY() == node->getY()){
    		return n;
    	}
    }
    return nullptr;
}
bool AStar::isGoalReached(NodePtr node)
{
    switch(player->getId())
    {
        case 0:
            return node->getX() == width-1;
        case 1:
            return node->getX() == 0;
        case 2:
            return node->getY() == height -1 ;
    }
    return -1;
}
vector<NodePtr> AStar::getConnections(NodePtr node)
{
    vector<NodePtr> connections;
    //right
    if(isRightPossible(node))
    {
        connections.push_back(NodePtr(new Node(node->getX()+1, node->getY(), Direction::Left, node->getCostSoFar()+1)));
    }
    //left
    if(isLeftPossible(node))
    {
        connections.push_back(NodePtr(new Node(node->getX()-1, node->getY(), Direction::Right, node->getCostSoFar()+1)));
    }
    //down
    if(isDownPossible(node))
    {
        connections.push_back(NodePtr(new Node(node->getX(), node->getY()+1, Direction::Up, node->getCostSoFar()+1)));
    }
    //up
    if(isUpPossible(node))
    {
        connections.push_back(NodePtr(new Node(node->getX(), node->getY()-1, Direction::Down, node->getCostSoFar()+1)));
    }
    return connections;
}
bool AStar::isRightPossible(NodePtr node)
{
    bool possible = node->getX()< width-1;
    for(WallPtr w:walls)
    {
        possible &= (w->getOrientation().compare("V") != 0 || w->getX() != node->getX()+1 || (w->getY() != node->getY() && w->getY() != node->getY()-1));
    }
    return possible;
}
bool AStar::isLeftPossible(NodePtr node)
{
    bool possible = node->getX() > 0;
    for(WallPtr w:walls)
    {
        possible &= (w->getOrientation().compare("V") != 0 || w->getX() != node->getX() || (w->getY() != node->getY() && w->getY() != node->getY()-1));
    }
    return possible;
}
bool AStar::isDownPossible(NodePtr node)
{
    bool possible = node->getY() < height-1;
    for(WallPtr w:walls)
    {
        possible &= (w->getOrientation().compare("H") != 0 || w->getY() != node->getY()+1 || (w->getX() != node->getX() && w->getX() != node->getX()-1));
    }
    return possible;
}
bool AStar::isUpPossible(NodePtr node)
{
    bool possible = node->getY() > 0;
    for(WallPtr w:walls)
    {
        possible &= (w->getOrientation().compare("H") != 0 || w->getY() != node->getY() || (w->getX() != node->getX() && w->getX() != node->getX()-1));
    }
    return possible;
}
Direction AStar::reverseDirection(Direction direction)
{
    switch(direction)
    {
        case Direction::Right:
            return Direction::Left;
        case Direction::Left:
            return Direction::Right;
        case Direction::Up:
            return Direction:: Down;
        case Direction::Down:
            return Direction::Up;
    }
    return Direction::None;
}
NodePtr AStar::getFromNode(const vector<NodePtr>& closed, NodePtr node)
{
    int x;
    int y;
    switch(node->getConnection())
    {
        case Direction::Right:
            x = node->getX() + 1;
            y = node->getY();
            break;
        case Direction::Left:
            x = node->getX() - 1;
            y = node->getY();
            break;
        case Direction::Up:
            x = node->getX();
            y = node->getY() - 1;
            break;
        case Direction::Down:
            x = node->getX();
            y = node->getY() + 1;
            break;
    }
    for(NodePtr c: closed)
    {
        if(c->getX() == x && c->getY() == y)
            return c;
    }
    return node;
}
Direction AStar::getDirection() const {
	return direction;
}
int AStar::getLength() const {
	return length;
}
/*
 * Position.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */
Position::~Position() {
	// TODO Auto-generated destructor stub
}
int Position::getX() const {
	return x;
}
void Position::setX(int x) {
	this->x = x;
}
int Position::getY() const {
	return y;
}
void Position::setY(int y) {
	this->y = y;
}
