//
//  Card.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Card.h"


Card::Card(CardType t) {
    type = t;
}


WeaponCard::WeaponCard(WeaponType type) : Card(Weapon) {
    weaponType = type;
}

SuspectCard::SuspectCard(CharacterType type) : Card(Suspect) {
    characterType = type;
}


LocationCard::LocationCard(LocationType type) : Card(Location) {
    locationType = type;
}


