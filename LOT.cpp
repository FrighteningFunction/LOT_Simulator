#include "LOT.h"

#include <vector>
#include <string>
#include <memory>
#include <random>

Error* LOT::ChooseError(const std::vector<std::unique_ptr<Error>>& errors) const {
    // Ha üres
    if(errors.empty()) {
        return nullptr;
    }

    // Random index generálás
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, errors.size() - 1);

    int randomIndex = dist(mt);

    //A  kiválasztott Error pointerének visszaadása
    return errors[randomIndex].get();
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

    double score= RAND-(Corporatebar+Studentbar)/4;

    if (score<0) score=0; //0-nál kisebb score nem értelmezett

    int num=2; //[alapérték], ennyi hiba mindenképpen spawnol

    //A score értéke szerint hozzáadunk még több hibát
    if(score>75) num+=4;
    else if(score>50) num+=3;
    else if(score>25) num+=2;
    else if(score>10) num+=1;
    //egyébként marad az alapérték

    //Random szintet kiválasztva, az Errors globális smart pointereket tároló listából random
    //hibát kiválasztva hozzáadogatunk num db hibát a LOT-hoz
    //vigyázat! A hibák példányait nem szabad törölni, csak a pointereket. A pointerek száma határozza meg,
    //mennyi in-game hiba van a LOT-ban (pl. ha 4db NoisyRoom van, az 4db pointert jelent UGYANARRA a NoisyRoom
    //hibapéldányra, a törlésnek az illúzióját a LOT vectoraiban levő pointereinek törlése jelenti, valamint
    //az eliminate() Error funkció.
    //
    // VALÓJÁBAN NEM SZABADÍTUNK FEL VAGY FOGLALUNK MEMÓRIÁT SOHA.
    for (int i=0; i!=num; i++){
        Szintek[randomszint()].push_back(ChooseError(Errors));
    }

    //többi hiba...
}
