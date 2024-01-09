// Giulio Zanardi 2076063

#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>
#include <vector>
#include "Variabili.h"

// Questa è una casella generica e rappresenta le caselle agli angoli
class Casella
{
public:
    // Costruttore
    Casella(int R, int C, char cont);

    // Funzioni membro
    void addPlayer(int player); // Agginge un giocatore nella casella (push_back())
    void removePlayer();        // Rimuve un giocatore dalla casella (erase())
    Casella* find(std::pair<char, int>);

    // Utile per la stampa
    virtual std::string to_String();

    // Funzioni GET
    char getType() const { return _type; }
    Casella* getSucc() const { return _succ; }
    std::pair<char, int> getCoordinata() const { return _coordinata; }

    std::string getCoordinata_to_String() const { return _coordinata.first + std::to_string(_coordinata.second); }

    // Metodo per settare la casella successiva (usato solo dal costruttore del tabellone)
    void setSucc(Casella *next) { _succ = next; }

    // Variabili oggetto
    std::vector<int> _players; // Rappresenta i giocatori che sono sopra alla casella
protected:
    Casella* _succ;
    std::pair<char, int> _coordinata;
    char _type;
};

// Metodi e variabili utili per la stampa, dichiarati in scope globale così tutti i file vi hanno accesso
std::string normalize(std::string);
char int_to_char(int);

#endif // CASELLA_H