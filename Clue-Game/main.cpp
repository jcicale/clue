//
//  main.cpp
//  Clue-Game
//
//  Created by Julia on 7/16/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Room {
public:
    string name;
    string abbreviation;
    vector<Room*> connectedRooms;
    void addConnectedRoom(Room* room) {
        connectedRooms.push_back(room);
    };
    Room(string roomName, string roomAbbreviation) {
        name = roomName;
        abbreviation = roomAbbreviation;
    };
    void debugPrint() {
        cout << "This room is the " << name << endl;
        cout << "It is connected to the ";
        for (int i = 0; i < connectedRooms.size(); i++) {
            cout << connectedRooms[i]->name << ", ";
        }
        cout << endl;
    };
    
};

Room* findRoomWithAbbreviation(string abbreviation, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->abbreviation.compare(abbreviation) == 0){
            return rooms[i];
        }
    }
    return NULL;
}


class Board {
public:
    vector<Room*> rooms;
    void addRoom(Room* roomToAdd) {
        rooms.push_back(roomToAdd);
    };
    void debugPrint() {
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->debugPrint();
        }
    };
    Board() {
        Room* kitchen = new Room("Kitchen", "K");
        Room* ballroom = new Room("Ballroom", "B");
        Room* conservatory = new Room("Conservatory", "C");
        Room* billiardRoom = new Room("Billiard Room", "BR");
        Room* library = new Room("Library", "L");
        Room* study = new Room("Study", "S");
        Room* hall = new Room("Hall", "H");
        Room* lounge = new Room("Lounge", "LO");
        Room* diningRoom = new Room("Dining Room", "D");
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
    
};

class Player {
public:
    string name;
    Room* playerLocation;
    Player(string playerName) {
        name = playerName;
    }
    void move(){
        string newLocation;
        cout << "You are currently in the " << playerLocation->name << "." << endl;
        cout << "From here, you can move to the ";
        for (int i = 0; i < playerLocation->connectedRooms.size(); i++) {
            cout << playerLocation->connectedRooms[i]->name << " (" << playerLocation->connectedRooms[i]->abbreviation << "), " << endl;
        }
        cout << "Please enter the abbreviation of the room you would like to move to." << endl;
        cin >> newLocation;
        Room* newRoom = findRoomWithAbbreviation(newLocation, playerLocation->connectedRooms);
        if (newRoom != NULL) {
            playerLocation = newRoom;
        }
        
    }
};

enum CardType {
    Weapon,
    Suspect,
    Location
};

#define NUM_WEAPONS 6

enum WeaponType {
    Candlestick,
    Knife,
    LeadPipe,
    Revolver,
    Rope,
    Wrench
};

string getWeaponTypeString(WeaponType type) {
    switch (type) {
        case Candlestick:
            return "Candlestick";
        case Knife:
            return "Knife";
        case LeadPipe:
            return "Lead Pipe";
        case Revolver:
            return "Revolver";
        case Rope:
            return "Rope";
        case Wrench:
            return "Wrench";
    }
}

#define NUM_SUSPECTS 6

enum SuspectType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};

string getSuspectTypeString(SuspectType type) {
    switch (type) {
        case Scarlet:
            return "Miss Scarlet";
        case Mustard:
            return "Colonel Mustard";
        case White:
            return "Mrs. White";
        case Green:
            return "Mr. Green";
        case Peacock:
            return "Mrs. Peacock";
        case Plum:
            return "Professor Plum";
    }
}

#define NUM_LOCATIONS 9

enum LocationType {
    Kitchen,
    Ballroom,
    Conservatory,
    BilliardRoom,
    Library,
    Study,
    Hall,
    Lounge,
    DiningRoom
};

string getLocationTypeString(LocationType type) {
    switch (type) {
        case Kitchen:
            return "Kitchen";
        case Ballroom:
            return "Ballroom";
        case Conservatory:
            return "Conservatory";
        case BilliardRoom:
            return "Billiard Room";
        case Library:
            return "Library";
        case Study:
            return "Study";
        case Hall:
            return "Hall";
        case Lounge:
            return "Lounge";
        case DiningRoom:
            return "Dining Room";
    }
}

class Card {
public:
    CardType type;
    Card(CardType t) {
        type = t;
    }
};

class WeaponCard : public Card {
public:
    WeaponType weaponType;
    WeaponCard(WeaponType type) : Card(Weapon) {
        weaponType = type;
    }
};

class SuspectCard : public Card {
public:
    SuspectType suspectType;
    SuspectCard(SuspectType type) : Card(Suspect) {
        suspectType = type;
    }
};

class LocationCard : public Card {
public:
    LocationType locationType;
    LocationCard(LocationType type) : Card(Location) {
        locationType = type;
    }
};

class Deck {
public:
    vector<Card*> cards;
    Deck() {
        for (int i = 0; i < NUM_WEAPONS; i++) {
            WeaponCard* card = new WeaponCard((WeaponType)i);
            cards.push_back(card);
        }
        for (int i = 0; i < NUM_SUSPECTS; i++) {
            SuspectCard* card = new SuspectCard((SuspectType)i);
            cards.push_back(card);
        }
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            LocationCard* card = new LocationCard((LocationType)i);
            cards.push_back(card);
        }
        
    }
    void debugPrint() {
        for (int i = 0; i < cards.size(); i++) {
            Card* card = cards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
            else if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }
            else if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
    }
    
    void shuffle(){
        random_shuffle(cards.begin(), cards.end());
    }
};

int main(int argc, const char * argv[]) {
    Board clueBoard;
    vector<Player*> players;
    string location;
    Player* player = new Player("Miss Scarlet");
    cout << "Miss Scarlet can start in the Lounge (LO) or the Hall (H). Please enter your location." << endl;
    cin >> location;
    Room* startingLocation = findRoomWithAbbreviation(location, clueBoard.rooms);
    player->playerLocation = startingLocation;
    //    while (1) {
    //        player->move();
    //    }
    Deck deck;
    deck.debugPrint();
    deck.shuffle();
    cout << "SHUFFLE TIME" << endl;
    deck.debugPrint();
    return 0;
    
}




