#ifndef LOT_LOT_H
#define LOT_LOT_H

#include <iostream>
#include <vector>

#include "Errors.h"

class LOT {
    ///@brief heterogén kollekciók, melyek a szintenkénti hibákat tárolják

    std::vector<Error*> Elso,
    Masodik,
    Harmadik,
    Negyedik;
public:
    LOT()=default;

    ///hibákat spawnol minden emeletre a stud. bar felhasználásával.
    ///a szakkollégiumi programokat is spawnolja a corp. bar felhasználásával.
    void spawnerrors();


};

#endif //LOT_LOT_H
