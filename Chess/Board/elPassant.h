//
// Created by dom on 29/03/18.
//

#ifndef PROJECT_ELPASSANT_H
#define PROJECT_ELPASSANT_H

#include <QtCore/QPoint>

class ElPassant{
public:
    ElPassant();
    void setElPassant(QPoint attacker, QPoint victim);
    void clearElPassant();
    bool getPresent();
    QPoint getAttacker();
    QPoint getVictim();

private:
    bool isPresent;
    QPoint attacker;
    QPoint victim;
};

#endif //PROJECT_ELPASSANT_H
