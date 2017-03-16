/*
 * Solution1.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: sbl
 */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Solution1.h"

#include "Link.h"

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

		// find adjacent nodes to SI
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

		// if one of the adjacent node is a gateway chose this, else chose first adjacent node
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
