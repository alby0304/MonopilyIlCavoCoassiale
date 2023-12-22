#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
    bool makeChoice() override;
};

#endif  // COMPUTER_H