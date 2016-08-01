//
//  Envelope.cpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#include "Envelope.h"

//CONSTRUCTOR
//envelope consists of one Type Collection that includes one card of each type
Envelope::Envelope(WeaponType weaponUsed, CharacterType suspectUsed, LocationType locationUsed) {
    envelopeCards.weaponUsed = weaponUsed;
    envelopeCards.suspectUsed = suspectUsed;
    envelopeCards.locationUsed = locationUsed;
}
//METHODS
//method to check if an accusation was correct, returns true if correct, else false
bool Envelope::checkAccusation(TypeCollection accusation) {
    if (envelopeCards.weaponUsed == accusation.weaponUsed && envelopeCards.suspectUsed == accusation.suspectUsed && envelopeCards.locationUsed == accusation.locationUsed) {
        return true;
    }
    else return false;
}
//method to print the cards in the envelope
void Envelope::debugPrintEnvelope() {
    cout << "The weapon card in the envelope is the " << getWeaponTypeString(envelopeCards.weaponUsed) << endl;
    cout << "The suspect card in the envelope is " << getCharacterTypeString(envelopeCards.suspectUsed) << endl;
    cout << "The location card in the envelope is the " << getLocationTypeString(envelopeCards.locationUsed) << endl;
}
