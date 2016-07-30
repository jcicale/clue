
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
    
    
    Board clueBoard;
    vector<Player*> players;
    //user inputs how many computer players will be playing
    cout << "Welcome to Clue! First, select how many computer players you will be playing against (2-5)" << endl;
    while (1) {
        numberOfComputerPlayers = getIntFromConsole();
        if (numberOfComputerPlayers >= 2 && numberOfComputerPlayers <= 5){
            break;
        }
        else {
            cout << "Not a valid number. Please enter a number between 2 and 5." << endl;
        }
    }
    //user selects his/her character
    cout << "Which character would you like to be (enter player number): " << endl;
    for (int i = 0; i < NUM_CHARACTERS; i++) {
        cout << i << ". " << getCharacterTypeString((CharacterType)i) << endl;
    }
    //user's character is added to players vector
    while(1) {
        humanPlayerSelection = getIntFromConsole();
        if (humanPlayerSelection >= 0 && humanPlayerSelection < NUM_CHARACTERS) {
            CharacterType selectedType = (CharacterType)humanPlayerSelection;
            Player* player = new HumanPlayer(selectedType);
            players.push_back(player);
            break;
        }
        else {
            cout << "Not a valid number. Please enter a valid character number." << endl;
        }
    }
    //adds remaining characters to a temporary vector
    vector<int> charactersLeftToPick;
    for (int i = 0; i < NUM_CHARACTERS; i ++) {
        if (i != humanPlayerSelection) {
            charactersLeftToPick.push_back(i);
        }
    }
    //shuffles the temporary vector
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(charactersLeftToPick.begin(), charactersLeftToPick.end(), default_random_engine((unsigned)seed));
    //creates computer players
    for (int i = 0; i < numberOfComputerPlayers; i++) {
        CharacterType computerType = (CharacterType)charactersLeftToPick.back();
        Player* player = new ComputerPlayer(computerType);
        players.push_back(player);
        charactersLeftToPick.pop_back();
    }
    //puts the players vector back in playing order
    sort(players.begin(), players.end(), isOrderedBefore);
    
    //shows who is playing
    cout << "This game's players are: " << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << players[i]->name << endl;
    }
    
    //puts human player in his/her starting position
    
    //creates each Type Deck
    WeaponDeck weaponDeck;
    SuspectDeck suspectDeck;
    LocationDeck locationDeck;
    //pulls a random card from each
    WeaponType weaponUsed = weaponDeck.getRandomCard()->weaponType;
    CharacterType suspectUsed = suspectDeck.getRandomCard()->characterType;
    LocationType locationUsed = locationDeck.getRandomCard()->locationType;
    //creates the Envelope with the three killer cards
    Envelope confidential(weaponUsed, suspectUsed, locationUsed);
    //creates the full Deck with all Card Types
    Deck fullDeck(weaponDeck, suspectDeck, locationDeck);
    for (int i = 0; i < players.size(); i ++) {
        players[i]->chooseStartingLocation(clueBoard);
    }
    fullDeck.dealCards(players);
    while (1) {
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->name << " is up." << endl;
            TypeCollection* accusation = players[i]->makeAccusation();
            if (accusation != NULL) {
                if (confidential.checkAccusation(*accusation)) {
                    cout << "You have correctly identified the killer. You win!" << endl;
                }
                else cout << "Your accusation was incorrect. The correct answer was "<< getCharacterTypeString(confidential.envelopeCards.suspectUsed) << " in the " << getLocationTypeString(confidential.envelopeCards.locationUsed) << " with the " << getWeaponTypeString(confidential.envelopeCards.weaponUsed)  <<  ". Game over!" << endl;
                exit(0);
                //Check the accusation?
            }
            players[i]->move();
            TypeCollection* suggestion = players[i]->makeSuggestion();
            if (suggestion != NULL) {

                //Check the suggestion?
            }
            cout << players[i]->name << "'s turn has ended. " << players
            [i]->name << " is in the " << players[i]->playerLocation->name << endl;
        }
        
    }

    
    
//    while (1) {
//        cout<< "Would you Like to make an Accusation? (y/n)"<<endl;
//        cin >> input1;
//        if( input1 == 'y'){
//            cout<< "The Murderer is: "<<endl;
//            cin.ignore();
//            getline(cin, killer);
//            cout<< "The Weapon the murderer used to Kill is: "<<endl;
//            getline(cin, weaponused);
//            cout<< "The Room the murderer murdered Mr. Boddy is: "<<endl;
//            getline(cin, crimescene);
//            Accusation accuser;
//            if( accuser.checkAccusationisCorrect(killer, weaponused, crimescene) == true){ cout<<"You WIN!!!"<<endl; break;}
//            else{ cout<<" You lose! GAME OVER!!"<<endl; break;}
//        };
//        
//        player->move();
//        
//        cout<< " Would you like to make a suggestion? (y/n) "<< endl;
//        cin>> input;
//        if( input == 'y'){
//            cout<< "Who is the suspect? "<<endl;
//            cin>> suspect;
//            cout<< "what is the suspected weapon? "<<endl;
//            cin >> suspectedweapon;
//            
//        }
//        
//    }
    
    return 0;
}
