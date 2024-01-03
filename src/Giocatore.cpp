#include "..\include/Giocatore.h"

std::string Giocatore::to_String_elenco_proprietà()
{
    std::string s = "Giocatore " + ID;
    s = s + " : ";
    for (int i=0; i< _elenco_proprietà.size(); i++)
        s = s + _elenco_proprietà[i]->to_String() +  " ";
    return s;
}

Giocatore::Giocatore(int n, Casella* P)
{
    _pos = P;
    ID = n;
    _isInGame = true;
    _money = 100;
}