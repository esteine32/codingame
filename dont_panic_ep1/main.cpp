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
#include <memory>

#include "Elevator.h"

using namespace std;

typedef shared_ptr<Elevator> ElevatorPtr;

bool wrongDirection(int clonePos, int targetPos, string direction)
{
    return (clonePos > targetPos && direction.compare("RIGHT")==0) || (clonePos < targetPos && direction.compare("LEFT")==0);
}

int findElevatorPosOnFloor(int floor, vector<ElevatorPtr> elevators)
{
    ElevatorPtr e = elevators[0];
    for(int i = 1; i<elevators.size(); ++i)
    {
        if(elevators[i]->getFloor() == floor)
        {
            e = elevators[i];
            break;
        }
    }
    return e->getPos();
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
    //cerr << "nbFloors=" << nbFloors << ", width=" << width << ", nbRounds="<< nbRounds << ", exitFloor=" << exitFloor << ", exitPos=" << exitPos << ", nbTotalClones=" << nbTotalClones << ", nbAdditionalElevators=" << nbAdditionalElevators << ", nbElevators="<< nbElevators<<endl;

    vector<ElevatorPtr> elevators;
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        //cerr << "elevetor number=" << i << ": elevatorFloor="<<elevatorFloor << ", elevatorPos=" << elevatorPos << endl;

        ElevatorPtr e(new Elevator(elevatorFloor, elevatorPos));
        elevators.push_back(e);
    }


    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        //cerr << "cloneFloor=" << cloneFloor << ", clonePos="<< clonePos << ", direction="<< direction << endl;


        string result = "WAIT";
        int targetPos = -1;
        if(cloneFloor != -1){
            if(cloneFloor == exitFloor)
                targetPos = exitPos;
            else
            	 targetPos = findElevatorPosOnFloor(cloneFloor, elevators);

            if(wrongDirection(clonePos, targetPos, direction))
                result = "BLOCK";
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << result << endl; // action: WAIT or BLOCK
    }
}


