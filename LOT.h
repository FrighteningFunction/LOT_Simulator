#ifndef LOT_LOT_H
#define LOT_LOT_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>

#include "Errors.h"

class LOT {
    ///@brief heterogén kollekciók, melyek a szintenkénti hibák pointereit tárolják

    std::vector<std::unique_ptr<Error>> Foldszint,
    Elso,
    Masodik,
    Harmadik,
    Negyedik;

    std::vector<std::vector<std::unique_ptr<Error>>> Szintek = {Foldszint, Elso, Masodik, Harmadik, Negyedik};
public:
    LOT()=default;

    ///A spawnerrorshoz kell. Az egyik hibákat tároló mapből választ ki random egy hibatípust, létrehoz abból egy új példányt,
    ///és visszaad egy unique pointert arra a példányra.
    ///@param map Az Errors vagy StudErrors map.
    std::unique_ptr<Error> ChooseError(const std::map<std::string, std::function<std::unique_ptr<Error>()>>& map) const;

    ///egy 0-4-ig terjedő random számot ad vissza (szintén a spawnerrors-hoz kell, a szinteknél)
    int randomszint();

    ///hibákat spawnol minden szintre a stud. bar felhasználásával.
    ///a szakkollégiumi programokat is spawnolja a corp. bar felhasználásával.
    void spawnerrors();


};

#endif //LOT_LOT_H
