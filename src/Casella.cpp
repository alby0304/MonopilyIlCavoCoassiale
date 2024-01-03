#include "../include/Casella.h"

Casella::Casella(int R, int C, char cont)
{
    // Conversione da "riga 1" a "riga A"
    char r = int_to_char(R);

    _coordinata = std::make_pair(r,C);
    _type = cont;
}

Casella* Casella::find(std::pair<char,int> target)
{
    // Controllo che il nodo su cui viene chiamato è quello che cerco
    if(this->_coordinata== target)
        return this;

    // Se il giocatore non è in questa casella, provo a cercare "andando avanti" rispetto alla Casella this
    // Questo avviene finchè non ritorno da dove sono partito (controllo nella condizone while)
    Casella* next = this->succ;
    while (next->_type != 'P')
    {
        if ((next->_coordinata.first == target.first)&&((next->_coordinata.second == target.second)))
        {
            return next;
        }
        next = next->succ;
    }

    // Se non lo ho trovato significa che non c'è (non dovrebbe succedere), quindi restituisco nullptr 
    return nullptr;
}

std::string Casella::to_String()
{
    // Ogni casella viene rappresentata da una stringa di 9 spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";

    // Salva in s lo spazio vuoto solo se non c'è nessun giocatore sopra
    if ((_players.size()==0)&&(_type==' '))
        s = s + _type;
    // Salva in s 'P' e poi eventuali giocatori
    if (_type=='P')
        s = s + _type;
    for (int i=0; i < _players.size(); i++)
    {
        s = s +  std::to_string(_players[i]);
    }

    s = s + "|";
    s = normalize(s, _dim_max_Casella);
    return s;
}

std::string normalize (std::string s, int _dim_max_Casella)
{
    // In questo programma normalize viene invocato da stringhe con lunghezza massima di 7 caratteri, quindi è sempre minore di dim_max_Cella
    // Sfrutto il fatto che la divisione tra due interi in C++ restituisce la parte intera del risultato, troncando eventuali decimali
    int x = (_dim_max_Casella - s.length())/2;
    // Aggiungo x spazi da entrambe le parti (per arrivaere a: s.length() = dim_max_Cella || dim_max_Cella-1)
    for (int i=0; i<x; i++)
    { 
        s = " " + s + " ";
    }
    // Se s.length() = dim_max_Cella-1, aggiungo uno spazio a sinistra (scelta di programmazione, potevo agiungerlo anche a destra)
    if (s.length()!=_dim_max_Casella)
    {
        s = " " + s;
    }
    return s;
}

char int_to_char(int n)
{
    switch(n)
    {
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return 'E';
        case 5: return 'F';
        case 6: return 'G';
        case 7: return 'H';
    }
    // Sarebbe il default dello switch
    return ' ';
}

void Casella::addPlayer(int ID_player)
{
    _players.push_back(ID_player);
}

void Casella::removePlayer()
{
    // Se c'è almeno un giocatore su questa casella, allora posso toglierlo
    if(!_players.empty())
    {
         _players.erase(_players.begin());
    }
}
