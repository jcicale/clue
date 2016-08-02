
//
//  main.cpp
//  Clue-Game
//
//  Created by Julia on 7/16/16.
//  Copyright Â© 2016 Julia. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include "Enumerations.h"
#include "Room.h"
#include "Board.h"
#include "Utility.h"
#include "Player.h"
#include "Envelope.h"
#include "Deck.h"


int main(int argc, const char * argv[]) {
    int numberOfComputerPlayers;
    int humanPlayerSelection;

    //introductory text
    cout << "Welcome to Clue!" << endl;
    cout << "\nHere is a list of all of the Weapons, Suspects, and Locations in the game. You may want to copy them for future reference:" << endl;
    
    cout << "\nWeapons: " << endl;
    for(int i=0; i<NUM_WEAPONS; i++){
        cout << "\t" << getWeaponTypeString((WeaponType)i) << endl;
    }
    
    cout << "\nSuspects: " << endl;
    for(int i=0; i<NUM_SUSPECTS; i++){
        cout << "\t" << getSuspectTypeString((SuspectType)i) << endl;
    }
    
    cout << "\nLocations: " << endl;
    for(int i=0; i<NUM_LOCATIONS; i++){
        cout << "\t" << getLocationTypeString((LocationType)i) << endl;
    }
    //user inputs how many computer players will be playing, between 2 and 5
    cout << "\nFirst, select how many computer players you will be playing against (2-5):" << endl;
    
    while (1) {
        numberOfComputerPlayers = getIntFromConsole();
        if (numberOfComputerPlayers >= 2 && numberOfComputerPlayers <= 5){
            break;
        }
        else {
            cout << "Not a valid number. Please enter a number between 2 and 5." << endl;
        }
    }
    //creates the board
    Board* clueBoard = new Board;
    //creates empty vector of player pointers
    vector<Player*> players;
        //user selects his/her suspect type from list of suspect type enumeration
        cout << "\nWhich suspect would you like to be (enter player number): " << endl;
        for (int i = 0; i < NUM_SUSPECTS; i++) {
            cout << i << ". " << getSuspectTypeString((SuspectType)i) << endl;
        }
        //user's suspect is added to players vector
        while(1) {
            //ensuring that the input is valid
            humanPlayerSelection = getIntFromConsole();
            if (humanPlayerSelection >= 0 && humanPlayerSelection < NUM_SUSPECTS) {
                SuspectType selectedType = (SuspectType)humanPlayerSelection;
                Player* player = new HumanPlayer(selectedType);
                players.push_back(player);
                break;
            }
            else {
                cout << "Not a valid number. Please enter a valid suspect number." << endl;
            }
        }
        cout << "\nYou chose " << players[0]->name << endl;
    //all remaining suspect types are added to a temporary vector
    vector<int> suspectsLeftToPick;
    for (int i = 0; i < NUM_SUSPECTS; i ++) {
        if (i != humanPlayerSelection) {
            suspectsLeftToPick.push_back(i);
        }
    }
    //temporary vector is shuffled
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(suspectsLeftToPick.begin(), suspectsLeftToPick.end(), default_random_engine((unsigned)seed));
    //computer players created by pushing that number of elements onto players and popping them from the temp vector
    for (int i = 0; i < numberOfComputerPlayers; i++) {
        SuspectType computerType = (SuspectType)suspectsLeftToPick.back();
        Player* player = new ComputerPlayer(computerType);
        players.push_back(player);
        suspectsLeftToPick.pop_back();
    }
    //puts the players vector back in playing order
    sort(players.begin(), players.end(), isOrderedBefore);
    
    //shows who is playing
    cout << "\nThis game's players are: " << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << players[i]->name << endl;
    }
    //Deck setup
    //creates each Type Deck
    WeaponDeck weaponDeck;
    SuspectDeck suspectDeck;
    LocationDeck locationDeck;
    //pulls a random card from each
    WeaponType weaponUsed = weaponDeck.getRandomCard()->weaponType;
    SuspectType suspectUsed = suspectDeck.getRandomCard()->suspectType;
    LocationType locationUsed = locationDeck.getRandomCard()->locationType;
    //creates the Envelope with the three killer cards
    Envelope *confidential = new Envelope(weaponUsed, suspectUsed, locationUsed);
    //creates the full Deck with all Card Types
    Deck fullDeck(weaponDeck, suspectDeck, locationDeck);
    
    //puts players in their starting position
    for (int i = 0; i < players.size(); i ++) {
        players[i]->chooseStartingLocation(clueBoard);
    }
    //hands cards out to players
    fullDeck.dealCards(players);
    //removes the cards from the list of weapons/suspects/locations
    for (int i = 0; i < players.size(); i++) {
        players[i]->removePlayersCardsFromList();
        players[i]->cheat(confidential);
    }
    
    //Gameplay
    //while loop continues until someone makes an accusation and either wins or loses
    int turns = 0;
    bool gameWon = false;
    while (!gameWon) {
        //this loop iterates through the players
        for (int i = 0; i < players.size(); i++) {
            //prints the user's cards for reference
            players[i]->printOutCards();
            //prints whose turn it is
            cout << "\n" << players[i]->name << " is up." << endl;
            //player can make an accusation or not
            TypeCollection* accusation = players[i]->makeAccusation();
            //if an accusation is made, it will be checked against the envelope
            if (accusation != NULL) {
                //if correct, player wins
                if (confidential->checkAccusation(*accusation)) {
                    cout << "\n" << players[i]->name << " has correctly identified the killer. " << players[i]->name << " wins!" << endl;
                    cout << "This game took " << turns << " turns to complete!"<<endl;
                }
                //if incorrect, player loses and game ends
                else cout << "Your accusation was incorrect. The correct answer was "<< getSuspectTypeString(confidential->envelopeCards.suspectUsed) << " in the " << getLocationTypeString(confidential->envelopeCards.locationUsed) << " with the " << getWeaponTypeString(confidential->envelopeCards.weaponUsed)  <<  ". Game over!" << endl;
                gameWon = true;
                break;
            }
            //if no accusation, player moves to another room
            players[i]->move();
            //player can make a suggestion or not
            TypeCollection* suggestion = players[i]->makeSuggestion();
            if (suggestion != NULL) {
                //if a suggestion is made, move the suggested suspect to the suggested room
                Player* suggestedPlayer = findPlayerWithIdentity(players, suggestion->suspectUsed);
                clueBoard->movePlayerToRoom(suggestedPlayer, suggestion->locationUsed);
                //if a suggestion is made, iterate through players starting with player AFTER current player
                bool disproved = false;
                for (int j = i+1; j < players.size()+i; j++) {
                    //check if any players can disprove the suggestion with one of their cards
                    Card* card = players[j%players.size()]->disproveSuggestion(*suggestion, players[i]);
                    if (card != NULL) {
                        //if they can, player who made the suggestion will be shown the card that disproves it
                        disproved = true;
                        players[i]->suggestionDisproved(players[j%players.size()], card);
                        break;
                    }
                }
                //if no one can disprove current player, player has the option to make an accusation
                if (disproved == false) {
                    cout << "\n" << players[i]->name <<"'s suggestion has not been disproved. " << players[i]->name << " has the chance to make an accusation." << endl;
                    accusation = players[i]->makeAccusation();
                    if (accusation != NULL) {
                        //if correct, player wins
                        if (confidential->checkAccusation(*accusation)) {
                            cout << "\n" << players[i]->name << " has correctly identified the killer. " << players[i]->name << " wins!" << endl;
                            cout << "This game took " << turns << " turns to complete!"<<endl;
                        }
                        //if incorrect, player loses and game ends
                        else cout << "\nThat accusation was incorrect. The correct answer was "<< getSuspectTypeString(confidential->envelopeCards.suspectUsed) << " in the " << getLocationTypeString(confidential->envelopeCards.locationUsed) << " with the " << getWeaponTypeString(confidential->envelopeCards.weaponUsed)  <<  ". Game over!" << endl;
                        gameWon = true;
                        break;
                    }

                }
                delete suggestion;
            }

            //player's turn ends, informs user what room they ended up in
            cout << players[i]->name << "'s turn has ended. " << players
            [i]->name << " is in the " << players[i]->playerLocation->name << endl << endl;
            //button push to go to next player
            cout << "Please press 1 to continue to the next player's turn." << endl;
            while(1){
                int moveOn = getIntFromConsole();
                if (moveOn == 1) {
                    break;
                }
                else cout << "Invalid entry, please press 1 to continue." << endl;
            }
        }
        //increment turns counter
        turns++;
    }
    
    //cleaning up dynamically allocated memory
    for (int i = 0; i < players.size(); i++) {
        delete players[i];
    }
    
    delete clueBoard;
    delete confidential;

    return 0;
}
