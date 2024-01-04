#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
public:

    Computer(int ID, Casella* P) : Giocatore(ID,P){}

    bool makeChoice() override;     // Decisione automatica con 25% di possibilità di comprarla
};

#endif  // COMPUTER_H