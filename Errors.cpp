/**
 * @file Errors.cpp
 * @brief A játékban előforduló hiba osztályok részletes megvalósításai.
 */

#include "Errors.h"

#include <vector>
#include <random>

//Global, nem teljesről kezdünk
int Corp=70; //max: 100
int Stud=50; //max: 100
int Score=0;
int HP=3;
int days=1;

//Error
void Error::barmodify() {
    Corp+=corporate; //mert - és + is lehet az érték, vigyázat!
    Stud+=student;
}
void Error::eliminate() {
    Score+=value;
}

std::ostream& operator<<(std::ostream& os, const Error& obj){
    os<<obj.getname();
    return os;
}

// Szakkollégiumi Programok
SZP::SZP() {
    // A lehetséges szakkollégiumi programok
    std::map<std::string, std::string> programNames = {
            {"Meszaros Tamas jon",                     "Meszaros Tamas jon"},
            {"Magyar 1 filmezes",                      "Magyar 1 filmezes lesz, kotelezo  megjelenes!"},
            {"Jon a puspok",                           "Jon a puspok!!"},
            {"Krisna eloadas",                         "Valami krisnások jönnek!"},
            {"Valamelyik miniszter jon",               "Valamelyik miniszter jon!"},
            {"Kotelezo lakogyules!!",                  "Kopogtak az ajtodon hogy fel ora mulva lakogyules!!!"},
            {"kotelezo PBGYP program",                 "Spawnolt egy random PBGYP program!"},
            {"Szemetszedes Angyalfoldon",              "Menned kell Angyalfoldre szemetet szedni!"},
            {"Mar megint egy lakogyules",              "3 oras lakogyules, mindenki menjen le a foldszintre!! Ding-dong!"},
            {"Interju Valakivel Valahonnan Valamirol", "Random kotelezo eloadas spawnolt, 5 perc mulva kezdodik!"}
    };

    // Random index generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, programNames.size() - 1);
    size_t randomIndex = dist(gen);

    // Iterátor a random indexhez
    auto iter = programNames.begin();
    std::advance(iter, randomIndex);

    // Beállítjuk a spawnolt szakkollégiumi program "neveit"
    name = iter->first;  // Random name
    printable = "DEADLY SCREAMS!!! "+iter->second;  // Corresponding printable

    // Csak a főnökséget dühíti, ha nem veszel részt, egyébként nem ér semmit
    corporate = -6;
    student = 0;
    value = 0;
}

void SZP::barmodify() {
    Corp+=corporate; //mert - és + is lehet az érték, vigyázat!
    HP--; //csökkenti a játékos HP-ját
}

//A többi hiba

// Broken Lighting in the Corridor
BrokenLighting::BrokenLighting() {
    name = "Tonkrement vilagitas a folyoson";
    printable="Nem mukszik  az erzekelo az egyik folyoson!";
    corporate = -2;
    student = -1;
    value = 10;
}

// Malfunctioning Oven
MalfunctioningOven::MalfunctioningOven() {
    name = "Rossz suto";
    printable="Nem melegszik a suto!";
    corporate = -5;
    student = -3;
    value = 20;
}

// Faulty Washing Machine
MoldyWashingMachine::MoldyWashingMachine() {
    name = "Peneszes mosogep";
    printable="Bepeneszedett a mosogep!";
    corporate = -5;
    student = -10;
    value = 5;
}

// Leakage
Leakage::Leakage() {
    name = "Beazas";
    printable="Az egyik szobaban nedvesedik a fal!";
    corporate = -3;
    student = -7;
    value = 12;
}

// Malfunctioning Disabled Gate
EldugultWC::EldugultWC() {
    name = "Eldugult WC az egyik szobaban";
    printable="Valaki sved husgolyot huzott le az egyik WC-ben!";
    corporate = -5;
    student = -10;
    value = 30;
}

// Noisy Room
NoisyRoom::NoisyRoom() {
    name = "Hangos szoba";
    printable="Enekelnek, vihognak, bombolo zenet hallgatnak az egyik szobaban!";
    corporate = -3;
    student = -1;
    value = 5;
}

// Noisy Party
NoisyParty::NoisyParty() {
    name = "Hangos Party";
    printable="Az egesz Magyar Tudosok korutja feljelentette a kollegiumot!";
    corporate = -8;
    student = -1;
    value = 10;
}

// False Fire Alarm
FalseFireAlarm::FalseFireAlarm() {
    name = "Teves Tuzriado";
    printable="Valaki szetegette a bacont a konyhaban!";
    corporate = -5;
    student = -5;
    value = 25;
}

// Mixed-Up Entry Cards
MixedUpEntryCards::MixedUpEntryCards() {
    name = "Osszekevert belepokartyak";
    printable="Rosszul osztottak ki a belepokartyakat az egyik szinten!";
    corporate = -2;
    student = -2;
    value = 12;
}

// Penészes hűtő!
MoldyFridge::MoldyFridge() {
    name = "Peneszes huto!";
    printable="Rohad a huto!";
    corporate = -1;
    student = -2;
    value = 10;
}

// Broken Library Computers
Rosszulfelmosott::Rosszulfelmosott() {
    name = "Rosszul felmosott folyoso";
    printable="Az egyik szinten rosszul mostak fel a padlot";
    corporate = -3;
    student = -3;
    value = 8;
}

// Poster Door in Room 208
PosterDoorInRoom208::PosterDoorInRoom208() {
    name = "Poszteres ajto";
    printable="Kiposztereztek egy ajtot!";
    corporate = 2;
    student = -1;
    value = 8;
}

//Kupi egy konyhában
KupiaKonyhaban::KupiaKonyhaban() {
    name = "Kupi a konyhaban";
    printable="Kupit csinaltak az egyik konyhaban!";
    corporate = -4;
    student = -4;
    value = 20;
}

/**
 * @details
 * @todo Igazából ezek szimpla lambda funkciókat tároló vectorok is lehetnének,
 * Azért hagytam mégis így meg, hogy ID-k alapján is kereshetők legyenek a funkciók.
 * Pillanatnyilag csak "felcsapunk" egy map entryt, és csak a spawnoló Error kell nekünk,
 * teljesen érdektelen, milyen az az Error,
 * hiszen a hiba kategóriáját úgyis a map maga határozza meg (diák és nem-diák eredetű hibák
 * külön vannak tárolva)
 */

///az összes nem-diák hibatípust tároló map. A hibák egyenletes randomizálásához kell.
const std::map<string, std::function<std::unique_ptr<Error>()>> Errors{
        {"BrokenLighting", [](){ return std::make_unique<BrokenLighting>(); }},
        {"MalfunctioningOven", [](){ return std::make_unique<MalfunctioningOven>(); }},
        {"MoldyWashingMachine", [](){ return std::make_unique<MoldyWashingMachine>(); }},
        {"Leakage", [](){ return std::make_unique<Leakage>(); }},
        {"MalfunctioningDisabledGate", [](){ return std::make_unique<EldugultWC>(); }},
        {"MixedUpEntryCards", [](){ return std::make_unique<MixedUpEntryCards>(); }},
        {"BrokenLibraryComputers", [](){ return std::make_unique<Rosszulfelmosott>(); }},
        {"ElevatorNotWorking", [](){ return std::make_unique<KupiaKonyhaban>(); }}
};

///Az összes diák eredetű hibatípust tároló map. A hibák egyenletes randomizáláshoz kell.
const std::map<string, std::function<std::unique_ptr<Error>()>> StudErrors{
        {"NoisyRoom", [](){ return std::make_unique<NoisyRoom>(); }},
        {"NoisyParty", [](){ return std::make_unique<NoisyParty>(); }},
        {"FalseFireAlarm", [](){ return std::make_unique<FalseFireAlarm>(); }},
        {"MoldyFridge", [](){ return std::make_unique<MoldyFridge>(); }},
        {"PosterDoorInRoom208", [](){ return std::make_unique<PosterDoorInRoom208>(); }},


};

