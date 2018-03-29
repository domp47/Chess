#include "elPassant.h"



ElPassant::ElPassant() {
    clearElPassant();
}

void ElPassant::setElPassant(QPoint attacker, QPoint victim) {
    this->attacker = attacker;
    this->victim = victim;
    isPresent = true;
}

void ElPassant::clearElPassant() {
    attacker = NULL;
    victim = NULL;
    isPresent = false;
}

QPoint ElPassant::getAttacker() {
    return attacker;
}

QPoint ElPassant::getVictim() {
    return victim;
}

bool ElPassant::getPresent() {
    return isPresent;
}
