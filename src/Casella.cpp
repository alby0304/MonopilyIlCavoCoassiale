#include "../include/Casella.h"

//Costruttore
Casella::Casella(Index_riga R, int C, char type): _coordinata{position(R,C)}, _type{type}{}

//funzioni membros
void Casella::addPlayer(Giocatore* player){
    _players.push_back(player);
}

void Casella::removePlayer(Giocatore* player){
    _players.erase(_players);
}   

std::string Casella::normalize (std::string s)
{
    // in questo programma normalize viene invocato da stringhe con lunghezza massima di 7 caratteri, quindi è sempre minore di dim_max_Cella
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










//Casella::Casella(Index_riga R, int C, char cont): _coordinata{new position(R,C)}, _type{cont}
//{}

/*Casella* Casella::find(int giocatore)
{
    // Controllo che il nodo su cui viene chiamato è quello che cerco
    if(this->giocatore1)
        return this;

    // Se il giocatore non è in questa casella, provo a cercare "andando avanti" rispetto alla Casella this
    // Questo avviene finchè non ritorno da dove sono partito (controllo nella condizone while)
    Casella* next = this->succ;
    while ((next->_riga != this->_riga)&&((next->_colonna != this->_colonna)))
    {
        if(next->giocatore1)
        {
            return next;
        }
        next=next->succ;
    }

    // Se non lo ho trovato significa che non c'è (non dovrebbe succedere), quindi restituisco nullptr 
    return nullptr;
}*/

/*std::string Casella::to_String()
{
    // Ogni casella viene rappresentata da una stringa di 9 spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";
    // Salva in s lo spazio vuoto solo se non c'è nessun giocatore sopra
    if ((!giocatore1)&&(!giocatore2)&&(!giocatore3)&&(!giocatore4)&&(_type==' '))
        s = s + _type;
    // Salva in s 'P' e poi eventuali giocatori
    if (_type=='P')
        s = s + _type;
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
}*/

