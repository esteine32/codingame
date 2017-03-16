#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

#include "Solution2.h"
#include "Node.h"

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

		// find closest gateway to SI (given by BFS)
		NodePtr closestGateway(nullptr);
		for(NodePtr gateway : gateways){
			if(gateway->getDistance() != -1 && (closestGateway == nullptr || gateway->getDistance() < closestGateway->getDistance())){
				closestGateway = gateway;
			}
		}

		// following route from closest gateway to SI, find link connected to SI
		NodePtr n1(closestGateway);
		NodePtr n2(nodes[n1->getPredecessor()]);
		while(n2->getPredecessor() != -1){
			n1 = n2;
			n2 = nodes[n2->getPredecessor()];
		}

		// remove result link for following iterations
		n1->removeAdjacentNode(n2->getNumber());
		n2->removeAdjacentNode(n1->getNumber());

		cout << n1->getNumber() << " " << n2->getNumber() << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between

		resetNodes(nodes);
	}
}
