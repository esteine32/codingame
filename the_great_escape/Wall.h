/*
 * Wall.h
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#ifndef WALL_H_
#define WALL_H_

#include <string>
#include <vector>

#include "Direction.h"

class Wall;
typedef std::shared_ptr<Wall> WallPtr;

class Wall {
    int x;
    int y;
    std::string orientation;

public:
	Wall(int x, int y, std::string o) : x(x), y(y), orientation(o){}
	virtual ~Wall();
	std::string getOrientation() const;
	int getX() const;
	int getY() const;
	bool hasValidCoords();
	bool isPlacingOnOtherWall(const std::vector<WallPtr>& walls);
	static std::vector<WallPtr> getWallsInDirection(int x, int y, const Direction& d);
};



#endif /* WALL_H_ */
