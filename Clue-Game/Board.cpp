//
//  Board.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Board.h"
#include "Player.h"


void Board::addRoom(Room* roomToAdd) {
    rooms.push_back(roomToAdd);
}

void Board::debugPrint() {
    for (int i = 0; i < rooms.size(); i++) {
        rooms[i]->debugPrint();
    }
}

Board::Board() {
    Room* kitchen = new Room(Kitchen);
    Room* ballroom = new Room(Ballroom);
    Room* conservatory = new Room(Conservatory);
    Room* billiardRoom = new Room(BilliardRoom);
    Room* library = new Room(Library);
    Room* study = new Room(Study);
    Room* hall = new Room(Hall);
    Room* lounge = new Room(Lounge);
    Room* diningRoom = new Room(DiningRoom);
    addRoom(kitchen);
    addRoom(ballroom);
    addRoom(conservatory);
    addRoom(billiardRoom);
    addRoom(library);
    addRoom(study);
    addRoom(hall);
    addRoom(lounge);
    addRoom(diningRoom);
    kitchen->addConnectedRoom(ballroom);
    kitchen->addConnectedRoom(diningRoom);
    kitchen->addConnectedRoom(study);
    ballroom->addConnectedRoom(kitchen);
    ballroom->addConnectedRoom(conservatory);
    conservatory->addConnectedRoom(ballroom);
    conservatory->addConnectedRoom(billiardRoom);
    conservatory->addConnectedRoom(lounge);
    billiardRoom->addConnectedRoom(conservatory);
    billiardRoom->addConnectedRoom(library);
    library->addConnectedRoom(billiardRoom);
    library->addConnectedRoom(study);
    study->addConnectedRoom(library);
    study->addConnectedRoom(hall);
    study->addConnectedRoom(kitchen);
    hall->addConnectedRoom(study);
    hall->addConnectedRoom(lounge);
    lounge->addConnectedRoom(hall);
    lounge->addConnectedRoom(diningRoom);
    lounge->addConnectedRoom(conservatory);
    diningRoom->addConnectedRoom(lounge);
    diningRoom->addConnectedRoom(kitchen);
}

void Board::movePlayerToRoom(Player* player, LocationType location) {
    player->playerLocation;
}

