#include "LOT.h"

#include <vector>
#include <string>
#include <memory>
#include <random>

std::unique_ptr<Error> LOT::ChooseError(const std::map<string, std::function<std::unique_ptr<Error>()>>& map) const {
    // Ha üres
    if(map.empty()) {
        return nullptr;
    }

    // Random index generálás
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, map.size() - 1);

    int randomIndex = dist(mt);

    // Iterátor, ami a map elejére mutat
    auto iter = map.begin();

// Mozgassuk az iterátort a random szám szerint
    std::advance(iter, randomIndex);

// Most az iter egy random bejegyzésre mutat a mapben
    auto& randomEntry = *iter;

    return (iter->second)();
}

int LOT::randomszint(){
    // Randomszám generálás 0-4 ig
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 4);

    return dist(mt);
}

void LOT::spawnerrors() {
    //Az általános hibákat nézzük meg

    //RAND generálás
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 50.0);

    double RAND = dist(mt);

    double score= RAND-(Corporatebar+Studentbar)/4.0;

    if (score<0) score=0; //0-nál kisebb score nem értelmezett

    int num=2; //[alapérték], ennyi hiba mindenképpen spawnol

    //A score értéke szerint hozzáadunk még több hibát
    if(score>75) num+=4;
    else if(score>50) num+=3;
    else if(score>25) num+=2;
    else if(score>10) num+=1;
    //egyébként marad az alapérték

    for (int i=0; i!=num; i++){
        Szintek[randomszint()].push_back(ChooseError(Errors));
    }

    //többi hiba...
}
