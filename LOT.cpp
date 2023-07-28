/**
 * @file LOT.cpp
 * @brief A LOT-ot megvalósító funckiók részletes kifejtése.
 */

#include "LOT.h"

#include <map>
#include <memory>
#include <functional>
#include <random>

///visszaadja, hány számjegyű egy szám
int countdigit(int no){
    if (no == 0) {
        return 1; // Speckó eset a 0-ra, aminek egy számjegye van
    }

    int count = 0;
    while (no != 0) {
        no /= 10;
        count++;
    }

    return count;
}

//LOT

LOT LOT::peldany;

LOT& LOT::mutasdalotot(){
    return peldany;
}

std::vector<std::vector<std::unique_ptr<Error>>*>& LOT::getSzintek(){
    return Szintek;
}

///Az Errors vagy a StudErrors globális konténerből kiválaszt egy ranodm hibatípust,
///majd abból a hibatípusból visszad egy új olyan típusú hibapéldányra mutató unique_ptr-t.
///@param map Errors vagy StudErrors map (extern)
std::unique_ptr<Error> LOT::ChooseError(const std::map<string, std::function<std::unique_ptr<Error>()>>& map){
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

// Create a distribution that will give us numbers from 0 to map.size() - 1
    std::uniform_int_distribution<> dis(0, map.size() - 1);

// Generate a random number
    int randomIndex = dis(gen);

// Get an iterator pointing to the beginning of the map
    auto iter = map.begin();

// Advance the iterator by the random number
    std::advance(iter, randomIndex);

// Now iter points to a random entry in the map
    auto& randomEntry = *iter;

    return (randomEntry.second)();
}

///Szintén a spawnerrorshoz kell, visszaad egy  random 0-4-ig terjedő számot (a LOT szinteket)
int LOT::randomszint(){
// Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

// 0-4-ig randomszám generálás
    std::uniform_int_distribution<> dis(0, 4);

// visszatérés a generált randomszámmal
    return dis(gen);
}

///hibákat spawnol minden emeletre a stud. bar felhasználásával.
///a szakkollégiumi programokat is spawnolja a corp. bar felhasználásával.
void LOT::spawnerrors(){
    //először generáljuk az általános (non-student) hibákat

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    //RAND generálás
    std::uniform_real_distribution<> dis(0, 50);

    double RAND=dis(gen);

    double score=RAND-(Corp+Stud)/4.0; //0 és 100 közötti szám
    if(score<0) score=0; //0-nál kisebb score nem értelmezett

    int num=2; //[alapérték], ennyi számú hiba mindenképpen spawnol

    if(score>75) num+=4;
    else if(score>50) num+=3;
    else if(score>25) num+=2;
    else if(score>10) num+=1;
    //egyébként marad az [alapérték]

    //num-szor hozzáadunk egy random kiválaszott szinthez a LOT-ban egy random
    //nem-diák alapú új hibapéldányt (Errors  map);
    for(int i=0; i!=num; ++i){
        Szintek[randomszint()]->push_back(ChooseError(Errors));
    }

    //diák-eredetű hibák generálása ----------------------------------------------------
    //Itt kicsit másképp van. num-szor FUTTATJUK LE a "dobást", nem a hibák számát határozza meg
    //közvetlenül a num.

    //num-mal kezdünk.

    num=1; //[alapérték], ennyiszer mindenképpen lefut a "dobás"

    if(Stud<10) num+=2; //vigyázat, itt "fordítva" pásztázzuk az eseteket
    else if(Stud<50) num+=1;
    //egyébként marad [alapérték]

    //num-szor lefuttatjuk a dobást
    for (int i=0; i!=num; i++) {
        //RAND generálás
        std::uniform_real_distribution<> stud_dis(0, 100);

        RAND = stud_dis(gen);

        score = RAND - Stud / 2.0; //0 és 100 közötti szám
        if (score < 0) score = 0; //0-nál kisebb score nem értelmezett

        //Ha a kapott score legalább 50, akkor a dobás pozitív,
        // és spawnol egy diák-eredetű hiba
        if (score >= 50) Szintek[randomszint()]->push_back(ChooseError(StudErrors));
    }

    //szakkollégiumi programok generálása ----------------------------------------------
    //ugyanúgy, mint a StudErrorsnál.

    //num-mal kezdünk.

    num=1; //[alapérték], ennyiszer mindenképpen lefut a "dobás"

    if(Corp<10) num+=2; //itt Corporatebart nézünk
    else if(Corp<50) num+=1;
    //egyébként marad [alapérték]

    //num-szor lefuttatjuk a dobást
    for (int i=0; i!=num; i++) {
        //RAND generálás
        std::uniform_real_distribution<> szakk_dis(0, 100);

        RAND = szakk_dis(gen);

        score = RAND - Stud / 4.0; //0 és 100 közötti szám
        if (score < 0) score = 0; //0-nál kisebb score nem értelmezett

        //Ha a kapott score legalább 50, akkor a dobás pozitív,
        // és spawnol egy Szakkollégiumi Program
        if (score >= 50) Szakkollegiumi.push_back(std::make_unique<SZP>());
    }

}
//spawnerrors vége

///szintenként kiprinteli az összes hibát az azonosítójukkal (számukkal) együtt.
void LOT::print() const{
    int i;
    //végighalad az összes szinten
    for (i=0; i!=Szintek.size(); ++i){
        if (i==0) std::cout<<"FOLDSZINT\n";
        else std::cout<<i<<". EMELET\n";
        //kiprinteli az adott szinten az összes hibát
        for (int k=0; k!=Szintek[i]->size(); k++){
            //[00] name\n
            std::cout<<'['<<i<<k<<']'<<' ';
            std::cout << *(Szintek[i]->at(k)) << '\n';
        }
    }
    if (!Szakkollegiumi.empty()){
        int sz=0; //a szakkollégiumi program indexe
        std::cout<<"SZAKKOLLEGIUMI\n";
        for (auto & l : Szakkollegiumi){
            std::cout<<'['<<i<<sz<<']'<<' '; //i=LOT Szintek szama +1
            std::cout << *l << '\n';
            ++sz;
        }
    }
}

///kiprinteli az összes error printable-jét.
void LOT::ErrorShout(){
    //először a szinteken pásztázunk végig
    for (auto & i : Szintek){
        for (auto & k : *i) std::cout<<k->getprintable()<<'\n';
    }
    //aztán az esetleges szakkollégiumi programokon
    for (auto & k : Szakkollegiumi) std::cout<<k->getprintable()<<'\n';
}

///A megadott szám alapján kiválasztott hibát kitörli a listából
void LOT::ResolveError(int index) {
    int digits= countdigit(index);

    int floor;
    if(digits==1) floor=0;
    else floor=index/((digits-1)*10);

    int errorIndex;
    if(digits==1) errorIndex=index;
    else errorIndex=index%((digits-1)*10);

    if(floor<=Floors) {
        Szintek[floor]->erase(Szintek[floor]->begin() + errorIndex);
    }else Szakkollegiumi.erase((Szakkollegiumi.begin()+errorIndex));
}

///vektoraiban fellelhető összes hibának meghívja a barmodify()
///funkcióját, ezzel a globális barokat módosítva
void LOT::modifyAllBars() {
    // List of all the vectors
    std::vector<std::vector<std::unique_ptr<Error>>*> allVectors = {&Foldszint, &Elso, &Masodik, &Harmadik, &Negyedik, &Szakkollegiumi};

    // Iterate over each vector
    for(auto& vec : allVectors) {
        // Iterate over each unique_ptr<Error> in the vector
        for(auto& errorPtr : *vec) {
            // Call the barmodify() function
            errorPtr->barmodify();
        }
    }
}

///Minden hibát kitöröl anélkül, hogy a globális változók változnának
void LOT::Reset() {
    // Save the original values of the global variables
    int originalScore = Score;
    int originalStud = Stud;
    int originalCorp = Corp;

    // Clear all vectors
    Foldszint.clear();
    Elso.clear();
    Masodik.clear();
    Harmadik.clear();
    Negyedik.clear();
    Szakkollegiumi.clear();

    // Restore the global variables to their original values
    Score = originalScore;
    Stud = originalStud;
    Corp = originalCorp;
}

///igen, ha van szakkollegiumi program
///nem, ha nincs
bool LOT::van_eSzakkollegiumi() const{
    return !Szakkollegiumi.empty();
}

///egy referenciát ad vissza a szakkollégiumi programokat tároló vectorra
std::vector<std::unique_ptr<Error>>& LOT::getSzakkollegiumi(){
    return Szakkollegiumi;
}


