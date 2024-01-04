#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{
public:
    // Costruttore che richiama quello della superclasse
    Human(int ID, Casella* P) : Giocatore(ID,P){}

    bool makeChoice() override;
};

#endif  // HUMAN_H