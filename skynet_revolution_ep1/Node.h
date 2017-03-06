/*
 * Node.h
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */

#ifndef NODE_H_
#define NODE_H_

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
public:
	Node(int n) : number(n), state(State::UNDESCOVERED), predecessor(-1), distance(-1){}
	virtual ~Node();

	int getNumber() const;
	State getState() const;
	void setState(State state);
	int getPredecessor() const;
	void setPredecessor(int predecessor);
	int getDistance() const;
	void setDistance(int distance);
};

#endif /* NODE_H_ */
