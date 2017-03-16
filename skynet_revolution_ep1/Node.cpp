/*
 * Node.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */

#include <iostream>

#include "Node.h"

Node::~Node() {
}

int Node::getNumber() const {
	return number;
}

State Node::getState() const {
	return state;
}

void Node::setState(State state) {
	this->state = state;
}


int Node::getPredecessor() const {
	return predecessor;
}

void Node::setPredecessor(int predecessor) {
	this->predecessor = predecessor;
}

int Node::getDistance() const {
	return distance;
}

void Node::setDistance(int distance) {
	this->distance = distance;
}

const std::vector<int>& Node::getAdjacentNodes() const {
	return adjacentNodes;
}

void Node::addAdjacentNode(int nodeNumber){
	this->adjacentNodes.push_back(nodeNumber);
}

void Node::removeAdjacentNode(int nodeNumber){
	adjacentNodes.erase(std::remove(adjacentNodes.begin(), adjacentNodes.end(), nodeNumber), adjacentNodes.end());
}

void Node::reset(){
	state = defaultState;
	predecessor = defaultPredecessor;
	distance = defaultDistance;
}

std::ostream& operator<<(std::ostream &strm, const Node &node) {
  std::vector<int> adjacentNodes = node.getAdjacentNodes();
  std::stringstream ss;
  ss << "[";
  for(std::vector<int>::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); ++it){
	  if(it != adjacentNodes.begin()) ss << ",";
	  ss << *it;
  }
  ss << "]";


  return strm << "Node[number="<< node.getNumber() << ", predecessor=" << node.getPredecessor() << ", distance="<< node.getDistance() << ", adjacentNodes=" << ss.str() << "]";
}
