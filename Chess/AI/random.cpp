#include "random.h"

#include <iostream>

Random::Random() {
    mt = std::mt19937(rd());
}

char Random::getRandomUpgrade() {
    std::uniform_int_distribution<int> moveDist(0,3);
    int piece = moveDist(mt);

    switch (piece){
        case 0:
            return 'r';
        case 1:
            return 'k';
        case 2:
            return 'b';
        default:
            return 'q';
    }
}
