#include "elPassant.h"

ElPassant::ElPassant() {

}

void ElPassant::setElPassant(QPoint attacker, QPoint victim) {
    if(!isPresent){
        this->attacker1 = attacker;
        this->victim = victim;
        isPresent = true;
    }else{
        this->attacker2 = attacker;
    }

}

void ElPassant::clearElPassant() {
    attacker1 = QPoint(-1,-1);
    attacker2 = QPoint(-1,-1);
    victim = QPoint(-1,-1);
    isPresent = false;
}

QPoint ElPassant::getAttacker1() {
    return attacker1;
}

QPoint ElPassant::getAttacker2() {
    return attacker2;
}

QPoint ElPassant::getVictim() {
    return victim;
}

bool ElPassant::getPresent() {
    return isPresent;
}
