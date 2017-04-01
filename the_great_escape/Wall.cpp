/*
 * Wall.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: sbl
 */

#include "Wall.h"

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

std::string Wall::getOrientation() const {
	return orientation;
}

int Wall::getX() const {
	return x;
}

int Wall::getY() const {
	return y;
}

bool Wall::hasValidCoords()
{
    if(orientation.compare("H") == 0 && x > -1 && x < 8 && y > 0 && y < 9)
    {
        return true;
    }

    if(orientation.compare("V") == 0 && x > 0 && x < 9 && y > -1 && y < 8)
    {
        return true;
    }

    return false;
}

bool Wall::isPlacingOnOtherWall(const std::vector<WallPtr>& walls)
{

    for(WallPtr w: walls)
    {
        bool sameDirectionFail = false;
        bool otherDirectionFail = false;
        if(orientation.compare("H") == 0){
            sameDirectionFail = w->getOrientation().compare("H") == 0 && y == w->getY() && (x == w->getX()-1 || x == w->getX() || x == w->getX() + 1);
            otherDirectionFail =w->getOrientation().compare("V") == 0 && y == w->getY()+1 && x == w->getX()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        else
        {
            sameDirectionFail = w->getOrientation().compare("V") == 0 && x == w->getX() && (y == w->getY()-1 || y == w->getY() || y == w->getY() + 1);
            otherDirectionFail =w->getOrientation().compare("H") == 0 && x == w->getX()+1 && y == w->getY()-1;
            if(sameDirectionFail || otherDirectionFail)
                return true;
        }
        //cerr << "isPlacingOnOtherWall: " << w.x << " " << w.y << " " << w.orientation  << endl;
    }
    return false;
}

std::vector<WallPtr> Wall::getWallsInDirection(int x, int y, const Direction& d){

    std::vector<WallPtr> walls;

    switch(d)
    {
        case Direction::Up:
            walls.push_back(WallPtr(new Wall(x, y, "H")));
            walls.push_back(WallPtr(new Wall(x-1, y, "H")));
            break;
        case Direction::Down:
            walls.push_back(WallPtr(new Wall(x, y+1, "H")));
            walls.push_back(WallPtr(new Wall(x-1, y+1, "H")));
            break;
        case Direction::Left:
            walls.push_back(WallPtr(new Wall(x, y, "V")));
            walls.push_back(WallPtr(new Wall(x, y-1, "V")));
            break;
        case Direction::Right:
            walls.push_back(WallPtr(new Wall(x+1, y, "V")));
            walls.push_back(WallPtr(new Wall(x+1, y-1, "V")));
            break;
    }

    return walls;
}
