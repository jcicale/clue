//
//  Deck.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Deck.h"
#include <random>


//constructs and shuffles the WeaponDeck
WeaponDeck::WeaponDeck() {
    for(int i = 0; i<NUM_WEAPONS; i++){
        WeaponCard* card = new WeaponCard((WeaponType)i);
        weaponCards.push_back(card);
    }
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(weaponCards.begin(), weaponCards.end(), default_random_engine((unsigned)seed));
}
//returns a random card from the weapon deck, used for making the envelope
WeaponCard* WeaponDeck::getRandomCard() {
    WeaponCard* randomWeaponCard = weaponCards.back();
    weaponCards.pop_back();
    return randomWeaponCard;
}
//prints what is in the weapon deck
void WeaponDeck::printWeaponDeck(){
    for (int i = 0; i < weaponCards.size(); i++) {
        Card* card = weaponCards[i];
        if (card->type == Weapon) {
            WeaponCard* weapon = (WeaponCard*)card;
            cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
        }
    }
}


//constructs and shuffles the SuspectDeck
SuspectDeck::SuspectDeck() {
    for(int i = 0; i<NUM_CHARACTERS; i++){
        SuspectCard* card = new SuspectCard((CharacterType)i);
        suspectCards.push_back(card);
    }
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(suspectCards.begin(), suspectCards.end(), default_random_engine((unsigned)seed));
}
//returns a random card from the suspect deck, used for making the envelope
SuspectCard* SuspectDeck::getRandomCard(){
    SuspectCard* randomSuspectCard = suspectCards.back();
    suspectCards.pop_back();
    return randomSuspectCard;
}
//prints what is in the suspect deck
void SuspectDeck::printSuspectDeck(){
    for (int i = 0; i < suspectCards.size(); i++) {
        Card* card = suspectCards[i];
        if (card->type == Suspect) {
            SuspectCard* suspect = (SuspectCard*)card;
            cout <<"We have a suspect card: " << getCharacterTypeString(suspect->characterType)  << endl;
        }
    }
}


//constructs and shuffles the LocationDeck
LocationDeck::LocationDeck() {
    for(int i = 0; i<NUM_LOCATIONS; i++){
        LocationCard* card = new LocationCard((LocationType)i);
        locationCards.push_back(card);
    }
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(locationCards.begin(), locationCards.end(), default_random_engine((unsigned)seed));
}
//returns a random card from the location deck, used for making the envelope
LocationCard* LocationDeck::getRandomCard(){
    LocationCard* randomLocationCard = locationCards.back();
    locationCards.pop_back();
    return randomLocationCard;
}
//prints what is in the location deck
void LocationDeck::printLocationDeck(){
    for (int i = 0; i < locationCards.size(); i++) {
        Card* card = locationCards[i];
        if (card->type == Location) {
            LocationCard* location = (LocationCard*)card;
            cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
        }
    }
}


//constructs the Deck from the cards left in each Type Deck after selecting the killer cards
Deck::Deck(WeaponDeck weaponDeck, SuspectDeck suspectDeck, LocationDeck locationDeck) {
    for (int i = 0; i < weaponDeck.weaponCards.size(); i++) {
        cards.push_back(weaponDeck.weaponCards[i]);
    }
    for (int i = 0; i < suspectDeck.suspectCards.size(); i++) {
        cards.push_back(suspectDeck.suspectCards[i]);
    }
    for (int i = 0; i < locationDeck.locationCards.size(); i++) {
        cards.push_back(locationDeck.locationCards[i]);
    }
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine((unsigned)seed));
}
//deals cards out to players
void Deck::dealCards(vector<Player*> players) {
    while (!cards.empty()) {
        for (int i = 0; i < players.size(); i ++) {
            if (cards.empty()) break;
            players[i]->playersCards.push_back(cards.back());
            cards.pop_back();
            
        }
    }
}
