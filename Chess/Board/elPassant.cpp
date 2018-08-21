#include "elPassant.h"

/**
 * Default constructor
 */
ElPassant::ElPassant() {

}

/**
 * Sets the passants data with the two points on the board
 * 
 * @param attacker Attacker position
 * @param victim Victim position
 */
void ElPassant::setElPassant(QPoint attacker, QPoint victim) {
    if(!isPresent){
        this->attacker1 = attacker;
        this->victim = victim;
        isPresent = true;
    }else{
        this->attacker2 = attacker;
    }

}

/**
 *
 */
void ElPassant::clearElPassant() {
    attacker1 = QPoint(-1,-1);
    attacker2 = QPoint(-1,-1);
    victim = QPoint(-1,-1);
    isPresent = false;
}

/**
 *
 * @return
 */
QPoint ElPassant::getAttacker1() {
    return attacker1;
}

/**
 *
 * @return
 */
QPoint ElPassant::getAttacker2() {
    return attacker2;
}

/**
 *
 * @return
 */
QPoint ElPassant::getVictim() {
    return victim;
}

/**
 *
 * @return
 */
bool ElPassant::getPresent() {
    return isPresent;
}
