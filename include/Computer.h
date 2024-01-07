#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
public:

    Computer(int ID, Casella* P, int money) : Giocatore(ID,P,money){}
    Computer() {}

    Giocatore& operator=(Computer* g);

    bool choice() override;
};

std::ostream& operator<<(std::ostream& os, Computer G);

#endif  // COMPUTER_H