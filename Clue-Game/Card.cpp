//
//  Card.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Card.h"

//CONSTRUCTOR
Card::Card(CardType t) {
    type = t;
}

//WeaponCard Subclass Implementation
//CONSTRUCTOR
WeaponCard::WeaponCard(WeaponType type) : Card(Weapon) {
    weaponType = type;
    name = getWeaponTypeString(type);
}
//SuspectCard Subclass Implementation
//CONSTRUCTOR
SuspectCard::SuspectCard(CharacterType type) : Card(Suspect) {
    characterType = type;
    name = getCharacterTypeString(type);
}
//LocationCard Subclass Implementation
//CONSTRUCTOR
LocationCard::LocationCard(LocationType type) : Card(Location) {
    locationType = type;
    name = getLocationTypeString(type);
}


