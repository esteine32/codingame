/*
 * Position.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#include "Position.h"

Position::~Position() {
	// TODO Auto-generated destructor stub
}

int Position::getX() const {
	return x;
}

void Position::setX(int x) {
	this->x = x;
}

int Position::getY() const {
	return y;
}

void Position::setY(int y) {
	this->y = y;
}
