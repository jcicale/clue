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
    virtual void chooseStartingLocation(Board board);
    virtual void move();
    virtual TypeCollection* makeAccusation();
    virtual TypeCollection* makeSuggestion();
    virtual Card* disproveSuggestion(TypeCollection suggestion);
    virtual void suggestionDisproved(TypeCollection suggestion, Card* disprovingCard);
};

class HumanPlayer : public Player {
public:
    HumanPlayer(CharacterType type);
    void chooseStartingLocation(Board board);
    void move();
    TypeCollection* makeAccusation();
    TypeCollection* makeSuggestion();
    Card* disproveSuggestion(TypeCollection suggestion);
    void suggestionDisproved(TypeCollection suggestion, Card* disprovingCard);
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(CharacterType type);
    void chooseStartingLocation(Board board);
    void move();
    TypeCollection* makeAccusation();
    TypeCollection* makeSuggestion();
    Card* disproveSuggestion(TypeCollection suggestion);
    void suggestionDisproved(TypeCollection suggestion, Card* disprovingCard);

};

//function to compare the order of two players; returns true if playerOne goes before playerTwo, otherwise false
inline bool isOrderedBefore(Player* playerOne, Player* playerTwo) {
    if (playerOne->identity < playerTwo->identity) {
        return true;
    }
    else return false;
}

#endif /* Player_h */
