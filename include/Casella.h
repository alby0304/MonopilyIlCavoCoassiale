#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>
#include <string>
#include "Giocatore.h"

enum Index_riga
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H

};

struct position
{
    position() : position(0, 0){};
    position(Index_riga riga, int colonna) : _riga{riga}, _colonna{colonna} {};
    position(int riga, int colonna) : _riga{Index_riga(riga)}, _colonna{colonna} {};
    Index_riga _riga;
    int _colonna;
};

// Questa è una casella generica, ma è anche utile per rappresentare le caselle agli angoli
class Casella
{
public:
    Casella *succ;
    
    // Costruttore
    Casella(Index_riga R, int C, char type);

    //funzioni membro
    void addPlayer(Giocatore* player);// agginge un giocatore (Push_Back)
    void removePlayer(Giocatore* player); //rimuve un giocatore da una casella (metordo vector.erase())

    // Utile per la stampa
    std::string normalize(std::string);
    virtual std::string to_String();
    
    // Funzioni GET
    char getType() const  {return _type;}
    char getDimMaxCasella() const {return _dim_max_Casella;}
    position GetCordinata() const {return _coordinata;}

protected:
    std::vector<Giocatore*> _players;
    const position _coordinata;
    const char _type;
    const int _dim_max_Casella = 9; // Per l'output
    // La scelta del 9 è per poter stampare il carattere di inizio casella "|" + il tipo di casella "E/S/L/ "
    // + un numero variabile di giocatori (massimo 4, caso raro ma possibile) + carattere di chiusura cella "|"
    // = tot, che al massimo è 7
    // Aggiungo qualche spazio a destra e sinistra per avere un output del tabellone più omogeneo e arrivo a 9
};

#endif // CASELLA_H