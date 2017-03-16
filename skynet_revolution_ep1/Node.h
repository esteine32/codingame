/*
 * Node.h
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <algorithm>
#include <sstream>

enum class State{
	UNDESCOVERED,
	DESCOVERED,
	PROCESSED
};

class Node {
	int number;
	State state;
	int predecessor;
	int distance;
	std::vector<int> adjacentNodes;

	const static State defaultState = State::UNDESCOVERED;
	const static int defaultPredecessor = -1;
	const static int defaultDistance = -1;
public:
	Node(int n) : number(n), state(defaultState), predecessor(defaultPredecessor), distance(defaultDistance){}
	virtual ~Node();

	int getNumber() const;
	State getState() const;
	void setState(State state);
	int getPredecessor() const;
	void setPredecessor(int predecessor);
	int getDistance() const;
	void setDistance(int distance);
	const std::vector<int>& getAdjacentNodes() const;
	void addAdjacentNode(int nodeNumber);
	void removeAdjacentNode(int nodeNumber);
	void reset();
};

std::ostream& operator<<(std::ostream &strm, const Node &node);



#endif /* NODE_H_ */
