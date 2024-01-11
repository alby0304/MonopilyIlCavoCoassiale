// Giulio Zanardi 2076063

#include "../include/Casella.h"

Casella::Casella(int R, int C, char cont) : _coordinata{std::make_pair(int_to_char(R), C)}, _type{cont}
{
    // Conversione da "riga 1" a "riga A"
    // char r = int_to_char(R);
    // _coordinata = std::make_pair(r,C);
    // _type = cont;
}

Casella *Casella::find(std::pair<char, int> target)
{
    // Controllo che il nodo su cui viene chiamato è quello che cerco
    if (this->_coordinata == target)
        return this;

    // Se il giocatore non è in questa casella, provo a cercare "andando avanti" rispetto alla Casella this
    // Questo avviene finchè non ritorno da dove sono partito (controllo nella condizione while)
    Casella *next = this->_succ;
    while (next->_type != 'P') // il find viene chiamatop sempre dalla casella di partenza
    {
        if ((next->_coordinata.first == target.first) && ((next->_coordinata.second == target.second)))
        {
            return next;
        }
        next = next->_succ;
    }

    // Se non lo ho trovato significa che non c'è (non dovrebbe succedere), quindi restituisco nullptr
    return nullptr;
}

std::string Casella::to_String()
{
    // Ogni casella viene rappresentata da una stringa di 9 spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";

    // Salva in s lo spazio vuoto solo se non c'è nessun giocatore sopra
    if ((_players.size() == 0) && (_type == ' '))
        s = s + _type;
    // Salva in s 'P' e poi eventuali giocatori
    if (_type == 'P')
        s = s + _type;
    for (int i = 0; i < _players.size(); i++)
    {
        s = s + std::to_string(_players.at(i));
    }

    s = s + "|";
    s = normalize(s);
    return s;
}

std::string normalize(std::string s)
{
    // In questo progetto normalize viene invocato da stringhe con lunghezza massima di 7 caratteri, quindi è sempre minore di dim_max_Cella
    // Sfrutto il fatto che la divisione tra due interi in C++ restituisce la parte intera del risultato, troncando eventuali decimali
    int x = (Variabili::dimMaxCasella - s.length()) / 2;
    // Aggiungo x spazi da entrambe le parti (per arrivaere a: s.length() = dim_max_Cella || dim_max_Cella-1)
    for (int i = 0; i < x; i++)
    {
        s = " " + s + " ";
    }
    // Se s.length() = dim_max_Cella-1, aggiungo uno spazio a sinistra (scelta di programmazione, potevo agiungerlo anche a destra)
    if (s.length() != Variabili::dimMaxCasella)
    {
        s = " " + s;
    }
    return s;
}

char int_to_char(int n)
{
    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char conv = ' ';    // conv = int convertito in carattere convertito
    if ((n < alfabeto.size()) && (n >= 0))
        conv = alfabeto[n];

    return conv;
}

void Casella::addPlayer(int ID_player)
{
    _players.push_back(ID_player);
}

void Casella::removePlayer()
{
    // Se c'è almeno un giocatore su questa casella, allora posso toglierlo
    if (!_players.empty()) // Prevengo la possibile eccezione
    {
        // Il giocatore che si sposta sarà sempre il primo del vettore, perchè è stato il primo ad arrivare (quindi funziona anche in caso di più giocatori sulla stessa casella)
        _players.erase(_players.begin());
    }
}
