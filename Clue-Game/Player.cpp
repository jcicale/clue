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
    //creates each player's lists of weapons/characters/locations to cross off
    for (int i = 0; i < NUM_WEAPONS; i++) {
        WeaponCard* card = new WeaponCard((WeaponType)i);
        weaponsList.push_back(card);
    }
    for (int i = 0; i < NUM_CHARACTERS; i++) {
        SuspectCard* card = new SuspectCard((CharacterType)i);
        suspectsList.push_back(card);
    }
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        LocationCard* card = new LocationCard((LocationType)i);
        locationsList.push_back(card);
    }
}
Player::~Player() {
    for (int i = 0; i < locationsList.size(); i++) {
        delete locationsList[i];
    }
    for (int i = 0; i < weaponsList.size(); i++) {
        delete weaponsList[i];
    }
    for (int i = 0; i < suspectsList.size(); i++) {
        delete suspectsList[i];
    }
    for (int i = 0; i < playersCards.size(); i++) {
        delete playersCards[i];
    }
}
//virtual methods, implemented below for HumanPlayer and ComputerPlayer
void Player::chooseStartingLocation(Board* board) {}
void Player::printOutCards() {}
void Player::removePlayersCardsFromList() { }
void Player::move() {}
void Player::cheat(Envelope* envelope) {} 
//these return NULL just in case somehow a Player without a subclass is created
TypeCollection* Player::makeAccusation() {
    return NULL;
}
TypeCollection* Player::makeSuggestion() {
    return NULL;
}
Card* Player::disproveSuggestion(TypeCollection suggestion, Player* currentPlayer) {
    return NULL;
}
void Player::suggestionDisproved(Player* player, Card* disprovingCard) {
}

//HumanPlayer subclass implementation
//CONSTRUCTOR
HumanPlayer::HumanPlayer(CharacterType type) : Player(type) {}
//METHODS
//user is allowed to select which room to start in (each character type can start in one of two rooms)
void HumanPlayer::chooseStartingLocation(Board* board) {
    StartingLocations startingLocations = getStartingLocations(identity);
    cout << name << " can start in the " << endl;
    cout << startingLocations.choiceOne << ". " << getLocationTypeString(startingLocations.choiceOne) << endl;
    cout << startingLocations.choiceTwo << ". " << getLocationTypeString(startingLocations.choiceTwo) << endl;
    int selectedLocation;
    while(1) {
        selectedLocation = getIntFromConsole();
        if ((LocationType)selectedLocation == startingLocations.choiceOne || (LocationType)selectedLocation == startingLocations.choiceTwo) {
            Room* room = findRoomWithIdentity((LocationType)selectedLocation, board->rooms);
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
//method to print out HumanPlayer's card at the beginning of each turn for reference
void HumanPlayer::printOutCards() {
    cout << "You have the following cards: " << endl;
    for (int i = 0; i < playersCards.size(); i++){
        cout << i+1 << ". " << playersCards[i]->name << endl;
    }
}
//leaving blank for now as CP lists are more important
void HumanPlayer::removePlayersCardsFromList() {}
//method to move the HumanPlayer around the board; movement is based on connected rooms (each room has either two or three connected rooms to move to). This method updates the playerLocation property.
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
//method for HumanPlayer to make an accusation; returns a TypeCollection pointer if user wants to make an accusation, else returns NULL
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
//method for HumanPlayer to make a suggestion; returns a TypeCollection pointer if user wants to make an suggestion, else returns NULL. Location MUST be the player's current location, the other two TypeCollection properties are selected by the user
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
//method to check if any of the HumanPlayer's cards can disprove someone's suggestion; if yes and there is more than one, HumanPlayer selects which to use and that card is returned. If yes and there is only one, HumanPlayer is informed that card will be used and that card is returned. If no, returns NULL
Card* HumanPlayer::disproveSuggestion(TypeCollection suggestion, Player* currentPlayer) {
    vector<Card*> cardsThatDisprove;
    for(int x = 0; x < playersCards.size(); x++){
        Card* currentCard = playersCards[x];
        if (playersCards[x]->type == Weapon) {
            WeaponCard* currentWeaponCard = (WeaponCard*)currentCard;
            if (currentWeaponCard->weaponType == suggestion.weaponUsed) {
                cardsThatDisprove.push_back(currentWeaponCard);
            }
        }
        if (playersCards[x]->type == Suspect) {
            SuspectCard* currentSuspectCard = (SuspectCard*)currentCard;
            if (currentSuspectCard->characterType == suggestion.suspectUsed) {
                cardsThatDisprove.push_back(currentSuspectCard);
            }
        }
        if (playersCards[x]->type == Location) {
            LocationCard* currentLocationCard = (LocationCard*)currentCard;
            if (currentLocationCard->locationType == suggestion.locationUsed) {
                cardsThatDisprove.push_back(currentLocationCard);
            }
        }
    }
    if (!cardsThatDisprove.empty()) {
        if (cardsThatDisprove.size() == 1) {
            cout << "You have one card that can disprove the suggestion. It is the " << cardsThatDisprove[0]->name << ". This card will be shown to  " << currentPlayer->name << "." << endl;
            return cardsThatDisprove[0];
        }
        else {
            cout << "You have multiple cards that can disprove this suggestion. Please select which card you would like to use to show " << currentPlayer->name << "."  << endl;
            for (int i = 0; i < cardsThatDisprove.size(); i++) {
                Card* card = cardsThatDisprove[i];
                cout << i << ". " << card->name << endl;
                
            }
            while(1){
                int playersChoice = getIntFromConsole();
                if (playersChoice >= 0 && playersChoice < cardsThatDisprove.size()) {
                    cout << "You have shown the " << cardsThatDisprove[playersChoice]->name << endl;
                    return cardsThatDisprove[playersChoice];
                }
                else cout << "Not a valid entry. Please choose a valid number" << endl;
            }
        }
    }
    else {
        cout<<"You do not have any cards that could disprove the suggestion."<<endl;
        return NULL;
    }
    }

//if a card from another player has disproved HumanPlayer's suggestion, this method will tell them what player has disproved them and with which card
void HumanPlayer::suggestionDisproved(Player* player, Card* disprovingCard) {
    cout << player->name << " has proved your suggestion wrong by showing you " << disprovingCard->name << endl;
}
void HumanPlayer::cheat(Envelope* envelope) {}

//ComputerPlayer subclass implementation
//CONSTRUCTOR
ComputerPlayer::ComputerPlayer(CharacterType type) : Player(type) {}
//METHODS
//ComputerPlayer selects which room to start in by picking a random number, one of two(each character type can start in one of two rooms)
void ComputerPlayer::chooseStartingLocation(Board* board) {
    StartingLocations startingLocations = getStartingLocations(identity);
    int selectedLocation = getRandomNumber(1);
    Room *room;
    if (selectedLocation == 0) {
        room = findRoomWithIdentity(startingLocations.choiceOne, board->rooms);
    }
    else if (selectedLocation == 1) {
        room = findRoomWithIdentity(startingLocations.choiceTwo, board->rooms);
    }
    if (room != NULL) {
        playerLocation = room;
        cout << name << " has chosen to start in the " << playerLocation->name << endl;
    }
}
//this method does nothing because the ComputerPlayer's cards do not need to be printed out
void ComputerPlayer::printOutCards() {}
//this method removes the cards that the ComputerPlayer has been dealt from their lists
void ComputerPlayer::removePlayersCardsFromList(){
    for (int i = 0; i <playersCards.size(); i++) {
        Card* currentCard = playersCards[i];
        if (playersCards[i]->type == Weapon) {
            WeaponCard* currentWeaponCard = (WeaponCard*)currentCard;
            for (int j = 0; j < weaponsList.size(); j++) {
                WeaponCard* cardToCompare = weaponsList[j];
                if (currentWeaponCard->weaponType == cardToCompare->weaponType) {
                    weaponsList.erase(weaponsList.begin()+j);
                }
            }
        }
        if (playersCards[i]->type == Suspect) {
            SuspectCard* currentSuspectCard = (SuspectCard*)currentCard;
            for (int j = 0; j < suspectsList.size(); j++) {
                SuspectCard* cardToCompare = suspectsList[j];
                if (currentSuspectCard->characterType == cardToCompare->characterType) {
                    suspectsList.erase(suspectsList.begin()+j);
                }
            }
        }
        if (playersCards[i]->type == Location) {
            LocationCard* currentLocationCard = (LocationCard*)currentCard;
            for (int j = 0; j < locationsList.size(); j++) {
                LocationCard* cardToCompare = locationsList[j];
                if (currentLocationCard->locationType == cardToCompare->locationType) {
                    locationsList.erase(locationsList.begin()+j);
                }
            }
        }

    }
}
//method to move the ComputerPlayer around the board; movement is based on connected rooms (each room has either two or three connected rooms to move to) so ComputerPlayer picks a random number to correspond to which room to move to. This method updates the playerLocation property.
void ComputerPlayer::move() {
    vector<Room*> possibleRooms;
    for (int i = 0; i < locationsList.size(); i++) {
        LocationType targetLocation = locationsList[i]->locationType;
        Room *targetRoom = findRoomWithIdentity(targetLocation, playerLocation->connectedRooms);
        if (targetRoom != NULL) {
            possibleRooms.push_back(targetRoom);
        }
    }
    
    if (possibleRooms.size() == 1) {
        playerLocation = possibleRooms[0];
    } else {
        int newLocation = getRandomNumber(playerLocation->connectedRooms.size()-1);
        playerLocation = playerLocation->connectedRooms[newLocation];
    }

    cout << name << " has moved to the " << playerLocation->name << endl;
}
//method for ComputerPlayer to make an accusation; returns a TypeCollection pointer if ComputerPlayer can make an accusation (if list is down to one item of each type), else returns NULL
TypeCollection* ComputerPlayer::makeAccusation() {
    if (weaponsList.size() == 1 && suspectsList.size() == 1 && locationsList.size() == 1) {
        TypeCollection *accusation = new TypeCollection;
        accusation->weaponUsed = weaponsList[0]->weaponType;
        accusation->suspectUsed = suspectsList[0]->characterType;
        accusation->locationUsed = locationsList[0]->locationType;
        
        cout << name << " has accused " << getCharacterTypeString(accusation->suspectUsed) <<
        " of commiting the murder in the " << getLocationTypeString(accusation->locationUsed) <<
        " with the " << getWeaponTypeString(accusation->weaponUsed) << endl;
        
        return accusation;
    }
    cout << name << " did not make an accusation." << endl;
    return NULL;
}
//method for ComputerPlayer to make a suggestion; returns a TypeCollection pointer (ComputerPlayer will always make a random suggestion of a random weapon, suspect, and the room they are in)
TypeCollection* ComputerPlayer::makeSuggestion() {
    TypeCollection* computerSuggestion = new TypeCollection;
    int randomWeapon = getRandomNumber(weaponsList.size()-1);
    computerSuggestion->weaponUsed = weaponsList[randomWeapon]->weaponType;
    int randomCharacter = getRandomNumber(suspectsList.size()-1);
    computerSuggestion->suspectUsed = suspectsList[randomCharacter]->characterType;
    computerSuggestion->locationUsed = playerLocation->identity;
    cout << name << " has suggested the killer was " << getCharacterTypeString(computerSuggestion->suspectUsed) <<  " in the "<< getLocationTypeString(computerSuggestion->locationUsed) << " with the " << getWeaponTypeString(computerSuggestion->weaponUsed) << "." << endl;
    return computerSuggestion;
}
//method to check if any of the ComputerPlayer's cards can disprove someone's suggestion; if yes returns the first card found that disproves it. If no, returns NULL
Card* ComputerPlayer::disproveSuggestion(TypeCollection suggestion, Player* currentPlayer) {
    for (int i = 0; i < playersCards.size(); i++) {
        Card* card = playersCards[i];
        if (card->type == Weapon) {
            WeaponCard* weaponCard = (WeaponCard *)card;
            if (weaponCard->weaponType == suggestion.weaponUsed) return weaponCard;
        }
        if (card->type == Suspect) {
            SuspectCard *suspectCard = (SuspectCard *)card;
            if (suspectCard->characterType == suggestion.suspectUsed) return suspectCard;
        }
        if (card->type == Location) {
            LocationCard *locationCard = (LocationCard*)card;
            if(locationCard->locationType == suggestion.locationUsed) return locationCard;
        }
    }
    
    return NULL;
}
//if a card from another player has disproved ComputerPlayer's suggestion, this method remove the disprovingCard from their list
void ComputerPlayer::suggestionDisproved(Player* player, Card* disprovingCard) {
    cout << player->name << " has disproved " << name << "'s suggestion." << endl;
    if (disprovingCard->type == Weapon) {
        WeaponCard* disprovingWeaponCard = (WeaponCard*)disprovingCard;
        for(int i=0; i<weaponsList.size(); i++) {
            if(disprovingWeaponCard->weaponType == weaponsList[i]->weaponType) {
                weaponsList.erase(weaponsList.begin()+i);
            }
        }
    } else if (disprovingCard->type == Suspect) {
        SuspectCard* disprovingSuspectCard = (SuspectCard*)disprovingCard;
        for(int i=0; i<suspectsList.size(); i++) {
            if(disprovingSuspectCard->characterType == suspectsList[i]->characterType) {
                suspectsList.erase(suspectsList.begin()+i);
            }
        }
    } else if (disprovingCard->type == Location) {
        LocationCard* disprovingLocationCard = (LocationCard*)disprovingCard;
        for(int i=0; i<locationsList.size(); i++) {
            if(disprovingLocationCard->locationType == locationsList[i]->locationType) {
                locationsList.erase(locationsList.begin()+i);
            }
        }
    }
}

void ComputerPlayer::cheat(Envelope* envelope) {

    int randomNumber = getRandomNumber(3);
    
    if (randomNumber == 0) {
        locationsList.erase(locationsList.begin(), locationsList.end());
        locationsList.push_back(new LocationCard(envelope->envelopeCards.locationUsed));
    } else if (randomNumber == 1) {
        weaponsList.erase(weaponsList.begin(), weaponsList.end());
        weaponsList.push_back(new WeaponCard(envelope->envelopeCards.weaponUsed));
    } else if (randomNumber == 2) {
        suspectsList.erase(suspectsList.begin(), suspectsList.end());
        suspectsList.push_back(new SuspectCard(envelope->envelopeCards.suspectUsed));
    }
}

