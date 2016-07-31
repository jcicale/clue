
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

#define NUM_CHARACTERS 6

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

struct StartingLocations {
    LocationType choiceOne;
    LocationType choiceTwo;
};

StartingLocations getStartingLocations(CharacterType character) {
    StartingLocations startingLocations;
    switch (character) {
        case Scarlet:
            startingLocations.choiceOne = Hall;
            startingLocations.choiceTwo = Lounge;
            break;
        case Mustard:
            startingLocations.choiceOne = Lounge;
            startingLocations.choiceTwo = DiningRoom;
            break;
        case White:
            startingLocations.choiceOne = Kitchen;
            startingLocations.choiceTwo = Ballroom;
            break;
        case Green:
            startingLocations.choiceOne = Ballroom;
            startingLocations.choiceTwo = Conservatory;
            break;
        case Peacock:
            startingLocations.choiceOne = Conservatory;
            startingLocations.choiceTwo = BilliardRoom;
            break;
        case Plum:
            startingLocations.choiceOne = Library;
            startingLocations.choiceTwo = Study;
            break;

    }
    return startingLocations;
}

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
    void movePlayerToRoom(Player* player, LocationType location) {
        
    }
    
};

//function to return a pointer to a room based on its LocationType
Room* findRoomWithIdentity(LocationType type, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++){
        if (rooms[i]->identity == type) {
            return rooms[i];
        }
    }
    return NULL;
}

//function to handle user entering a non-numeric character
int getIntFromConsole() {
    int input;
    bool badEntry = false;
    while(1) {
        cin >> input;
        badEntry = cin.fail();
        if (badEntry) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid entry. Please enter a number." << endl;
        }
        else break;
    }
    return input;
}

//function to get a random number between 0 and max for computer player decisions
int getRandomNumber(int max) {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, max);
    return distr(eng);
}

//allows getRandomNumber function to work using the size of array as a parameter
int getRandomNumber(unsigned long max) {
    return getRandomNumber((int)max);
}

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

//these are the three Card Types that will go in the killer envelope
struct TypeCollection {
    WeaponType weaponUsed;
    CharacterType suspectUsed;
    LocationType locationUsed;
};


class Player {
public:
    string name;
    CharacterType identity;
    Room* playerLocation;
    vector<Card*> playersCards;
    Player(CharacterType type) {
        name = getCharacterTypeString(type);
        identity = type;
    }
    virtual void chooseStartingLocation(Board board) {}
    virtual void move() {}
    virtual TypeCollection* makeAccusation() {
        return NULL;
    }
    virtual TypeCollection* makeSuggestion() {
        return NULL;
    }
    virtual Card* disproveSuggestion(TypeCollection suggestion) {
        return NULL;
    }
    virtual void suggestionDisproved(TypeCollection suggestion, Card* disprovingCard) {
        
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(CharacterType type) : Player(type) {}
    void chooseStartingLocation(Board board) {
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
    void move(){
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
    
    void WeaponList(){
        vector<Card*> weaponsList;
        for (int i = 0; i < NUM_WEAPONS; i++) {
            WeaponCard* card = new WeaponCard((WeaponType)i);
            weaponsList.push_back(card);
        }
        
        cout << "Weapons: " << endl;
        for (int i = 0; i < weaponsList.size(); i++){
            Card* card = weaponsList[i];
            WeaponCard* weapon = (WeaponCard*)card;
            cout <<"\t" << getWeaponTypeString(weapon->weaponType)  << endl;

        }

    }
    
    void SuspectList(){
        vector<Card*> suspectsList;
        for (int i = 0; i < NUM_CHARACTERS; i++) {
            SuspectCard* card = new SuspectCard((CharacterType)i);
            suspectsList.push_back(card);
        }
        
        cout << "Suspects: " << endl;
        for (int i = 0; i < suspectsList.size(); i++){
            Card* card = suspectsList[i];
            SuspectCard* suspect = (SuspectCard*)card;
            cout <<"\t" << getCharacterTypeString(suspect->characterType)  << endl;
            
        }

        
    }
    
    void LocationList(){
        vector<Card*> locationsList;
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            LocationCard* card = new LocationCard((LocationType)i);
            locationsList.push_back(card);
        }
        
        cout << "Locations: " << endl;
        for (int i = 0; i < locationsList.size(); i++){
            Card* card = locationsList[i];
            LocationCard* location = (LocationCard*)card;
            cout <<"\t" << getLocationTypeString(location->locationType)  << endl;

        }

    }
    
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(CharacterType type) : Player(type) {}
    void chooseStartingLocation(Board board) {
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
    void move() {
        int newLocation = getRandomNumber(playerLocation->connectedRooms.size()-1);
        playerLocation = playerLocation->connectedRooms[newLocation];
        cout << name << " has moved to the " << playerLocation->name << endl;
    }
};




//holds the three killer cards
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
        for(int i = 0; i<NUM_CHARACTERS; i++){
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

    void dealCards(vector<Player*> players) {
        while (!cards.empty()) {
            for (int i = 0; i < players.size(); i ++) {
                if (cards.empty()) break;
                players[i]->playersCards.push_back(cards.back());
                cards.pop_back();

            }
        }
    }
};

void printCards(vector<Card*> cards) {
    for (int i = 0; i < cards.size(); i++) {
        Card* card = cards[i];
        if (card->type == Weapon) {
            WeaponCard* weapon = (WeaponCard*)card;
            cout <<"Weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
        }
        else if (card->type == Suspect) {
            SuspectCard* suspect = (SuspectCard*)card;
            cout <<"Suspect card: " << getCharacterTypeString(suspect->characterType)  << endl;
        }
        else if (card->type == Location) {
            LocationCard* location = (LocationCard*)card;
            cout <<"Location card: " << getLocationTypeString(location->locationType)  << endl;
        }
    }
    
}

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
    while (1) {
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->name << " is up." << endl;
            TypeCollection* accusation = players[i]->makeAccusation();
            if (accusation != NULL) {
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
