//
//  Board.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <vector>
#include "Room.h"
class Player;

class Board {
public:
    vector<Room*> rooms;
    
    void addRoom(Room* roomToAdd);
    void debugPrint();
    
    Board();
    void movePlayerToRoom(Player* player, LocationType location);
};


#endif /* Board_hpp */
