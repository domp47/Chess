#ifndef MAP_H
#define MAP_H

#include <string>
#include <unordered_map>

class Map {
public:
    Map();
    std::string getItem(int key);

private:
    std::unordered_map<int, std::string> map;
};

#endif // MAP_H