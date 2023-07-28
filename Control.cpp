/**
 * @file Control.cpp
 * @brief A fő, játékot irányító ciklust kiszolgáló funckiók.
 */

#include "Control.h"
#include "LOT.h"

#include <iostream>
#include <thread>
#include <chrono>

typedef std::string string;

///A játék címe
const string JATEKCIM="LOT Simulator";

///@brief törli a konzolt, kiprinteli a
///Pontszámot,
///Eleterőt,
///Hányadik nap van,
///Valamint a LOT összes hibáját
void InterfaceUpdate(const LOT& dorm){
    //kiprintelünk egy elválasztót, különben kesze-kusza lenne a játék
    std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
               "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    std::cout<<"Pontszam: "<<Score<<'\n';
    std::cout<<"Eleterod: "<<HP<<"\n";
    std::cout<<"LOT DAY "<<days<<"\n\n";
    dorm.print();
}

/**
 * Bekéri a felhasználótól, melyik hibát szeretné kijavítani,
 * illetve mit szeretne csinálni.
 * ellenőrzi az input helyességét.
 * @param dorm a LOT példányának referenciája
 * @return egy helyes int
 */
int valaszbeker(LOT& dorm){
    std::cout << "Mit szeretnel kijavitani, vagy min szeretnel reszt venni? "
                 "(Valaszkent usd be az elvegzendo lehetoseg elotti szamot!)\n";

    std::string userInput;
    std::cin >> userInput;

    try {
        //számot írt be?
        int userChoice = std::stoi(userInput);
        int digits= countdigit(userChoice);

        //kiszámoljuk a szintszámot
        int floor;
        if(digits==1) floor=0;
        else floor=userChoice/((digits-1)*10);
        //kiszámoljuk az Error számát is
        int errorIndex;
        if(digits==1) errorIndex=userChoice;
        else errorIndex=userChoice%((digits-1)*10);

        //jó-e a szintszám?
        ///Itt jön képbe, hogy külön kezeljük a Szakkollégiumi programokat sajnos,
        ///kicsit kellemetlen
        if(dorm.van_eSzakkollegiumi()) {
            //ha van, akkor szintek+1 floor index is értelmezett
            if (floor < 0 || floor > dorm.Floors+1) {
                throw std::out_of_range("A szintszam hatarokon kívul van");
            }
        } else {
            //ha  nincs, akkor nem szabad szinteken túl indexelni
            if (floor < 0 || floor > dorm.Floors) {
                throw std::out_of_range("A szintszam hatarokon kívul van");
            }
        }

        //jó-e az Errorindex?
        if(floor<=dorm.Floors) {
            //ha a szintekre hivatkozott a játékos
            if (errorIndex < 0 || errorIndex >= dorm.getSzintek()[floor]->size()) {
                throw std::out_of_range("A hiba indexe hataron kivul esik");
            }
        }else{
            //ha a szakkollégiumi programokra hivatkozott a játékos
            if (errorIndex < 0 || errorIndex >= dorm.getSzakkollegiumi().size()) {
                throw std::out_of_range("A hiba indexe hataron kivul esik");
            }
        }

        return userChoice;
    }

    //Itt kapjuk el, ha nem számot írt be
    catch (std::invalid_argument& e) {
        std::cerr << "Kerlek, szamot irj be!\n";
        return valaszbeker(dorm);  // Ask for input again
    }
    //Itt kapjuk el a szintszám- és Errorindex bajokat
    catch (std::out_of_range& e) {
        std::cerr <<e.what()<< "\n";
        return valaszbeker(dorm);  // Ask for input again
    }
}

///vár egy megadott mennyiségű millisecundumot
void wait(int millisec){std::this_thread::sleep_for(std::chrono::milliseconds(millisec));}
