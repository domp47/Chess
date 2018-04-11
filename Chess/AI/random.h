#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <Controller/controller.h>

class Board;

class Random{

public:
    Random();
    char getRandomUpgrade();

private:
    std::random_device rd;
    std::mt19937 mt;
};

#endif // RANDOM_H