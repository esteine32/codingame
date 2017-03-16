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
class Solution1 {
public:
	static void run();
};
#endif /* SOLUTION1_H_ */
#ifndef SOLUTION2_H_
#define SOLUTION2_H_
class Solution2 {
public:
	static void run();
};
#endif /* SOLUTION2_H_ */
int main()
{
    Solution2::run();
}
/*
 * Connection.cpp
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */
/*
 * Connection.h
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */
#ifndef LINK_H_
#define LINK_H_
class Link {
    int n1;
    int n2;
public:
	Link(int n1, int n2) : n1(n1), n2(n2){}
	virtual ~Link();
	int getN1() const;
	int getN2() const;
	bool operator==(Link c);
};
#endif /* LINK_H_ */
int Link::getN1() const {
	return n1;
}
int Link::getN2() const {
	return n2;
}
bool Link::operator==(Link l){
	return this->n1 == l.n1 && this->n2 == l.n2;
}
Link::~Link() {
	// TODO Auto-generated destructor stub
}
/*
 * Node.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
#include <iostream>
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
/*
 * Solution1.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
#include <string>
using namespace std;
void Solution1::run(){
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();
	vector<Link> links;
	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();
		Link l(N1, N2);
		links.push_back(l);
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
		//cerr << "agent: " << SI <<  endl;
		vector<int> adjacentNodes;
		for(Link l:links)
		{
			if(l.getN1() == SI)
			{
				adjacentNodes.push_back(l.getN2());
			}
			else if(l.getN2() == SI)
			{
				adjacentNodes.push_back(l.getN1());
			}
		}
		int result = adjacentNodes[0];
		for(int n: adjacentNodes)
		{
			for(int g: gateways)
			{
				if(n == g)
				{
					result = n;
				}
			}
		}
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;
		cout << SI << " " << result << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	}
}
#include <memory>
#include <queue>
using namespace std;
typedef shared_ptr<Node> NodePtr;
void breadthFirstSearch(const vector<NodePtr> &nodes, int startNodeNumber){
	NodePtr startNode = nodes[startNodeNumber];
	startNode->setState(State::DESCOVERED);
	startNode->setDistance(0);
	queue<NodePtr> q;
	q.push(startNode);
	while(!q.empty()){
		NodePtr u = q.front();
		q.pop();
		for(int nodeNumber : u->getAdjacentNodes()){
			NodePtr v = nodes[nodeNumber];
			if(v->getState() == State::UNDESCOVERED){
				v->setState(State::DESCOVERED);
				v->setDistance(u->getDistance() + 1);
				v->setPredecessor(u->getNumber());
				q.push(v);
			}
		}
		u->setState(State::PROCESSED);
	}
}
void printPath(const vector<NodePtr> &nodes, int startNodeNumber, int nodeNumber){
	NodePtr node = nodes[nodeNumber];
	if(startNodeNumber == nodeNumber){
		cerr << *nodes[startNodeNumber] << endl;
	}else if(node->getPredecessor() == -1){
		cerr << "No path from node="<<startNodeNumber<<" to node="<<nodeNumber<<" exists" <<endl;
	}else{
		printPath(nodes, startNodeNumber, node->getPredecessor());
		cerr << *node << endl;
	}
}
void printPaths(const vector<NodePtr> &nodes, int startNodeNumber){
	for(NodePtr node : nodes){
		cerr << "************************** Path for node=" << node->getNumber() << "**************************" << endl;
		printPath(nodes, startNodeNumber, node->getNumber());
	}
}
void resetNodes(const vector<NodePtr> &nodes){
	for(NodePtr node : nodes){
		node->reset();
	}
}
void Solution2::run(){
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();
	vector<NodePtr> nodes;
	for (int i = 0; i<N; ++i){
		nodes.push_back(NodePtr(new Node(i)));
	}
	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();
		nodes[N1]->addAdjacentNode(N2);
		nodes[N2]->addAdjacentNode(N1);
	}
	vector<NodePtr> gateways;
	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		gateways.push_back(nodes[EI]);
	}
	// game loop
	while (1) {
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();
		breadthFirstSearch(nodes, SI);
		//printPaths(nodes, SI);
		NodePtr closestGateway(nullptr);
		for(NodePtr gateway : gateways){
			if(gateway->getDistance() != -1 && (closestGateway == nullptr || gateway->getDistance() < closestGateway->getDistance())){
				closestGateway = gateway;
			}
		}
		NodePtr n1(closestGateway);
		NodePtr n2(nodes[n1->getPredecessor()]);
		while(n2->getPredecessor() != -1){
			n1 = n2;
			n2 = nodes[n2->getPredecessor()];
		}
		n1->removeAdjacentNode(n2->getNumber());
		n2->removeAdjacentNode(n1->getNumber());
		cout << n1->getNumber() << " " << n2->getNumber() << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
		resetNodes(nodes);
	}
}
