#include "Control.h"

///a játék fősodrát ez viszi
int main() {

    LOT& dorm=LOT::mutasdalotot(); //spawnolja a LOT-ot
    while(days<=15 && HP>0){ //addig, míg le nem teltek a napok vagy meg nem halt
        dorm.spawnerrors();
        //kiírja a hibák printable-jait
        dorm.ErrorShout();
        //3s
        wait(3000);

        InterfaceUpdate(dorm);
        //kétszer van lehetősége akciózni, aztán vége a napnak
        for (int i=0; i!=akciok; ++i){
            std::cout<<"Meg "<<akciok-i<<" akciod van!\n";
            dorm.ResolveError(valaszbeker(dorm));
            InterfaceUpdate(dorm);
        }
        dorm.modifyAllBars();

        //meghalt ma a játékos?
        if(HP<=0){
            std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                       "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                       "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                       "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

            std::cout<<"YOU\n";
            wait(1000);
            std::cout<<"DIED\n";
            wait(1000);
            std::cerr<<"Tul sokszor hianyoztal szakkollegiumi programrol!\n";
        }
            //nem, és nem is ez az uccsó nap
        else if(days<=15){
            std::cout << "Elfogytak az akcioid, uj nap kovetkezik!\n";
            days++;

            //éjszaka hangeffektjei
            std::cout << "\n[Tucsokciripeles hangeffekt]\n";
            wait(2000);
            std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                       "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
        }
            //egyébként mondjuk meg neki, ha mégis
        else {
            std::cout<<"Ez volt az uccso nap!\n";
            std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                       "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
        }
    }
    //while ciklus vége

    //Ha sikeresen befejezte a játékot, kiírjuk a pontszámát
    if(HP>0) {
        std::cout<<"Gratula! Sikerult "<<Score<<" pontszamot osszeszedned!\n";
    }

    wait(4000);//vagy a Score-ját, vagy a halálképernyőt bámulja 4 másodpercig
}
