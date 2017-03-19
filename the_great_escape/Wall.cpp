/*
 * Wall.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#include "Wall.h"


std::string Wall::getOrientation() const {
	return orientation;
}

int Wall::getX() const {
	return x;
}

int Wall::getY() const {
	return y;
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

