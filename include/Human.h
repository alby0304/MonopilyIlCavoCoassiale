#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{
public:
    // Costruttore che richiama quello della superclasse
    Human(int ID, Casella* P, int money) : Giocatore(ID,P,money){}
    Human() {}

    Giocatore& operator=(Human* g);

    bool choice() override;

};

#endif  // HUMAN_H