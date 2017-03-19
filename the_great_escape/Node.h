/*
 * Node.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#ifndef NODE_H_
#define NODE_H_

#include "Direction.h"

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

#endif /* NODE_H_ */
