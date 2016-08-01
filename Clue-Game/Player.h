//
//  Player.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include "Enumerations.h"
#include "Room.h"
#include <vector>
#include "Card.h"
#include "Board.h"

class Player {
public:
    string name;
    CharacterType identity;
    Room* playerLocation;
    vector<Card*> playersCards;
    Player(CharacterType type);
    ~Player();
    vector<WeaponCard*> weaponsList;
    vector<SuspectCard*> suspectsList;
    vector<LocationCard*> locationsList;
    virtual void chooseStartingLocation(Board board);
    virtual void printOutCards();
    virtual void removePlayersCardsFromList(vector<Card*> playersCards);
    virtual void move();
    virtual TypeCollection* makeAccusation();
    virtual TypeCollection* makeSuggestion();
    virtual Card* disproveSuggestion(TypeCollection suggestion, Player* currentPlayer);
    virtual void suggestionDisproved(Player* player, Card* disprovingCard);

};

class HumanPlayer : public Player {
public:
    HumanPlayer(CharacterType type);
    void chooseStartingLocation(Board board);
    void printOutCards();
    void removePlayersCardsFromList(vector<Card*> playersCards);
    void move();
    TypeCollection* makeAccusation();
    TypeCollection* makeSuggestion();
    Card* disproveSuggestion(TypeCollection suggestion, Player* currentPlayer);
    void suggestionDisproved(Player* player, Card* disprovingCard);
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(CharacterType type);
    void chooseStartingLocation(Board board);
    void printOutCards();
    void removePlayersCardsFromList(vector<Card*> playersCards);
    void move();
    TypeCollection* makeAccusation();
    TypeCollection* makeSuggestion();
    Card* disproveSuggestion(TypeCollection suggestion, Player* currentPlayer);
    void suggestionDisproved(Player* player, Card* disprovingCard);

};

//function to compare the order of two players; returns true if playerOne goes before playerTwo, otherwise false
inline bool isOrderedBefore(Player* playerOne, Player* playerTwo) {
    if (playerOne->identity < playerTwo->identity) {
        return true;
    }
    else return false;
}

inline Player* findPlayerWithIdentity(vector<Player*> players, CharacterType identity) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->identity == identity) return players[i];
    }
    return NULL;
}

#endif /* Player_h */
