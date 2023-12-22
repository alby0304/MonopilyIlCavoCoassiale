#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Casella.h"
#include <vector>

class Giocatore
{
    int money;
    std::string name;
    virtual void buy();
    Casella* _poss;
    
    std::vector<std::pair<char,int>> _elenco_proprietà;

};

#endif  // GIOCATORE_H