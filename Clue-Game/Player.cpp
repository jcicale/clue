//
//  Player.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Player.h"
#include <iostream>
#include "Utility.h"

//Player implementation
//constructor
Player::Player(CharacterType type) {
    name = getCharacterTypeString(type);
    identity = type;
}
//virtual methods, implemented below for HumanPlayer and ComputerPlayer
void Player::chooseStartingLocation(Board board) {}
void Player::move() {}
TypeCollection* Player::makeAccusation() {
    return NULL;
}
TypeCollection* Player::makeSuggestion() {
    return NULL;
}
Card* Player::disproveSuggestion(TypeCollection suggestion) {
    return NULL;
}
void Player::suggestionDisproved(TypeCollection suggestion, Card* disprovingCard) {
}

//HumanPlayer subclass implementation
//constructor
HumanPlayer::HumanPlayer(CharacterType type) : Player(type) {}
//methods
void HumanPlayer::chooseStartingLocation(Board board) {
    StartingLocations startingLocations = getStartingLocations(identity);
    cout << name << " can start in the " << endl;
    cout << startingLocations.choiceOne << ". " << getLocationTypeString(startingLocations.choiceOne) << endl;
    cout << startingLocations.choiceTwo << ". " << getLocationTypeString(startingLocations.choiceTwo) << endl;
    int selectedLocation;
    while(1) {
        selectedLocation = getIntFromConsole();
        if ((LocationType)selectedLocation == startingLocations.choiceOne || (LocationType)selectedLocation == startingLocations.choiceTwo) {
            Room* room = findRoomWithIdentity((LocationType)selectedLocation, board.rooms);
            if (room != NULL) {
                playerLocation = room;
                break;
            }
        }
        else {
            cout << "Not a valid number. Please enter a valid starting room number." << endl;
        }
    }
}

void HumanPlayer::move(){
    int newLocation;
    cout << "You are currently in the " << playerLocation->name << "." << endl;
    cout << "From here, you can move to the " << endl;
    for (int i = 0; i < playerLocation->connectedRooms.size(); i++) {
        LocationType currentRoomIdentity = playerLocation->connectedRooms[i]->identity;
        cout << currentRoomIdentity << ". " << playerLocation->connectedRooms[i]->name << endl;
    }
    while(1){
        cout << "Please enter the number of the room you would like to move to." << endl;
        newLocation = getIntFromConsole();
        Room* newRoom = findRoomWithIdentity((LocationType)newLocation, playerLocation->connectedRooms);
        if (newRoom != NULL) {
            playerLocation = newRoom;
            break;
        }
        cout << "Not a valid number. Please try again." << endl;
    }
}

TypeCollection* HumanPlayer::makeAccusation() {
    cout << "Would you like to make an accusation?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    int response;
    while (1) {
        response = getIntFromConsole();
        if (response == 2) {
            return NULL;
        }
        else if (response == 1) {
            TypeCollection* playersAccusation = new TypeCollection;
            cout << "What weapon would you like to select?" << endl;
            for (int i = 0; i < NUM_WEAPONS; i++) {
                cout << i << ". " << getWeaponTypeString((WeaponType)i) << endl;
            }
            playersAccusation->weaponUsed = (WeaponType)getIntFromConsole();
            cout << "Which character would you like to select?" << endl;
            for (int i = 0; i < NUM_CHARACTERS; i++) {
                cout << i << ". " << getCharacterTypeString((CharacterType)i) << endl;
            }
            CharacterType test = (CharacterType)getIntFromConsole();
            playersAccusation->suspectUsed = test;
            cout << "Which room would you like to select?" << endl;
            for (int i = 0; i < NUM_LOCATIONS; i++) {
                cout << i << ". " << getLocationTypeString((LocationType)i) << endl;
            }
            playersAccusation->locationUsed = (LocationType)getIntFromConsole();
            return playersAccusation;
        }
        else cout << "Not a valid number, please try again" << endl;
    }
}

TypeCollection* HumanPlayer::makeSuggestion() {
    cout << "Would you like to make a suggestion in the " << playerLocation->name << "?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    int response;
    while (1) {
        response = getIntFromConsole();
        if (response == 2) {
            return NULL;
        }
        else if (response == 1) {
            TypeCollection* playersSuggestion = new TypeCollection;
            cout << "What weapon would you like to select?" << endl;
            for (int i = 0; i < NUM_WEAPONS; i++) {
                cout << i << ". " << getWeaponTypeString((WeaponType)i) << endl;
            }
            playersSuggestion->weaponUsed = (WeaponType)getIntFromConsole();
            cout << "Which character would you like to select?" << endl;
            for (int i = 0; i < NUM_CHARACTERS; i++) {
                cout << i << ". " << getCharacterTypeString((CharacterType)i) << endl;
            }
            playersSuggestion->suspectUsed = (CharacterType)getIntFromConsole();;
            playersSuggestion->locationUsed = playerLocation->identity;
            return playersSuggestion;
        }
        else cout << "Not a valid number, please try again" << endl;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Card* HumanPlayer::disproveSuggestion(TypeCollection suggestion) {

        for(int x= 0; x<playersCards.size(); x++){
           if (playersCards[x]->type == suggestion.weaponUsed ||playersCards[x]->type == suggestion.locationUsed || playersCards[x]->type==suggestion.suspectUsed ){
               cout<< "This card: "<< playersCards[x]<< "disporves your suggestion"<<endl;
               suggestionDisproved(suggestion, playersCards[x]);
               return NULL;
           }
       }
    cout<<" Suggestion could not be dissproved"<<endl;
    return NULL;
}

void HumanPlayer::suggestionDisproved(TypeCollection suggestion, Card* disprovingCard) {


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ComputerPlayer subclass implementation
//constructor
ComputerPlayer::ComputerPlayer(CharacterType type) : Player(type) {}
//methods
void ComputerPlayer::chooseStartingLocation(Board board) {
    StartingLocations startingLocations = getStartingLocations(identity);
    int selectedLocation = getRandomNumber(1);
    Room *room;
    if (selectedLocation == 0) {
        room = findRoomWithIdentity(startingLocations.choiceOne, board.rooms);
    }
    else if (selectedLocation == 1) {
        room = findRoomWithIdentity(startingLocations.choiceTwo, board.rooms);
    }
    if (room != NULL) {
        playerLocation = room;
        cout << name << " is starting in the " << playerLocation->name << endl;
    }
}

void ComputerPlayer::move() {
    int newLocation = getRandomNumber(playerLocation->connectedRooms.size()-1);
    playerLocation = playerLocation->connectedRooms[newLocation];
    cout << name << " has moved to the " << playerLocation->name << endl;
}

TypeCollection* ComputerPlayer::makeAccusation() {
    cout << name << " did not make an accusation." << endl;
    return NULL;
}

TypeCollection* ComputerPlayer::makeSuggestion() {
    TypeCollection* computerSuggestion = new TypeCollection;
    int randomWeapon = getRandomNumber(NUM_WEAPONS-1);
    computerSuggestion->weaponUsed = (WeaponType)randomWeapon;
    int randomCharacter = getRandomNumber(NUM_CHARACTERS-1);
    computerSuggestion->suspectUsed = (CharacterType)randomCharacter;
    computerSuggestion->locationUsed = playerLocation->identity;
    cout << name << " has suggested the killer was " << getCharacterTypeString(computerSuggestion->suspectUsed) <<  " in the "<< getLocationTypeString(computerSuggestion->locationUsed) << " with the " << getWeaponTypeString(computerSuggestion->weaponUsed) << "." << endl;
    return computerSuggestion;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Card* ComputerPlayer::disproveSuggestion(TypeCollection suggestion) {
    return NULL;
}
void ComputerPlayer::suggestionDisproved(TypeCollection suggestion, Card* disprovingCard) {
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
