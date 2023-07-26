#ifndef LOT_ERRORS_H
#define LOT_ERRORS_H
/**
 * @file Errors.h
 * @brief A hibák típusait deklaráló fájl.
 * @details
 * Feleslegesen bonyolultnak és "macskakörmösnek" tűnhet,
 * azért használjunk külön osztályt minden hibának mégis, hogy később
 * a játékot könnyen tudjuk bővíteni. Lehet, hogy mindegyik hiba más-más, különlegesebb tulajdonsággal rendelkezne később alapból
 * vagy egy modban, azt pedig egy egyszerű Error structal kényelmetlenebb lenne fejleszteni (felszaporodnának másutt a "case-if"-ek)
 *
 * Alternatív ötlet:
 * Error struktrúra, benne simán egy név, corporate, student, value intek, és egy vektorhoz hozzáadni a típusukat (egyszerű, de rugalmatlan)
 */


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>

typedef std::string string; //!!

extern int Corporatebar;
extern int Studentbar;
extern int Score;

/**
 * @class Error
 * @brief A játék hiba alaposztálya (ne hozzunk létre belőle példányt!). Minden innen származik.
 */
class Error{
protected:
    string name="Uninitialized Error!";
    int corporate=0;
    int student=0;
    int value=0;
public:
    Error()=default;

    string getname() const {return name;}

    //ha megmarad a kör végén, módosítja a bar-okat
    void barmodify();

    //amikor megsemmisül a kör végén, az értékét hozzáadja a játékos pénztárcájához
    void eliminate();
};
std::ostream& operator<<(std::ostream& os, const Error& obj);

//Error class vége


//A szakkollégiumi programok
class szp : public Error{
public:
    szp();
};

//A többi hiba

class BrokenLighting : public Error {
public:
    BrokenLighting();
};

class MalfunctioningOven : public Error {
public:
    MalfunctioningOven();
};

class FaultyWashingMachine : public Error {
public:
    FaultyWashingMachine();
};

class Leakage : public Error {
public:
    Leakage();
};

class MalfunctioningDisabledGate : public Error {
public:
    MalfunctioningDisabledGate();
};

class NoisyRoom : public Error {
public:
    NoisyRoom();
};

class NoisyParty : public Error {
public:
    NoisyParty();
};

class FalseFireAlarm : public Error {
public:
    FalseFireAlarm();
};

class MixedUpEntryCards : public Error {
public:
    MixedUpEntryCards();
};

class MoldyFridge : public Error {
public:
    MoldyFridge();
};

class BrokenLibraryComputers : public Error {
public:
    BrokenLibraryComputers();
};

class PosterDoorInRoom208 : public Error {
public:
    PosterDoorInRoom208();
};

class ElevatorNotWorking : public Error {
public:
    ElevatorNotWorking();
};

///Fontos! Error osztály hozzáadásakor ezt is bővíteni kell!

///az összes nem-diák hibatípust tároló map. A hibák egyenletes randomizálásához kell.
extern std::map<string, std::function<std::unique_ptr<Error>()>> Errors;

///az összes diák eredetű hibatípust tároló map. Szintén a hibák egyenletes randomizáláshoz kell.
extern std::map<string, std::function<std::unique_ptr<Error>()>> StudErrors;




#endif //LOT_ERRORS_H