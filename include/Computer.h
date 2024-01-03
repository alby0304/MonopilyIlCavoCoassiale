#ifndef ROBOT_H
#define ROBOT_H

#include "Giocatore.h"

class Robot : public Giocatore
{
public:
    Robot(int ID, Casella* P) : Giocatore(ID,P){}

    bool makeChoice() override;     // Decisione automatica con 25% di possibilità di comprarla
};

#endif  // ROBOT_H