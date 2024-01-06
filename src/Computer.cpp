#include "../include/Computer.h"
#include <random>

bool Computer::want_to_buy_terreno() // il computer effettua l'acquisto solo se il numero generato randomicamente (tra 1 e 4) è 1
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 4);

    return distr(gen) == 1;
}

bool Computer::want_to_buy_casa() // il computer effettua l'acquisto solo se il numero generato randomicamente (tra 1 e 4) è 1
{
    return want_to_buy_terreno();
}

bool Computer::want_to_buy_albergo() // il computer effettua l'acquisto solo se il numero generato randomicamente (tra 1 e 4) è 1
{
    return want_to_buy_terreno();
}

Giocatore& Computer::operator=(Computer* g)
{
    _pos= g->getPosition();
    ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(ID);
    return *this;
}

std::ostream& operator<<(std::ostream& os, Computer G)
{
    return os << G.to_String();
}