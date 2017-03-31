/*
 * AStarResult.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#include "AStar.h"

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




