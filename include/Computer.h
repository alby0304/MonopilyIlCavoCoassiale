#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
public:

    Computer(int ID, Casella* P) : Giocatore(ID,P){}
    Computer() {}

    Giocatore& operator=(Computer* g);

    bool want_to_buy_terreno();     // Decisione automatica con 25% di possibilità di comprare il terreno
    bool want_to_buy_casa();        // Decisione automatica con 25% di possibilità di comprare la casa
    bool want_to_buy_albergo();     // Decisione automatica con 25% di possibilità di comprarle l'albergo
};

#endif  // COMPUTER_H