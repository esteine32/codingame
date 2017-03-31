/*
 * AStarResult.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#ifndef ASTARRESULT_H_
#define ASTARRESULT_H_

#include "Direction.h"

class AStarResult {
    Direction direction;
    int length;
public:
	AStarResult(Direction d, int l) : direction(d), length(l){}
	virtual ~AStarResult();
	Direction getDirection() const;
	int getLength() const;
};

#endif /* ASTARRESULT_H_ */
