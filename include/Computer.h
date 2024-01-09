// Christian De Chirico 2074972
#ifndef COMPUTER_H
#define COMPUTER_H

#include "Giocatore.h"

class Computer : public Giocatore
{
public:

    Computer(int ID) : Giocatore(ID){}

    Giocatore& operator=(Computer* g);

    bool choice() override;
};

#endif  // COMPUTER_H