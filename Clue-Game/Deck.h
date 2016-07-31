//
//  Deck.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Deck_h
#define Deck_h

#include <stdio.h>
#include "Card.h"
#include "Player.h"


class WeaponDeck {
public:
    vector<WeaponCard*> weaponCards;
    
    WeaponDeck();
    
    WeaponCard* getRandomCard();
    void printWeaponDeck();
    
};

class SuspectDeck {
public:
    vector<SuspectCard*> suspectCards;
    
    SuspectDeck();
    
    SuspectCard* getRandomCard();
    void printSuspectDeck();
};

class LocationDeck {
public:
    vector<LocationCard*> locationCards;

    LocationDeck();
    LocationCard* getRandomCard();
    void printLocationDeck();
};

class Deck {
public:
    vector<Card*> cards;
    
    Deck(WeaponDeck weaponDeck, SuspectDeck suspectDeck, LocationDeck locationDeck);
    
    void dealCards(vector<Player*> players);
};


#endif /* Deck_h */
