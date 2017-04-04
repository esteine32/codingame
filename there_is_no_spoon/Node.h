/*
 * Node.h
 *
 *  Created on: 4 Apr 2017
 *      Author: sbl
 */

#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <iostream>

class Node {
	int x;
	int y;
	int rightNeighbor;
	int bottomNeighbor;
public:
	Node(int x, int y) : x(x), y(y), rightNeighbor(-1), bottomNeighbor(-1) {}
	virtual ~Node();
	int getX() const;
	int getY() const;
	int getRightNeighbor() const;
	void setRightNeighbor(int rightNeighbor);
	int getBottomNeighbor() const;
	void setBottomNeighbor(int bottomNeighbor);
};

typedef std::shared_ptr<Node> NodePtr;

std::ostream& operator<<(std::ostream &strm, const Node &node);

#endif /* NODE_H_ */
