//
//  Utility.h
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#include <random>
//function to handle user entering a non-numeric character
inline int getIntFromConsole() {
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
inline int getRandomNumber(int max) {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, max);
    return distr(eng);
}

//allows getRandomNumber function to work using the size of array as a parameter
inline int getRandomNumber(unsigned long max) {
    return getRandomNumber((int)max);
}


#endif /* Utility_h */
