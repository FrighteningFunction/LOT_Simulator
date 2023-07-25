#ifndef LOT_LOT_H
#define LOT_LOT_H

#include <iostream>
#include <vector>
#include <memory>

#include "Errors.h"

class LOT {
    ///@brief heterogén kollekciók, melyek a szintenkénti hibák pointereit tárolják

    std::vector<Error*> Foldszint,
    Elso,
    Masodik,
    Harmadik,
    Negyedik;

    std::vector<std::vector<Error*>> Szintek = {Foldszint, Elso, Masodik, Harmadik, Negyedik};
public:
    LOT()=default;

    ///A spawnerrorshoz kell. Az Errors listából választ ki random egy hibát, és egy pointert ad vissza rá.
    ///@param vector Az Errors vagy StudErrors vector.
    Error* ChooseError(const std::vector<std::unique_ptr<Error>>& vector) const;

    ///egy 0-4-ig terjedő random számot ad vissza (szintén a spawnerrors-hoz kell, a szinteknél)
    int randomszint();

    ///hibákat spawnol minden szintre a stud. bar felhasználásával.
    ///a szakkollégiumi programokat is spawnolja a corp. bar felhasználásával.
    void spawnerrors();


};

#endif //LOT_LOT_H
