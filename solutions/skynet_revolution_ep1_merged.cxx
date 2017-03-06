//This file was created with Single-C-File
//Single-C-File was developed by Adrian Dawid.
/*
 * Solution1.h
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
#ifndef SOLUTION1_H_
#define SOLUTION1_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/*
 * Connection.h
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */
#ifndef CONNECTION_H_
#define CONNECTION_H_
class Connection {
    int n1;
    int n2;
public:
	Connection(int n1, int n2) : n1(n1), n2(n2){}
	virtual ~Connection();
	int getN1() const;
	int getN2() const;
};
#endif /* CONNECTION_H_ */
class Solution1 {
public:
	static void run();
};
#endif /* SOLUTION1_H_ */
int main()
{
    Solution1::run();
}
/*
 * Connection.cpp
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */
int Connection::getN1() const {
	return n1;
}
int Connection::getN2() const {
	return n2;
}
Connection::~Connection() {
	// TODO Auto-generated destructor stub
}
/*
 * Node.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
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
/*
 * Solution1.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
using namespace std;
void Solution1::run(){
	int N; // the total number of nodes in the level, including the gateways
	    int L; // the number of links
	    int E; // the number of exit gateways
	    cin >> N >> L >> E; cin.ignore();
	    vector<Connection> connections;
	    for (int i = 0; i < L; i++) {
	        int N1; // N1 and N2 defines a link between these nodes
	        int N2;
	        cin >> N1 >> N2; cin.ignore();
	        Connection c(N1, N2);
	        connections.push_back(c);
	    }
	    vector<int> gateways;
	    for (int i = 0; i < E; i++) {
	        int EI; // the index of a gateway node
	        cin >> EI; cin.ignore();
	        gateways.push_back(EI);
	    }
	    // game loop
	    while (1) {
	        int SI; // The index of the node on which the Skynet agent is positioned this turn
	        cin >> SI; cin.ignore();
	        //cerr << "gateway: " << SI <<  endl;
	        vector<int> outConnections;
	        for(Connection c:connections)
	        {
	            if(c.getN1() == SI)
	            {
	                outConnections.push_back(c.getN2());
	            }
	            else if(c.getN2() == SI)
	            {
	                outConnections.push_back(c.getN1());
	            }
	        }
	        int result = outConnections[0];
	        for(int c: outConnections)
	        {
	            for(int g: gateways)
	            {
	                if(c == g)
	                {
	                    result = c;
	                }
	            }
	        }
	        // Write an action using cout. DON'T FORGET THE "<< endl"
	        // To debug: cerr << "Debug messages..." << endl;
	        cout << SI << " " << result << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	    }
}
