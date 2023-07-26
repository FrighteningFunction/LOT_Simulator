#include "Errors.h"

#include <vector>
#include <random>

//Global
int Corporatebar=100;
int Studentbar=100;
int Score=0;

//Error
void Error::barmodify() {
    Corporatebar-=corporate;
    Studentbar-=student;
}
void Error::eliminate() {
    Score+=value;
}

std::ostream& operator<<(std::ostream& os, const Error& obj){
    os<<obj.getname();
    return os;
}

// Szakkollégiumi programok
szp::szp() {
    std::vector<std::string> programNames = {"Meszaros Tamas jon", "Magyar 1 filmezes", "Jon a puspok",
                                             "Krisna eloadas", "Valamelyik miniszter jon", "Kotelezo lakogyules!!",
                                             "kotelezo PBGYP program", "Szemetszedes Angyalfoldon", "Mar megint egy lakogyules",
                                             "Interju Valakivel Valahonnan Valamirol"};

    //random indexet csinálunk
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, programNames.size()-1);
    size_t randomIndex=dist(gen);


    name = "DEADLY SCREAMS!!"+programNames[randomIndex];  // DEADLY SCREAMS!! [Random név]
    //Csak a főnökséget dühíti, ha nem veszel részt, amúgy nem ér semmit
    corporate = 6;
    student = 0;
    value = 0;
}

// Broken Lighting in the Corridor
BrokenLighting::BrokenLighting() {
    name = "Broken Lighting in the Corridor";
    corporate = -2;
    student = -1;
    value = 10;
}

// Malfunctioning Oven
MalfunctioningOven::MalfunctioningOven() {
    name = "Malfunctioning Oven";
    corporate = -5;
    student = -3;
    value = 20;
}

// Faulty Washing Machine
FaultyWashingMachine::FaultyWashingMachine() {
    name = "Faulty Washing Machine";
    corporate = -2;
    student = -2;
    value = 15;
}

// Leakage
Leakage::Leakage() {
    name = "Leakage";
    corporate = -3;
    student = -2;
    value = 12;
}

// Malfunctioning Disabled Gate
MalfunctioningDisabledGate::MalfunctioningDisabledGate() {
    name = "Malfunctioning Disabled Gate";
    corporate = -2;
    student = -4;
    value = 30;
}

// Noisy Room
NoisyRoom::NoisyRoom() {
    name = "Noisy Room";
    corporate = -3;
    student = -1;
    value = 8;
}

// Noisy Party
NoisyParty::NoisyParty() {
    name = "Noisy Party";
    corporate = -4;
    student = -1;
    value = 10;
}

// False Fire Alarm
FalseFireAlarm::FalseFireAlarm() {
    name = "False Fire Alarm";
    corporate = -5;
    student = -5;
    value = 25;
}

// Mixed-Up Entry Cards
MixedUpEntryCards::MixedUpEntryCards() {
    name = "Mixed-Up Entry Cards";
    corporate = -2;
    student = -2;
    value = 12;
}

// Penészes hűtő!
MoldyFridge::MoldyFridge() {
    name = "Moldy Fridge";
    corporate = -1;
    student = -2;
    value = 10;
}

// Broken Library Computers
BrokenLibraryComputers::BrokenLibraryComputers() {
    name = "Broken Library Computers";
    corporate = -3;
    student = -3;
    value = 18;
}

// Poster Door in Room 208
PosterDoorInRoom208::PosterDoorInRoom208() {
    name = "Poster Door in Room 208";
    corporate = 2;
    student = -1;
    value = 8;
}

// Elevator Not Working
ElevatorNotWorking::ElevatorNotWorking() {
    name = "Elevator Not Working";
    corporate = -4;
    student = -4;
    value = 20;
}

///az összes nem-diák hibatípust tároló map. A hibák egyenletes randomizálásához kell.
std::map<string, std::function<std::unique_ptr<Error>()>> Errors=
        {
                {"Broken Lighting", [](){ return std::make_unique<BrokenLighting>(); }},

                {"Malfunctioning Oven", [](){ return std::make_unique<MalfunctioningOven>(); }},

                {"Faulty Washing Machine", [](){ return std::make_unique<FaultyWashingMachine>(); }},

                {"Leakage", [](){ return std::make_unique<Leakage>(); }},

                {"Malfunctioning Disabled Gate", [](){ return std::make_unique<MalfunctioningDisabledGate>(); }},

                {"Mixed-Up EntryCards", [](){ return std::make_unique<MixedUpEntryCards>(); }},

                {"Broken Library Computers", [](){ return std::make_unique<BrokenLibraryComputers>(); }},

                {"Poster Door In Room208", [](){ return std::make_unique<PosterDoorInRoom208>(); }},

                {"Elevator Not Working", [](){ return std::make_unique<ElevatorNotWorking>(); }}
        };

///az összes diák eredetű hibatípust tároló map. Szintén a hibák egyenletes randomizáláshoz kell.
std::map<string, std::function<std::unique_ptr<Error>()>> StudErrors=
        {
                {"Noisy Room", [](){ return std::make_unique<NoisyRoom>(); }},

                {"Noisy Party", [](){ return std::make_unique<NoisyParty>(); }},

                {"False Fire Alarm", [](){ return std::make_unique<FalseFireAlarm>(); }},

                {"Moldy Fridge", [](){ return std::make_unique<MoldyFridge>(); }},
        };


