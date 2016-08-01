//
//  Room.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//
//
#include "Room.h"
#include "Enumerations.h"
#include <vector>
#include <string>
#include <iostream>

//CONSTRUCTOR
Room::Room(LocationType type) {
    name = getLocationTypeString(type);
    identity = type;
}
//METHODS
//adds connected rooms to the vector connected rooms
void Room::addConnectedRoom(Room* room) {
    connectedRooms.push_back(room);
}
//prints the name of the room and what it is connected to
void Room::debugPrint() {
    cout << "This room is the " << name << endl;
    cout << "It is connected to the ";
    for (int i = 0; i < connectedRooms.size(); i++) {
        cout << connectedRooms[i]->name << ", ";
    }
    cout << endl;
}


