/*
 * Player.h
 *
 *  Created on: 26 Feb 2017
 *      Author: sbl
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
	int id;
	int x;
	int y;
	int noOfwalls;

public:
	Player(int id, int x, int y, int noOfwalls) : id(id), x(x), y(y), noOfwalls(noOfwalls){}
	virtual ~Player();

	int getId() const;

	int getX() const;

	int getY() const;

	int getNoOfwalls() const;

};

#endif /* PLAYER_H_ */
