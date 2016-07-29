
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
# include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

enum CardType {
    Weapon,
    Suspect,
    Location
};

#define NUM_WEAPONS 6

enum WeaponType {
    Candlestick,
    Knife,
    LeadPipe,
    Revolver,
    Rope,
    Wrench
};

string getWeaponTypeString(WeaponType type) {
    switch (type) {
        case Candlestick:
            return "Candlestick";
        case Knife:
            return "Knife";
        case LeadPipe:
            return "Lead Pipe";
        case Revolver:
            return "Revolver";
        case Rope:
            return "Rope";
        case Wrench:
            return "Wrench";
    }
}

#define NUM_SUSPECTS 6

enum CharacterType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};

string getCharacterTypeString(CharacterType type) {
    switch (type) {
        case Scarlet:
            return "Miss Scarlet";
        case Mustard:
            return "Colonel Mustard";
        case White:
            return "Mrs. White";
        case Green:
            return "Mr. Green";
        case Peacock:
            return "Mrs. Peacock";
        case Plum:
            return "Professor Plum";
    }
}

#define NUM_LOCATIONS 9

enum LocationType {
    Kitchen,
    Ballroom,
    Conservatory,
    BilliardRoom,
    Library,
    Study,
    Hall,
    Lounge,
    DiningRoom
};

string getLocationTypeString(LocationType type) {
    switch (type) {
        case Kitchen:
            return "Kitchen";
        case Ballroom:
            return "Ballroom";
        case Conservatory:
            return "Conservatory";
        case BilliardRoom:
            return "Billiard Room";
        case Library:
            return "Library";
        case Study:
            return "Study";
        case Hall:
            return "Hall";
        case Lounge:
            return "Lounge";
        case DiningRoom:
            return "Dining Room";
    }
};


class Room {
public:
    string name;
    vector<Room*> connectedRooms;
    LocationType identity;
    void addConnectedRoom(Room* room) {
        connectedRooms.push_back(room);
    };
    Room(LocationType type) {
        name = getLocationTypeString(type);
        identity = type;
    };
    void debugPrint() {
        cout << "This room is the " << name << endl;
        cout << "It is connected to the ";
        for (int i = 0; i < connectedRooms.size(); i++) {
            cout << connectedRooms[i]->name << ", ";
        }
        cout << endl;
    };
    
};


class Board {
public:
    vector<Room*> rooms;
    void addRoom(Room* roomToAdd) {
        rooms.push_back(roomToAdd);
    };
    void debugPrint() {
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->debugPrint();
        }
    };
    Board() {
        Room* kitchen = new Room(Kitchen);
        Room* ballroom = new Room(Ballroom);
        Room* conservatory = new Room(Conservatory);
        Room* billiardRoom = new Room(BilliardRoom);
        Room* library = new Room(Library);
        Room* study = new Room(Study);
        Room* hall = new Room(Hall);
        Room* lounge = new Room(Lounge);
        Room* diningRoom = new Room(DiningRoom);
        addRoom(kitchen);
        addRoom(ballroom);
        addRoom(conservatory);
        addRoom(billiardRoom);
        addRoom(library);
        addRoom(study);
        addRoom(hall);
        addRoom(lounge);
        addRoom(diningRoom);
        kitchen->addConnectedRoom(ballroom);
        kitchen->addConnectedRoom(diningRoom);
        kitchen->addConnectedRoom(study);
        ballroom->addConnectedRoom(kitchen);
        ballroom->addConnectedRoom(conservatory);
        conservatory->addConnectedRoom(ballroom);
        conservatory->addConnectedRoom(billiardRoom);
        conservatory->addConnectedRoom(lounge);
        billiardRoom->addConnectedRoom(conservatory);
        billiardRoom->addConnectedRoom(library);
        library->addConnectedRoom(billiardRoom);
        library->addConnectedRoom(study);
        study->addConnectedRoom(library);
        study->addConnectedRoom(hall);
        study->addConnectedRoom(kitchen);
        hall->addConnectedRoom(study);
        hall->addConnectedRoom(lounge);
        lounge->addConnectedRoom(hall);
        lounge->addConnectedRoom(diningRoom);
        lounge->addConnectedRoom(conservatory);
        diningRoom->addConnectedRoom(lounge);
        diningRoom->addConnectedRoom(kitchen);
    }
    
};

Room* findRoomWithIdentity(LocationType type, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++){
        if (rooms[i]->identity == type) {
            return rooms[i];
        }
    }
    return NULL;
}

class Player {
public:
    string name;
    CharacterType identity;
    Room* playerLocation;
    Player(CharacterType type) {
        name = getCharacterTypeString(type);
        identity = type;
    }
    void move(){
        int newLocation;
        cout << "You are currently in the " << playerLocation->name << "." << endl;
        cout << "From here, you can move to the ";
        for (int i = 0; i < playerLocation->connectedRooms.size(); i++) {
            LocationType currentRoomIdentity = playerLocation->connectedRooms[i]->identity;
            cout << currentRoomIdentity << ". " << playerLocation->connectedRooms[i]->name << endl;
        }
        while(1){
            cout << "Please enter the number of the room you would like to move to." << endl;
            cin >> newLocation;
            Room* newRoom = findRoomWithIdentity((LocationType)newLocation, playerLocation->connectedRooms);
            if (newRoom != NULL) {
                playerLocation = newRoom;
                break;
            }
            cout << "Not a valid number. Please try again." << endl;
        }
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(CharacterType type) : Player(type) {

    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(CharacterType type) : Player(type) {
        
    }
};


class Card {
public:
    CardType type;
    Card(CardType t) {
        type = t;
    }
};

class WeaponCard : public Card {
public:
    WeaponType weaponType;
    WeaponCard(WeaponType type) : Card(Weapon) {
        weaponType = type;
    }
};

class SuspectCard : public Card {
public:
    CharacterType characterType;
    SuspectCard(CharacterType type) : Card(Suspect) {
        characterType = type;
    }
};

class LocationCard : public Card {
public:
    LocationType locationType;
    LocationCard(LocationType type) : Card(Location) {
        locationType = type;
    }
};

struct TypeCollection {
    WeaponType weaponUsed;
    CharacterType suspectUsed;
    LocationType locationUsed;
};

class Envelope{
public:
    TypeCollection envelopeCards;
    Envelope(WeaponType weaponUsed, CharacterType suspectUsed, LocationType locationUsed) {
        envelopeCards.weaponUsed = weaponUsed;
        envelopeCards.suspectUsed = suspectUsed;
        envelopeCards.locationUsed = locationUsed;
    }
    
    void debugPrintEnvelope() {
        cout << "The weapon card in the envelope is the " << getWeaponTypeString(envelopeCards.weaponUsed) << endl;
        cout << "The suspect card in the envelope is " << getCharacterTypeString(envelopeCards.suspectUsed) << endl;
        cout << "The location card in the envelope is the " << getLocationTypeString(envelopeCards.locationUsed) << endl;
    }
};



class WeaponDeck {
public:
    vector<WeaponCard*> weaponCards;
    //constructs and shuffles the WeaponDeck
    WeaponDeck() {
        for(int i = 0; i<NUM_WEAPONS; i++){
            WeaponCard* card = new WeaponCard((WeaponType)i);
            weaponCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(weaponCards.begin(), weaponCards.end(), default_random_engine((unsigned)seed));
    }
    WeaponCard* getRandomCard() {
        WeaponCard* randomWeaponCard = weaponCards.back();
        weaponCards.pop_back();
        return randomWeaponCard;
    }
    
    void printWeaponDeck(){
        for (int i = 0; i < weaponCards.size(); i++) {
            Card* card = weaponCards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
        }
    }
    
};

class SuspectDeck {
public:
    vector<SuspectCard*> suspectCards;
    //constructs and shuffles the SuspectDeck
    SuspectDeck() {
        for(int i = 0; i<NUM_SUSPECTS; i++){
            SuspectCard* card = new SuspectCard((CharacterType)i);
            suspectCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(suspectCards.begin(), suspectCards.end(), default_random_engine((unsigned)seed));
    }
    SuspectCard* getRandomCard(){
        SuspectCard* randomSuspectCard = suspectCards.back();
        suspectCards.pop_back();
        return randomSuspectCard;
    }
    void printSuspectDeck(){
        for (int i = 0; i < suspectCards.size(); i++) {
            Card* card = suspectCards[i];
            if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getCharacterTypeString(suspect->characterType)  << endl;
            }
        }
    }
    
};

class LocationDeck {
public:
    vector<LocationCard*> locationCards;
    //constructs and shuffles the LocationDeck
    LocationDeck() {
        for(int i = 0; i<NUM_LOCATIONS; i++){
            LocationCard* card = new LocationCard((LocationType)i);
            locationCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(locationCards.begin(), locationCards.end(), default_random_engine((unsigned)seed));
    }
    LocationCard* getRandomCard(){
        LocationCard* randomLocationCard = locationCards.back();
        locationCards.pop_back();
        return randomLocationCard;
    }
    void printLocationDeck(){
        for (int i = 0; i < locationCards.size(); i++) {
            Card* card = locationCards[i];
            if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
    }
    
};

class Deck {
public:
    vector<Card*> cards;
    //constructs the Deck from the cards left in each Type Deck after selecting the killer cards
     Deck(WeaponDeck weaponDeck, SuspectDeck suspectDeck, LocationDeck locationDeck) {
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
    void debugPrintDeck() {
        for (int i = 0; i < cards.size(); i++) {
            Card* card = cards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
            else if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getCharacterTypeString(suspect->characterType)  << endl;
            }
            else if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }

    }
};

//class Accusation{
//public:
//    bool checkAccusationisCorrect(string killer1, string weaponused1, string crimescene1){// order of cards is weapon, suspect, location
//        string weaponconfidential;
//        string suspectconfidential;
//        string locationconfidential;
//        for (int q = 0; q <confidential.size(); q++){
//            if (confidential[q]->type == Weapon){
//                WeaponCard* weapon1 = (WeaponCard*)confidential[q];
//                weaponconfidential = getWeaponTypeString(weapon1->weaponType);
//            }else if( confidential[q]-> type == Suspect){
//                SuspectCard* suspect1 = (SuspectCard*)confidential[q];
//                suspectconfidential = getCharacterTypeString(suspect1->characterType);
//            }else if( confidential[q]->type == Location){
//                LocationCard* location1 = (LocationCard*)confidential[q];
//                locationconfidential = getLocationTypeString(location1->locationType);
//            }
//        }
//        if ((weaponused1 == weaponconfidential) && (killer1 == suspectconfidential)&&(crimescene1==locationconfidential)){ return true;}
//        return false;
//    }
//    
//};

class Suggestion{
public:
    bool CheckSuggestion();
    
};

//function to compare the order of two players; returns true if playerOne goes before playerTwo, otherwise false
bool isOrderedBefore(Player* playerOne, Player* playerTwo) {
    if (playerOne->identity < playerTwo->identity) {
        return true;
    }
    else return false;
}

int main(int argc, const char * argv[]) {
    char input;
    char input1;
    string killer;
    string weaponused;
    string crimescene;
    string suspect;
    string suspectedweapon;
    int numberOfComputerPlayers;
    int humanPlayerSelection;
    
    
    Board clueBoard;
    vector<Player*> players;
    //user inputs how many computer players will be playing
    cout << "Welcome to Clue! First, select how many computer players you will be playing against (2-5)" << endl;
    while (1) {
        cin >> numberOfComputerPlayers;
        if (numberOfComputerPlayers >= 2 && numberOfComputerPlayers <= 5){
            break;
        }
        else {
            cout << "Not a valid number. Please enter a number between 2 and 5." << endl;
        }
    }
    //user selects his/her character
    cout << "Which character would you like to be (enter player number): " << endl;
    for (int i = 0; i < NUM_SUSPECTS; i++) {
        cout << i << ". " << getCharacterTypeString((CharacterType)i) << endl;
    }
    //user's character is added to players vector
    while(1) {
        cin >> humanPlayerSelection;
        if (humanPlayerSelection >= 0 && humanPlayerSelection < NUM_SUSPECTS) {
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
    for (int i = 0; i < 5; i ++) {
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
    //shows who is playing
    cout << "This game's players are: " << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << players[i]->name << endl;
    }
    //puts the players vector back in playing order
    sort(players.begin(), players.end(), isOrderedBefore);
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
    fullDeck.debugPrintDeck();
    confidential.debugPrintEnvelope();
    
    
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
