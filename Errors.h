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

    /// @brief A hiba printable-jét adja vissza
    /// @details printable=az error spawnolásakor kiírandó vicces üzenet
    /// A LOT Errorshout() funkciójához kell
    string getprintable() const {return printable;}

    ///ha megmarad a kör végén, módosítja a bar-okat (HP-t nem)
    virtual void barmodify();

    ///amikor a példány megsemmisül a kör végén, és az értékét hozzáadja a játékos pénztárcájához
    void eliminate();

    ~Error(){
        eliminate();
    }
};
///a nevét nyomtatja ki
std::ostream& operator<<(std::ostream& os, const Error& obj);

//Error class vége


//A szakkollégiumi programok
class SZP : public Error{
public:
    SZP();

    ///A HP-t is módosítja
    void barmodify() override;
};
//Szakkollégiumi programok vége

//Többi hibatípus

/**
 * @name diák eredetű hibák
 * @details Ezek a hibák nagyobb eséllyel spawnolnak,
 * ha a Student bar alacsony.
 * Az értékük kevesebb, míg többet vonnak le, mint a nem-diák
 * eredetűek
 *
 * @todo Több ilyen osztályt hozzáadni, és egyértelműbbé tenni,
 * melyik a helyes döntés. ("Nyomokat elhelyezni"), mert pillanatnyilag
 * nehéz megmondani, melyik hibát érdemesebb kijavítani, mint a másikat,
 * nem tisztán elkülöníthetőek a különböző hibák. (Ötlet: több in-game üzenet)
 */

class MoldyFridge : public Error {
public:
    MoldyFridge();
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

class PosterDoorInRoom208 : public Error {
public:
    PosterDoorInRoom208();
};

//Diák eredetű hibák vége

/**
 * @name Nem-Diák eredetű hibák
 * @details
 * A Student és a Corporate bar együttes felhasználásával spawnolnak.
 * Értékük változó.
 */

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

class EldugultWC : public Error {
public:
    EldugultWC();
};

class MixedUpEntryCards : public Error {
public:
    MixedUpEntryCards();
};

class Rosszulfelmosott : public Error {
public:
    Rosszulfelmosott();
};

class KupiaKonyhaban : public Error {
public:
    KupiaKonyhaban();
};

///@warning Fontos! Új Error alosztály hozzáadásakor ezeket is bővíteni kell majd!

///az összes nem-diák hibatípust tároló map. A hibák egyenletes randomizálásához kell.
extern const std::map<string, std::function<std::unique_ptr<Error>()>> Errors;

///Az összes diák eredetű hibatípust tároló map. A hibák egyenletes randomizáláshoz kell.
extern const std::map<string, std::function<std::unique_ptr<Error>()>> StudErrors;







#endif //LOT_ERRORS_H