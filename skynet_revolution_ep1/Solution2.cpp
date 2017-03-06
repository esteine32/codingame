/*
 * Solution2.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Solution2.h"
#include "Connection.h"
#include "Node.h"

using namespace std;
typedef shared_ptr<Connection> ConnectionPtr;
typedef shared_ptr<Node> NodePtr;


void Solution2::run(){
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();

	vector<ConnectionPtr> connections;
	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();

		connections.push_back(ConnectionPtr(new Connection(N1, N2)));
	}

	vector<int> gateways;
	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();

		gateways.push_back(EI);
	}

	int startSI; // The index of the node on which the Skynet agent is positioned at start
	cin >> startSI; cin.ignore();

	NodePtr startNode;

	vector<NodePtr> nodes;
	for (int i = 0; i<N; ++i){
		if(i == startSI){
			startNode = NodePtr(new Node(i));
		}else{
			nodes.push_back(NodePtr(new Node(i)));
		}
	}

	// game loop
	while (1) {
		static bool first = true;

		int SI; // The index of the node on which the Skynet agent is positioned this turn
		if(first){
			SI = startSI;
			first = false;
		}else{
			cin >> SI; cin.ignore();
		}

		cout << SI << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	}
}
