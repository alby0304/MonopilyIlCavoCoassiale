#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <vector>
#include "Casella_laterale.h"

class Giocatore
{
public:
    // Costruttore
    Giocatore(int, Casella*);

    // Funzioni membro
    void buy(); // Verifica se il giocatore ha abbastanza soldi (lancio eccezione) e procede all'acquisto in caso positivo (set primi valori private di casella laterale)
    virtual bool makeChoice() = 0; // Restituisce true se il giocatore vuole comprare il terreno/casa/albergo
    
    std::string to_String_elenco_proprietà();

    // Scambi di denaro tra giocatori
    void pay(int n);     // Se non si hanno abbastanza soldi il giocatore ha perso e lancio eccezione
    void deposit(int n); // Quando un altro giocatore cade su un mio terreno e mi deve pagare o quando passo dal via

    // Funzione GET
    int getMoney(){return _money;}
    
    // Move
    void move(int n);   //aggiornare _pos in cella;
    //***************
    // da implementare in futuro ;)
    // void move(position n);
    // void move(Casella c);
    //***************

    // Distruttore
    ~Giocatore(); // _elenco_proprietà, pos

    // Eccezione
    class Money_Finished{};
    
private:
    std::vector<Casella*> _elenco_proprietà;
    int _money;
    int ID;         // Variabile che identifica il giocatore come giocatore 1, 2, 3, ecc. (utile per la stampa)
    Casella* _pos;  // La posizione in cui si trova il giocatore nel tabellone
    bool _isInGame; // = true (utile per la stampa)
};

std::ostream &operator<<(std::ostream &, Giocatore);
/*
Il testo del progetto richiede che (nella legenda) quando viene statmpato un giocatore si scriva questo:
"Giocatore ID nella casella _pos con una casa /con un albergo"
*/

#endif // GIOCATORE_H