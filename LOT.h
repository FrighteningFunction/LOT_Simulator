/**
 * @file LOT.h
 * @brief A LOT class deklarációját tartalmazó fájl
 */

#ifndef LOT_LOT_H
#define LOT_LOT_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "Errors.h"

///visszaadja, hány számjegyű egy szám
int countdigit(int no);

/**
 * @class LOT
 * @brief A LOT-ot megtestesítő virtuális @singleton osztály, mely a hibákat tárolja
 *
 * @details
 * Az egyik vector a hibákat tároló konténereket jelenti,
 * A másik vector pedig a LOT-beli SZINTEKRE ad smart pointereket
 * Ezt nehéz lehet megszokni, de van egy jó oka: A Szakkollégiumi programokat külön kezeljük a többi hibától,
 * ugyanis elvégre csak a megvalósításban számítanak hibának.
 *
 * @todo Ötlet: Ha a jövőben elkülönítünk többféle hibakategóriákat, érdemes lehet kicsit változtatni a struktúrán,
 * pontosabban minden hibakategóriának külön vectorokat létrehozni, amiket végigpásztázhatunk. Ennek fényjelzésére
 * tettem és kezeltem külön a szakkollégiumi programokat a kódban (nem tettem a szintek közé, minek), még akkor is,
 * ha így bonyolultabb. Mégis átláthatóbb.
 */
class LOT {
private:
    ///@brief heterogén kollekciók, melyek a szintenkénti hibákat tárolják
    std::vector<std::unique_ptr<Error>> Foldszint,
    Elso,
    Masodik,
    Harmadik,
    Negyedik,
    Szakkollegiumi;

    ///A fenti szinteket egybegyűjtő konténer. Dereferálni kell, kicsit kellemetlen, de ez a legegyszerűbb megoldás
    std::vector<std::vector<std::unique_ptr<Error>>*> Szintek = {&Foldszint, &Elso, &Masodik, &Harmadik, &Negyedik};
    //Szakkollégiumi progamok külön kezelve!

    LOT()=default;

    ///A LOT singleton példánya
    static LOT peldany;
public:

    //kitörölt copy kontruktor és assignment operátor
    LOT(const LOT&) = delete;
    LOT& operator=(const LOT&) = delete;

    //a játék számára releváns megvalósítás

    ///Referenciát ad a LOT egyetlen létező singleton példányára
    static LOT& mutasdalotot();

    ///Egy egyszerű konstans, ami megmutatja, hány szintű a LOT
    ///@details esetleges bővítéseknél lehet nagyobb szerepe,
    ///egyébként a kód átláthatótáságának megőrzésében segít.
    const int Floors=static_cast<int>(Szintek.size()-1);

    ///Visszaad egy referenciát a szintekre mutató smart pointereket tároló Szintek vectorra
    std::vector<std::vector<std::unique_ptr<Error>>*>& getSzintek();

    ///Az Errors vagy a StudErrors globális konténerből kiválaszt egy random hibatípust,
    ///majd abból a hibatípusból visszad egy új olyan típusú hibapéldányra mutató unique_ptr-t.
    ///@param map Errors vagy StudErrors map (extern)
    std::unique_ptr<Error> ChooseError(const std::map<string, std::function<std::unique_ptr<Error>()>>& map);

    ///Szintén a spawnerrorshoz kell, visszaad egy  random 0-4-ig terjedő számot (a LOT szinteket)
    int randomszint();

    ///hibákat spawnol minden emeletre a stud. + corp.bar felhasználásával.
    ///a szakkollégiumi programokat is spawnolja a corp. bar felhasználásával.
    void spawnerrors();

    ///szintenként kiprinteli az összes hibát az azonosítójukkal (számukkal) együtt.
    void print() const;

    ///kiprinteli az összes error printable-jét.
    void ErrorShout();

    ///A megadott szám alapján kiválasztott hibát kitörli a listából
    void ResolveError(int index);

    ///vektoraiban fellelhető összes hibának meghívja a barmodify()
    ///funkcióját, ezzel a globális barokat módosítva
    void modifyAllBars();

    ///Minden hibát kitöröl anélkül, hogy a globális változók változnának
    void Reset();

    ///igen, ha van szakkollegiumi program
    ///nem, ha nincs
    bool van_eSzakkollegiumi() const;

    ///egy referenciát ad vissza a szakkollégiumi programokat tároló vectorra
    std::vector<std::unique_ptr<Error>>& getSzakkollegiumi();

};

#endif //LOT_LOT_H
