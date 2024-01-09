// Christian De Chirico 2074972
#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{
public:
    // Costruttore che richiama quello della superclasse
    Human(int ID) : Giocatore(ID){}

    Giocatore& operator=(Human* g);

    bool choice() override;

};

#endif  // HUMAN_H