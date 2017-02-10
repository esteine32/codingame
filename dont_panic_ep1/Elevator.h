/*
 * Elevator.h
 *
 *  Created on: 8 Feb 2017
 *      Author: sbl
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

class Elevator {
    int floor;
    int pos;
public:
	Elevator(int f, int p) : floor(f), pos(p){}
	virtual ~Elevator(){}

	int getFloor(){return floor;}
	int getPos(){return pos;}
};

#endif /* ELEVATOR_H_ */
