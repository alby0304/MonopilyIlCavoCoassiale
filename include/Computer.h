#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
    void buy() override;
};

#endif  // COMPUTER_H