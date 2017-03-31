/*
 * AStarResult.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#include "AStarResult.h"

Direction AStarResult::getDirection() const {
	return direction;
}

int AStarResult::getLength() const {
	return length;
}

AStarResult::~AStarResult() {
	// TODO Auto-generated destructor stub
}

