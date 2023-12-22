#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{    
    void buy() override;
};

#endif  // HUMAN_H