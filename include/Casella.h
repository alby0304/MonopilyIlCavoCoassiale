#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>
#include <string>
#include <vector>

// Questa è una casella generica e rappresenta le caselle agli angoli
class Casella
{
public:
    
    // Costruttore
    Casella(int R, int C , char cont);

    // Funzioni membro
    void addPlayer(int player);     // Agginge un giocatore (Push_Back)
    void removePlayer();            // Rimuve un giocatore da una casella (metordo vector.erase())
    Casella* find(std::pair<char,int>);

    // Utile per la stampa
    virtual std::string to_String();
    
    // Funzioni GET
    char getType()     const    {return _type;}   // Utile per le caselle laterali
    Casella* getSucc() const    {return succ;}

    // Metodo per settare la casella successiva (usato solo dal costruttore del tabellone)
    void setSucc(Casella* next) {succ = next;}

    // Variabili oggetto
    const int _dim_max_Casella = 9;
    /*
    La scelta del 9 è per poter stampare il carattere di inizio casella "|" + il tipo di casella "E/S/L/ "
    + un numero variabile di giocatori (massimo 4, caso raro ma possibile) + carattere di chiusura cella "|"
    = tot, che al massimo è 7.
    Aggiungo qualche spazio a destra e sinistra per avere un output del tabellone più omogeneo e arrivo a 9.
    */
protected:
    Casella *succ;
    std::vector<int> _players;      // Rappresenta i giocatori che sono sopra alla casella
    std::pair<char,int> _coordinata;
    char _type;
};

// Metodi e variabili utili per la stampa, dichiarati in scope globale così tutti i file vi hanno accesso
std::string normalize(std::string, int);
char int_to_char(int);

#endif // CASELLA_H