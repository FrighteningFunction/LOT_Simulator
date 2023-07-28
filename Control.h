#ifndef LOT_CONTROL_H
#define LOT_CONTROL_H

#include "Errors.h"
#include "LOT.h"

#include <string>

///Ennyi akciója van a játékosnak egy körben
int const akciok=2;

///A játék címe.
extern const string JATEKCIM;

void clearConsole();

void openingScreen(const std::string& title);

void InterfaceUpdate(LOT& dorm);

int valaszbeker(LOT& dorm);

void wait(int millisec);




#endif //LOT_CONTROL_H
