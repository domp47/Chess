#ifndef PROJECT_REPRESENTATIONMAP_H
#define PROJECT_REPRESENTATIONMAP_H


#include <string>
#include <unordered_map>

class RepresentationMap {
public:
    RepresentationMap();
    std::string getItem(int key);

private:
    std::unordered_map<int, std::string> map;
};


#endif //PROJECT_REPRESENTATIONMAP_H
