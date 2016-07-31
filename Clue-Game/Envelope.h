//
//  Envelope.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef Envelope_h
#define Envelope_h

#include <stdio.h>
#include "Card.h"

//holds the three killer cards
class Envelope{
public:
    TypeCollection envelopeCards;
    
    Envelope(WeaponType weaponUsed, CharacterType suspectUsed, LocationType locationUsed);
    bool checkAccusation(TypeCollection accusation);
    
    void debugPrintEnvelope();
};


#endif /* Envelope_h */
