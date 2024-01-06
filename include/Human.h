#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{
public:
    // Costruttore che richiama quello della superclasse
    Human(int ID, Casella* P) : Giocatore(ID,P){}
    Human() {}

    Giocatore& operator=(Human* g);

    bool want_to_buy_terreno();     // Se l'utente ha abbastanza soldi gli si chiede se vuole comprare il terreno
    bool want_to_buy_casa();        // Se l'utente ha abbastanza soldi gli si chiede se vuole comprare la casa
    bool want_to_buy_albergo();     // Se l'utente ha abbastanza soldi gli si chiede se vuole comprare l'albergo
};

#endif  // HUMAN_H