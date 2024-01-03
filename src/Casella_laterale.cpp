#include "../include/Casella_laterale.h"
#include "Casella.cpp"

Casella_Laterale::Casella_Laterale(int R, int C, char cont) : Casella(R,C,cont)
{
    // Per settare _albergo, _casa e _proprietario
    reset();

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
    // Ogni casella viene rappresentata da una stringa di dim_ma spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";

    // Salva in s il contenuto (E, S o L)
    s = s + _type;

    // Se c'è una casa o un'albergo lo salvo in s
    if (_casa)
        s = s + "*";
    if (_albergo)
        s = s + "^";

    // Salva in s eventuali giocatori
    for (int i=0; i < _players.size(); i++)
    {
        s = s +  std::to_string(_players[i]);
    }
    
    s = s + "|";
    s = normalize(s, _dim_max_Casella);
    return s;
}

void Casella_Laterale::buy(Giocatore* g)
{
    // Se il giocatore possiede già il terreno e la casa e ha abbastanza soldi, si procede all'acquisto di un albergo
    if ((_proprietario == g)&&(!_albergo)&&(_casa == true)&&(g->getMoney()>_prezzo_albergo))
    {
        _albergo = true;
    }
    // Se il giocatore possiede già il terreno e ha abbastanza soldi, si procede all'acquisto di una casa
    if ((_proprietario == g)&&(_casa == false)&&(g->getMoney()>_prezzo_casa))
    {
        _casa = true;
    }
    // Se la casella non è di nessuno e il giocatore ha abbastanza soldi, si procede all'acquisto
    if ((_proprietario == nullptr)&&(g->getMoney()>_prezzo_terreno))
    {
        _proprietario = g;
    }
}

int Casella_Laterale::getAffitto() const
{
    if (_albergo)
        return _affitto_albergo;
    if (_casa)
        return _affitto_casa;
    // Se non ci sono case o alberghi l'affitto da pagare è 0 
    // (Nella consegna del progetto non c'è scritto di far pagare la rendita del solo terreno, come avviene nel "vero" gioco del monopoli)
    return 0;
}

void Casella_Laterale::reset()
{
    _casa = false;
    _albergo = false;
    _proprietario = nullptr;
}