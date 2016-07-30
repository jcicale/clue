//
//  Enumerations.h
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Enumerations_h
#define Enumerations_h

#include <string>

using namespace std;

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

inline string getWeaponTypeString(WeaponType type) {
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

#define NUM_CHARACTERS 6

enum CharacterType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};

inline string getCharacterTypeString(CharacterType type) {
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

inline string getLocationTypeString(LocationType type) {
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
};

struct StartingLocations {
    LocationType choiceOne;
    LocationType choiceTwo;
};

inline StartingLocations getStartingLocations(CharacterType character) {
    StartingLocations startingLocations;
    switch (character) {
        case Scarlet:
            startingLocations.choiceOne = Hall;
            startingLocations.choiceTwo = Lounge;
            break;
        case Mustard:
            startingLocations.choiceOne = Lounge;
            startingLocations.choiceTwo = DiningRoom;
            break;
        case White:
            startingLocations.choiceOne = Kitchen;
            startingLocations.choiceTwo = Ballroom;
            break;
        case Green:
            startingLocations.choiceOne = Ballroom;
            startingLocations.choiceTwo = Conservatory;
            break;
        case Peacock:
            startingLocations.choiceOne = Conservatory;
            startingLocations.choiceTwo = BilliardRoom;
            break;
        case Plum:
            startingLocations.choiceOne = Library;
            startingLocations.choiceTwo = Study;
            break;
            
    }
    return startingLocations;
}

//these are the three Card Types that will go in the killer envelope
struct TypeCollection {
    WeaponType weaponUsed;
    CharacterType suspectUsed;
    LocationType locationUsed;
};


#endif
