// Christian De Chirico 2074972
#include "../include/Computer.h"
#include <random>

bool Computer::choice(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 4);

    return distr(gen) == 1;
}

Giocatore& Computer::operator=(Computer* g){
    _pos= g->getPosition();
    _ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(_ID);
    return *this;
}