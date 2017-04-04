/*
 * Node.cpp
 *
 *  Created on: 4 Apr 2017
 *      Author: sbl
 */

#include "Node.h"

Node::~Node() {
	// TODO Auto-generated destructor stub
}


int Node::getX() const {
	return x;
}

int Node::getY() const {
	return y;
}

int Node::getRightNeighbor() const {
	return rightNeighbor;
}

void Node::setRightNeighbor(int rightNeighbor) {
	this->rightNeighbor = rightNeighbor;
}


int Node::getBottomNeighbor() const {
	return bottomNeighbor;
}

void Node::setBottomNeighbor(int bottomNeighbor) {
	this->bottomNeighbor = bottomNeighbor;
}

std::ostream& operator<<(std::ostream &strm, const Node &node) {
  return strm << "Node[x="<< node.getX() << ", y=" << node.getY() << ", rightNeighbor=" << node.getRightNeighbor() << ", bottomNeighbor=" << node.getBottomNeighbor() << "]";
}




