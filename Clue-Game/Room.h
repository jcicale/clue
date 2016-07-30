//
//  Room.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Room_h
#define Room_h

#include "Enumerations.h"
#include <vector>
#include <string>

class Room {
public:
    string name;
    vector<Room*> connectedRooms;
    LocationType identity;

    Room(LocationType type);

    void addConnectedRoom(Room* room);
    void debugPrint();
    
};

//function to return a pointer to a room based on its LocationType
inline Room* findRoomWithIdentity(LocationType type, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++){
        if (rooms[i]->identity == type) {
            return rooms[i];
        }
    }
    return NULL;
}

#endif