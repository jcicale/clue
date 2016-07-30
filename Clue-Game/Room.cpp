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

void Room::addConnectedRoom(Room* room) {
    connectedRooms.push_back(room);
}

void Room::debugPrint() {
    cout << "This room is the " << name << endl;
    cout << "It is connected to the ";
    for (int i = 0; i < connectedRooms.size(); i++) {
        cout << connectedRooms[i]->name << ", ";
    }
    cout << endl;
}

Room::Room(LocationType type) {
    name = getLocationTypeString(type);
    identity = type;
}

