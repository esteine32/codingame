/*
 * Position.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
    int x;
    int y;
public:
	Position() : x(0), y(0){}
	virtual ~Position();
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};

#endif /* POSITION_H_ */
