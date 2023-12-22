#ifndef HUMAN_H
#define HUMAN_H

#include "Giocatore.h"

class Human : public Giocatore
{    
    bool makeChoice() override;
};

#endif  // HUMAN_H