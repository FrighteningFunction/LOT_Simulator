#ifndef LOT_ERRORS_H
#define LOT_ERRORS_H
/**
 * @file Errors.h
 * @brief A hibák típusait deklaráló fájl.
 * @details
 * Feleslegesen bonyolultnak és "macskakörmösnek" tűnhet,
 * azért használjunk külön osztályt minden hibának mégis, hogy később
 * a játékot könnyen tudjuk bővíteni. Lehet, hogy mindegyik hiba más-más, különlegesebb tulajdonsággal rendelkezne később alapból
 * vagy egy modban, azt pedig egy egyszerű Error structtal kényelmetlenebb lenne fejleszteni (felszaporodnának másutt a "case-if"-ek)
 *
 * Alternatív ötlet:
 * Error struktrúra, benne simán egy név, corporate, student, value intek, és egy vektorhoz hozzáadni a típusukat (egyszerű, de rugalmatlan)
 */


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

typedef std::string string; //!!

///Corporatebar
extern int Corp;
///Studentbar
extern int Stud;
///A  játékos pontszáma
extern int Score;
///A játékos HP-ja
extern int HP;

extern int days;

/**
 * @class Error
 * @brief A játék hiba alaposztálya (ne hozzunk létre belőle példányt!). Minden innen származik.
 */
class Error{
protected:
    //Az Error neve
    string name="Uninitialized Error!";
    //A szöveg, amit spawnoláskor kiír
    string printable="Unitialized Printable!";
    //Amennyivel a Corp-ot módosítja, ha megmarad (- vagy +)
    int corporate=0;
    //Amennyivel a Stud-ot módosítja, ha megmarad (- vagy +)
    int student=0;
    //Amennyit hozzáad a Score-hoz
    int value=0;
public:
    Error()=default;

    string getname() const {return name;}

    string getprintable() const {return printable;}

    //ha megmarad a kör végén, módosítja a bar-okat
    virtual void barmodify();

    //amikor megsemmisül a kör végén, és az értékét hozzáadja a játékos pénztárcájához
    void eliminate();

    ~Error(){
        eliminate();
    }
};
///a printable-t nyomtatja ki, nem a nevét
std::ostream& operator<<(std::ostream& os, const Error& obj);

//Error class vége


//A szakkollégiumi programok
class SZP : public Error{
public:
    SZP();

    void barmodify() override;
};
//Szakkollégiumi programok vége

//Többi hibatípus

class BrokenLighting : public Error {
public:
    BrokenLighting();
};

class MalfunctioningOven : public Error {
public:
    MalfunctioningOven();
};

class MoldyWashingMachine : public Error {
public:
    MoldyWashingMachine();
};

class Leakage : public Error {
public:
    Leakage();
};

class EldugultVC : public Error {
public:
    EldugultVC();
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

class Rosszulfelmosott : public Error {
public:
    Rosszulfelmosott();
};

class PosterDoorInRoom208 : public Error {
public:
    PosterDoorInRoom208();
};

class KupiaKonyhaban : public Error {
public:
    KupiaKonyhaban();
};

///Fontos! Error osztály hozzáadásakor ezeket is bővíteni kell!

///az összes nem-diák hibatípust tároló map. A hibák egyenletes randomizálásához kell.
extern std::map<string, std::function<std::unique_ptr<Error>()>> Errors;

///Az összes diák eredetű hibatípust tároló map. A hibák egyenletes randomizáláshoz kell.
extern std::map<string, std::function<std::unique_ptr<Error>()>> StudErrors;







#endif //LOT_ERRORS_H