/*
 * Node.cpp
 *
 *  Created on: 19 Mar 2017
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




