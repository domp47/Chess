#ifndef EVALMAP_H
#define EVALMAP_H

#include <string>
#include <unordered_map>

class EvalMap {
public:
    EvalMap();
    int getItem(int key);

private:
    std::unordered_map<int, int> map;
};

#endif // EVALMAP_H