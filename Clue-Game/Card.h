//
//  Card.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <stdio.h>
#include "Enumerations.h"
#include <vector>
#include <iostream>

class Card {
public:
    CardType type;
    Card(CardType t);
    string name;
};

class WeaponCard : public Card {
public:
    WeaponType weaponType;
    WeaponCard(WeaponType type);
};

class SuspectCard : public Card {
public:
    SuspectType suspectType;
    SuspectCard(SuspectType type);
};

class LocationCard : public Card {
public:
    LocationType locationType;
    LocationCard(LocationType type);
};

//function to print cards
inline void printCards(vector<Card*> cards) {
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards[i];
        if (card->type == Weapon) {
            WeaponCard* weapon = (WeaponCard*)card;
            cout <<"Weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
        }
        else if (card->type == Suspect) {
            SuspectCard* suspect = (SuspectCard*)card;
            cout <<"Suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
        }
        else if (card->type == Location) {
            LocationCard* location = (LocationCard*)card;
            cout <<"Location card: " << getLocationTypeString(location->locationType)  << endl;
        }
    }
}


#endif /* Card_h */
