// Christian De Chirico 2074972
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

#endif  // COMPUTER_H