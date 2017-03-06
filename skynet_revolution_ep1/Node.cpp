/*
 * Node.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */

#include "Node.h"

int Node::getNumber() const {
	return number;
}

int Node::getDistance() const {
	return distance;
}

void Node::setDistance(int distance) {
	this->distance = distance;
}

int Node::getPredecessor() const {
	return predecessor;
}

void Node::setPredecessor(int predecessor) {
	this->predecessor = predecessor;
}

State Node::getState() const {
	return state;
}

void Node::setState(State state) {
	this->state = state;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

