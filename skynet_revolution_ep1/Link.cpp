/*
 * Connection.cpp
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */

#include "Link.h"

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

