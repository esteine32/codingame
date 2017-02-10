//This file was created with Single-C-File
//Single-C-File was developed by Adrian Dawid.
/*
 * main.cpp
 *
 *  Created on: 8 Feb 2017
 *      Author: sbl
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
using namespace std;
bool wrongDirection(int clonePos, int targetPos, string direction)
{
    return (clonePos > targetPos && direction.compare("RIGHT")==0) || (clonePos < targetPos && direction.compare("LEFT")==0);
}
bool floorBlocked(int floor, const vector<bool>& floorsBlocked)
{
    if(floor == -1)
        return true;
    return floorsBlocked[floor];
}
int findElevatorPosOnFloor(int floor, vector<Elevator>& elevators)
{
    Elevator e = elevators[0];
    for(int i = 1; i<elevators.size(); ++i)
    {
        if(elevators[i].getFloor() == floor)
        {
            e = elevators[i];
            break;
        }
    }
    return e.getPos();
}
int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    cerr << "nbFloors=" << nbFloors << ", width=" << width << ", nbRounds="<< nbRounds << ", exitFloor=" << exitFloor << ", exitPos=" << exitPos << ", nbTotalClones=" << nbTotalClones << ", nbAdditionalElevators=" << nbAdditionalElevators << ", nbElevators="<< nbElevators<<endl;
    vector<Elevator> elevators;
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        cerr << "i=" << i << ": elevatorFloor="<<elevatorFloor << ", elevatorPos=" << elevatorPos << endl;
        Elevator e(elevatorFloor, elevatorPos);
        elevators.push_back(e);
    }
    vector<bool> floorsBlocked;
    for(int i = 0; i<nbFloors; ++i)
    {
        floorsBlocked.push_back(false);
    }
    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        cerr << "cloneFloor=" << cloneFloor << ", clonePos="<< clonePos << ", direction="<< direction << endl;
        string result = "WAIT";
        int targetPos = -1;
        if(cloneFloor != -1){
            if(cloneFloor == exitFloor)
            {
                targetPos = exitPos;
            }
            else
            {
            	 targetPos = findElevatorPosOnFloor(cloneFloor, elevators);
            }
        }
        if(wrongDirection(clonePos, targetPos, direction))
        {
            result = "BLOCK";
            floorsBlocked[cloneFloor] = true;
        }
        if(!floorBlocked(cloneFloor, floorsBlocked))
        {
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout << result << endl; // action: WAIT or BLOCK
    }
}
/*
 * Elevator.cpp
 *
 *  Created on: 8 Feb 2017
 *      Author: sbl
 */
