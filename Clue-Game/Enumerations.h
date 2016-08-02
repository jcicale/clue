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

//Enumeration for the three types of cards
enum CardType {
    Weapon,
    Suspect,
    Location
};

//constant number of weapons
#define NUM_WEAPONS 6
//Enumeration for the six types of weapons
enum WeaponType {
    Candlestick,
    Knife,
    LeadPipe,
    Revolver,
    Rope,
    Wrench
};
//function used to access a string corresponding to each weapon type
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

//constant number of suspects
#define NUM_SUSPECTS 6
//enumeration for the six types of suspects
enum SuspectType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};
//function used to access a string corresponding to each suspect type
inline string getSuspectTypeString(SuspectType type) {
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

//constant number of locations
#define NUM_LOCATIONS 9
//enumeration for the nine different types of location
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
//function used to access a string corresponding to each location type
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

//choice of two starting locations
struct StartingLocations {
    LocationType choiceOne;
    LocationType choiceTwo;
};
//function that assigns starting locations based on SuspectType enumeration
inline StartingLocations getStartingLocations(SuspectType suspect) {
    StartingLocations startingLocations;
    switch (suspect) {
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
    SuspectType suspectUsed;
    LocationType locationUsed;
};


#endif
