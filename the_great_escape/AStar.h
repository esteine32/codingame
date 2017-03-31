/*
 * AStarResult.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include <iostream>
#include <vector>
#include <memory>

#include "Direction.h"
#include "Player.h"
#include "Wall.h"
#include "Node.h"

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
