
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

class Room {
public:
    string name;
    string abbreviation;
    vector<Room*> connectedRooms;
    void addConnectedRoom(Room* room) {
        connectedRooms.push_back(room);
    };
    Room(string roomName, string roomAbbreviation) {
        name = roomName;
        abbreviation = roomAbbreviation;
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

Room* findRoomWithAbbreviation(string abbreviation, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->abbreviation.compare(abbreviation) == 0){
            return rooms[i];
        }
    }
    return NULL;
}


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
        Room* kitchen = new Room("Kitchen", "K");
        Room* ballroom = new Room("Ballroom", "B");
        Room* conservatory = new Room("Conservatory", "C");
        Room* billiardRoom = new Room("Billiard Room", "BR");
        Room* library = new Room("Library", "L");
        Room* study = new Room("Study", "S");
        Room* hall = new Room("Hall", "H");
        Room* lounge = new Room("Lounge", "LO");
        Room* diningRoom = new Room("Dining Room", "D");
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

class Player {
public:
    string name;
    Room* playerLocation;
    Player(string playerName) {
        name = playerName;
    }
    void move(){
        string newLocation;
        cout << "You are currently in the " << playerLocation->name << "." << endl;
        cout << "From here, you can move to the ";
        for (int i = 0; i < playerLocation->connectedRooms.size(); i++) {
            cout << playerLocation->connectedRooms[i]->name << " (" << playerLocation->connectedRooms[i]->abbreviation << "), " << endl;
        }
        cout << "Please enter the abbreviation of the room you would like to move to." << endl;
        cin >> newLocation;
        Room* newRoom = findRoomWithAbbreviation(newLocation, playerLocation->connectedRooms);
        if (newRoom != NULL) {
            playerLocation = newRoom;
        }
        
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(string playerName) : Player(playerName) {

    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(string playerName) : Player(playerName) {
        
    }
};

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

enum SuspectType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};

string getSuspectTypeString(SuspectType type) {
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
    SuspectType suspectType;
    SuspectCard(SuspectType type) : Card(Suspect) {
        suspectType = type;
    }
};

class LocationCard : public Card {
public:
    LocationType locationType;
    LocationCard(LocationType type) : Card(Location) {
        locationType = type;
    }
};


vector<Card*> confidential;

class Envelope{
public:
    void printConfidential(){
        for (int i = 0; i < confidential.size(); i++) {
            Card* card = confidential[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }else if(card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout << "We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }else if (card->type == Location){
                LocationCard* location = (LocationCard*)card;
                cout << "We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
    }
};

vector<Card*> cards;

class WeaponDeck {
public:
    vector<Card*> weaponCards;
    WeaponDeck() {
        for(int i = 0; i<NUM_WEAPONS; i++){
            WeaponCard* card = new WeaponCard((WeaponType)i);
            weaponCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(weaponCards.begin(), weaponCards.end(), default_random_engine((unsigned)seed));
        confidential.push_back(weaponCards.back());
        weaponCards.pop_back();
        for(int i = 0; i<weaponCards.size(); i++){
            cards.push_back(weaponCards[i]);
        }
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
    vector<Card*> suspectCards;
    SuspectDeck() {
        for(int i = 0; i<NUM_SUSPECTS; i++){
            SuspectCard* card = new SuspectCard((SuspectType)i);
            suspectCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(suspectCards.begin(), suspectCards.end(), default_random_engine((unsigned)seed));
        confidential.push_back(suspectCards.back());
        suspectCards.pop_back();
        for(int i = 0; i<suspectCards.size(); i++){
            cards.push_back(suspectCards[i]);
        }
    }
    
    void printSuspectDeck(){
        for (int i = 0; i < suspectCards.size(); i++) {
            Card* card = suspectCards[i];
            if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }
        }
    }
    
};

class LocationDeck {
public:
    vector<Card*> locationCards;
    LocationDeck() {
        for(int i = 0; i<NUM_LOCATIONS; i++){
            LocationCard* card = new LocationCard((LocationType)i);
            locationCards.push_back(card);
        }
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(locationCards.begin(), locationCards.end(), default_random_engine((unsigned)seed));
        confidential.push_back(locationCards.back());
        locationCards.pop_back();
        for(int i = 0; i<locationCards.size(); i++){
            cards.push_back(locationCards[i]);
        }
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
    /* vector<Card*> cards;
     Deck() {
     for (int i = 0; i < NUM_WEAPONS; i++) {
     WeaponCard* card = new WeaponCard((WeaponType)i);
     cards.push_back(card);
     }
     
     for (int i = 0; i < NUM_SUSPECTS; i++) {
     SuspectCard* card = new SuspectCard((SuspectType)i);
     cards.push_back(card);
     }
     
     
     for (int i = 0; i < NUM_LOCATIONS; i++) {
     LocationCard* card = new LocationCard((LocationType)i);
     cards.push_back(card);
     }
     }*/
    void debugPrint() {
        for (int i = 0; i < cards.size(); i++) {
            Card* card = cards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
            else if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }
            else if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
        
    }
    
    void shuffle(){
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(), cards.end(), default_random_engine((unsigned)seed));
    }
};

class Accusation{
public:
    bool checkAccusationisCorrect(string killer1, string weaponused1, string crimescene1){// order of cards is weapon, suspect, location
        string weaponconfidential;
        string suspectconfidential;
        string locationconfidential;
        for (int q = 0; q <confidential.size(); q++){
            if (confidential[q]->type == Weapon){
                WeaponCard* weapon1 = (WeaponCard*)confidential[q];
                weaponconfidential = getWeaponTypeString(weapon1->weaponType);
            }else if( confidential[q]-> type == Suspect){
                SuspectCard* suspect1 = (SuspectCard*)confidential[q];
                suspectconfidential = getSuspectTypeString(suspect1->suspectType);
            }else if( confidential[q]->type == Location){
                LocationCard* location1 = (LocationCard*)confidential[q];
                locationconfidential = getLocationTypeString(location1->locationType);
            }
        }
        if ((weaponused1 == weaponconfidential) && (killer1 == suspectconfidential)&&(crimescene1==locationconfidential)){ return true;}
        return false;
    }
    
};

class Suggestion{
public:
    bool CheckSuggestion();
    
};

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
    cout << "Which character would you like to be (enter player number): " << endl;
    for (int i = 0; i < NUM_SUSPECTS; i++) {
        cout << i << ". " << getSuspectTypeString((SuspectType)i) << endl;
    }
    while(1) {
        cin >> humanPlayerSelection;
        if (humanPlayerSelection >= 0 && humanPlayerSelection < NUM_SUSPECTS) {
            Player* player = new HumanPlayer(getSuspectTypeString((SuspectType)humanPlayerSelection));
            players.push_back(player);
            break;
        }
        else {
            cout << "Not a valid number. Please enter a valid character number." << endl;
        }
    }
    //adding remaining characters to a temporary vector
    vector<int> charactersLeftToPick;
    for (int i = 0; i < 5; i ++) {
        if (i != humanPlayerSelection) {
            charactersLeftToPick.push_back(i);
        }
    }
    //shuffling the temporary vector
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(charactersLeftToPick.begin(), charactersLeftToPick.end(), default_random_engine((unsigned)seed));
    //creating computer players
    for (int i = 0; i < numberOfComputerPlayers; i++) {
        Player* player = new ComputerPlayer(getSuspectTypeString((SuspectType)charactersLeftToPick.back()));
        players.push_back(player);
        charactersLeftToPick.pop_back();
    }
    //showing who is playing
    cout << "This game's players are: " << endl;
    for (int i = 0; i < players.size(); i++) {
        cout << players[i]->name << endl;
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
