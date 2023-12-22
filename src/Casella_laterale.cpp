#include "../include/Casella_laterale.h"

Casella_Laterale::Casella_Laterale(Index_riga R, int C, char cont) : Casella(R,C,cont)
{
    _casa = false;
    _albergo = false;
    _proprietario = 0; // IL proprietario è il "giocatore 0", ovvero la banca
    if(_type=='E')
    {
        _prezzo_terreno = 6;
        _prezzo_casa    = 3;
        _prezzo_albergo = 3;
        _affitto_casa   = 2;
        _affitto_albergo= 4;
    }
    if(_type=='S')
    {
        _prezzo_terreno = 10;
        _prezzo_casa    = 5;
        _prezzo_albergo = 5;
        _affitto_casa   = 4;
        _affitto_albergo= 8;
    }
    if(_type=='L')
    {
        _prezzo_terreno = 20;
        _prezzo_casa    = 10;
        _prezzo_albergo = 10;
        _affitto_casa   = 7;
        _affitto_albergo= 14;
    }
}

std::string Casella_Laterale::to_String()
{
    // Ogni casella viene rappresentata da una stringa di 9 spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";

    // Salva in s il contenuto (E, S o L)
    s = s + _type;

    // Se c'è una casa o un'albergo lo salvo in s
    if (_casa)
        s = s + "*";
    if (_albergo)
        s = s + "^";

    // Salva in s eventuali giocatori
    if(giocatore1)
        s = s + "1";
    if(giocatore2)
        s = s + "2";
    if(giocatore3)
        s = s + "3";
    if(giocatore4)
        s = s + "4";

    s = s + "|";

    s = normalize(s);
    return s;
}
